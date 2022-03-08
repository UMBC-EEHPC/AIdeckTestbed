#include "CollisionModel.h"

extern "C" L1_CL_MEM AT_L1_POINTER ptq_int8_L1_Memory;
extern "C" L2_MEM AT_L2_POINTER ptq_int8_L2_Memory;

extern "C" L1_CL_MEM AT_L1_POINTER Resize_L1_Memory;
extern "C" L2_MEM AT_L2_POINTER Resize_L2_Memory;

extern uint8_t g_net_decision;

using etl::vector_ext;

namespace Model {

PI_L2 uint8_t ResOut;
PI_L2 uint8_t* Img_In;
PI_L2 uint8_t* Img_Resized;

volatile static void cluster(void* arg)
{
    ptq_int8CNN(Img_In, reinterpret_cast<signed char*>(&ResOut));

    printf("%d\n", ResOut);

    g_net_decision = ResOut;
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
}

CollisionModel::~CollisionModel()
{
    if (m_is_model_open)
        close_model();
}

}

extern "C" AT_HYPERFLASH_FS_EXT_ADDR_TYPE volatile ptq_int8_L3_Flash = 0;
extern "C" volatile unsigned int __L3_Read, __L3_Write, __L2_Read, __L2_Write;