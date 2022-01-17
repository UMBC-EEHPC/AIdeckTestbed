#include "CollisionModel.h"

#define CAM_WIDTH     324
#define CAM_HEIGHT    244

extern "C" volatile unsigned int __L3_Read, __L3_Write, __L2_Read, __L2_Write;

extern "C" L1_CL_MEM AT_L1_POINTER ptq_int8_L1_Memory;
extern "C" L2_MEM AT_L2_POINTER ptq_int8_L2_Memory;

extern "C" L1_CL_MEM AT_L1_POINTER Resize_L1_Memory;
extern "C" L2_MEM AT_L2_POINTER Resize_L2_Memory;

extern "C" AT_HYPERFLASH_FS_EXT_ADDR_TYPE volatile ptq_int8_L3_Flash = 0;

PI_L2 volatile uint8_t ResOut;
PI_L2 volatile uint8_t *Img_In;
PI_L2 volatile uint8_t *Img_Resized;

volatile static void cluster(void* arg) {
    printf("Entered cluster\n");
#ifdef PERF
	gap_cl_starttimer();
	gap_cl_resethwtimer();
#endif
    ResizeImage(Img_In, Img_Resized);
	ptq_int8CNN(Img_Resized, &ResOut);
}

namespace Model {

CollisionModel::CollisionModel(etl::vector_ext<char>& frame_data, etl::vector_ext<char>& frame_resized) : Kernel(0, STACK_SIZE, SLAVE_STACK_SIZE, cluster, nullptr) {
    assert_gap8(Core::Device::Cluster::self().is_cluster_open())
    assert_gap8(!ptq_int8CNN_Construct());

    Img_In = (volatile uint8_t*)frame_data.data();
    assert_gap8(Img_In != nullptr);

    Img_Resized = (volatile uint8_t*)frame_resized.data();
    assert_gap8(Img_Resized != nullptr);

    Resize_L1_Memory = ptq_int8_L1_Memory;
    Resize_L2_Memory = ptq_int8_L2_Memory;
}

void CollisionModel::close_model() {
    ptq_int8CNN_Destruct();
#ifdef PERF
    unsigned int TotalCycles = 0, TotalOper = 0;
    printf("Value is: %u\n", ResOut);
    printf("\n");
    for (int i=0; i<(sizeof(AT_GraphPerf)/sizeof(unsigned int)); i++) {
        printf("%45s: Cycles: %10d, Operations: %10d, Operations/Cycle: %f\n", AT_GraphNodeNames[i], AT_GraphPerf[i], AT_GraphOperInfosNames[i], ((float) AT_GraphOperInfosNames[i])/ AT_GraphPerf[i]);
        TotalCycles += AT_GraphPerf[i]; TotalOper += AT_GraphOperInfosNames[i];
    }
    printf("\n");
    printf("%35s: %10d, Operation: %10d, Operation/Cycle: %f\n", "Total", TotalCycles, TotalOper, ((float) TotalOper)/ TotalCycles);
    printf("\n");
#endif
}

}