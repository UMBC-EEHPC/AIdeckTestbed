#include "CollisionModel.h"
#include "CollisionModelGenerated.inc"

using etl::vector_ext;

extern uint8_t g_net_decision;

namespace Model {

PI_L2 static uint8_t* original_image;
PI_L2 static uint8_t* resized_image;

PI_L2 static uint8_t decision;

volatile static void cluster(void* arg)
{
    ptq_int8CNN(original_image, reinterpret_cast<int8_t*>(&decision));
    g_net_decision = decision;
}

CollisionModel::CollisionModel(vector_ext<uint8_t>& frame_data, vector_ext<uint8_t>& frame_resized)
    : Kernel(0, STACK_SIZE, SLAVE_STACK_SIZE, cluster, nullptr)
{
    assert_gap8(open_model());

    original_image = frame_data.data();
    resized_image = frame_resized.data();

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
}

CollisionModel::~CollisionModel()
{
    if (m_is_model_open)
        close_model();
}

}

extern "C" AT_HYPERFLASH_FS_EXT_ADDR_TYPE volatile ptq_int8_L3_Flash = 0;
extern "C" volatile unsigned int __L3_Read, __L3_Write, __L2_Read, __L2_Write;