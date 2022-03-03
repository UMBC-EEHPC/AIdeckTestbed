#include "CollisionModel.h"

extern "C" L1_CL_MEM AT_L1_POINTER ptq_int8_L1_Memory;
extern "C" L2_MEM AT_L2_POINTER ptq_int8_L2_Memory;

extern "C" L1_CL_MEM AT_L1_POINTER Resize_L1_Memory;
extern "C" L2_MEM AT_L2_POINTER Resize_L2_Memory;

using etl::vector_ext;

namespace Model {

PI_L2 uint8_t ResOut;
PI_L2 uint8_t* Img_In;
PI_L2 uint8_t* Img_Resized;

volatile static void cluster(void* arg)
{
#ifdef BENCHMARKING_MODEL
    gap_cl_starttimer();
    gap_cl_resethwtimer();
#endif // BENCHMARKING_MODEL

#if defined(BENCHMARKING_POWER) && !defined(BENCHMARKING_WIFI_STREAMER)
    while (true) {
#endif // defined(BENCHMARKING_POWER) && !defined(BENCHMARKING_WIFI_STREAMER)

#ifdef BENCHMARKING_WIFI_STREAMER
        ResizeImage(Img_In, Img_Resized);
#endif

#ifdef BENCHMARKING_MODEL
        ptq_int8CNN(Img_Resized, reinterpret_cast<signed char*>(&ResOut));
#endif // BENCHMARKING_MODEL
#if defined(BENCHMARKING_POWER) && !defined(BENCHMARKING_WIFI_STREAMER)
    }
#endif // defined(BENCHMARKING_POWER) && !defined(BENCHMARKING_WIFI_STREAMER)
}

CollisionModel::CollisionModel(vector_ext<uint8_t>& frame_data, vector_ext<uint8_t>& frame_resized)
    : Kernel(0, STACK_SIZE, SLAVE_STACK_SIZE, cluster, nullptr)
{
    assert_gap8(open_model());

    Img_In = frame_data.data();
    Img_Resized = frame_resized.data();

    Resize_L1_Memory = ptq_int8_L1_Memory;
    Resize_L2_Memory = ptq_int8_L2_Memory;

    m_is_model_open = true;
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
    printf("Value is: %u\n", ResOut);
    printf("\n");
    for (int i = 0; i < (sizeof(AT_GraphPerf) / sizeof(unsigned int)); i++) {
        //printf("%45s: Cycles: %10d, Operations: %10d, Operations/Cycle: %f\n", AT_GraphNodeNames[i], AT_GraphPerf[i], AT_GraphOperInfosNames[i], ((float) AT_GraphOperInfosNames[i])/ AT_GraphPerf[i]);
        TotalCycles += AT_GraphPerf[i];
        TotalOper += AT_GraphOperInfosNames[i];
    }
    printf("\n");
    printf("%35s: %10u, Operation: %10u, Operation/Cycle: %f\n", "Total", TotalCycles, TotalOper, ((float)TotalOper) / TotalCycles);
    printf("\n");
#endif
}

CollisionModel::~CollisionModel()
{
    if (m_is_model_open)
        close_model();
}

}

extern "C" AT_HYPERFLASH_FS_EXT_ADDR_TYPE volatile ptq_int8_L3_Flash = 0;
extern "C" volatile unsigned int __L3_Read, __L3_Write, __L2_Read, __L2_Write;