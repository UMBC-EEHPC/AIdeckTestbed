#include "CollisionModel.h"
#include "CollisionModelGenerated.inc"

using Core::Device::Cluster;
using etl::vector_ext;

namespace Model {

PI_L2 static uint8_t* original_image;
PI_L2 static uint8_t* resized_image;

PI_L2 static int8_t output;

volatile static void cluster_task(void* arg)
{
/*
 * Needless to say, to collect measurements on how long an inference takes,
 * we need to start the timer right at the beginning of the neural network's run
 */
#ifdef BENCHMARKING_MODEL
    gap_cl_starttimer();
    gap_cl_resethwtimer();
#endif // BENCHMARKING_MODEL

/*
 * If the neural network expects an input image with a different size than the camera
 * outputs, then we need to resize the input image before we actually attempt to
 * run any inferences
 */
#if (CAMERA_WIDTH != MODEL_WIDTH && CAMERA_HEIGHT != MODEL_HEIGHT)
    ResizeImage(original_image, resized_image);
#endif // (CAMERA_WIDTH != MODEL_WIDTH && CAMERA_HEIGHT != MODEL_HEIGHT)

/*
 * If we're benchmarking the model's power usage, we want to run the model in a loop
 * to ensure that everytime the power is sampled, it's coming from the neural network,
 * otherwise, if we're just benchmarking latency or we want to actually use the results
 * from the neural network, we just run a single inference and exit
 */
#if defined(BENCHMARKING_MODEL) && defined(BENCHMARKING_POWER)
    while (true) {
#endif // defined(BENCHMARKING_MODEL) && defined(BENCHMARKING_POWER)
        ptq_int8CNN(resized_image, &output);
#if defined(BENCHMARKING_MODEL) && defined(BENCHMARKING_POWER)
    }
#endif // defined(BENCHMARKING_MODEL) && defined(BENCHMARKING_POWER)
}

CollisionModel::CollisionModel(vector_ext<uint8_t>& frame_data, vector_ext<uint8_t>& frame_resized, Cluster const& cluster)
    : m_cluster(cluster)
{
    assert_gap8(open_model());

    original_image = frame_data.data();
    resized_image = frame_resized.data();

    Resize_L1_Memory = ptq_int8_L1_Memory;
    Resize_L2_Memory = ptq_int8_L2_Memory;

    m_is_model_open = true;
}

[[nodiscard]] bool CollisionModel::run_model()
{
    return m_cluster.submit_task_synchronously(cluster_task, nullptr);
}

[[nodiscard]] bool CollisionModel::open_model()
{
    m_is_model_open = Core::Device::Cluster::self().is_cluster_open() && !ptq_int8CNN_Construct();
    return m_is_model_open;
}

void CollisionModel::close_model()
{
    ptq_int8CNN_Destruct();
    m_is_model_open = false;
#ifdef BENCHMARKING_MODEL
    unsigned int TotalCycles = 0, TotalOper = 0;
    printf("\n");
    printf("\n");
    for (unsigned int i = 0; i < (sizeof(AT_GraphPerf) / sizeof(unsigned int)); i++) {
        printf("%45s: Cycles: %10u, Operations: %10u, Operations/Cycle: %f\n", AT_GraphNodeNames[i], AT_GraphPerf[i], AT_GraphOperInfosNames[i], ((float)AT_GraphOperInfosNames[i]) / AT_GraphPerf[i]);
        TotalCycles += AT_GraphPerf[i];
        TotalOper += AT_GraphOperInfosNames[i];
    }
    printf("\n");
    printf("%45s: Cycles: %10u, Operations: %10u, Operations/Cycle: %f\n", "Total", TotalCycles, TotalOper, ((float)TotalOper) / TotalCycles);
    printf("\n");
#endif // BENCHMARKING_MODEL
}

CollisionModel::~CollisionModel()
{
    if (m_is_model_open)
        close_model();
}

}

extern "C" AT_HYPERFLASH_FS_EXT_ADDR_TYPE volatile ptq_int8_L3_Flash = 0;
extern "C" volatile unsigned int __L3_Read, __L3_Write, __L2_Read, __L2_Write;