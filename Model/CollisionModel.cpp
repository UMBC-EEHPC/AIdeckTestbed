#include "CollisionModel.h"

#define CAM_WIDTH     324
#define CAM_HEIGHT    244

unsigned int __L3_Read, __L3_Write, __L2_Read, __L2_Write;

AT_HYPERFLASH_FS_EXT_ADDR_TYPE ptq_int8_L3_Flash = 0;

PI_L2 uint8_t ResOut;
PI_L2 uint8_t *Img_In;

static void cluster(void* arg) {
#ifdef PERF
	gap_cl_starttimer();
	gap_cl_resethwtimer();
#endif
	ptq_int8CNN(Img_In, &ResOut);

	printf("Value is: %u\n", ResOut);
}

namespace Model {

CollisionModel::CollisionModel() : Kernel(0, STACK_SIZE, SLAVE_STACK_SIZE, cluster, nullptr) {
    assert_gap8(Core::Device::Cluster::self().is_cluster_open())
    assert_gap8(!ptq_int8CNN_Construct());

    Img_In = static_cast<uint8_t*>(
        Core::Heap::L2Heap::self().allocate((CAM_WIDTH*CAM_HEIGHT)*sizeof(uint8_t))
    );
    assert_gap8(Img_In != nullptr);
}

void CollisionModel::close_model() {
    ptq_int8CNN_Destruct();
#ifdef PERF
    unsigned int TotalCycles = 0, TotalOper = 0;
    printf("\n");
    for (int i=0; i<(sizeof(AT_GraphPerf)/sizeof(unsigned int)); i++) {
        printf("%45s: Cycles: %10d, Operations: %10d, Operations/Cycle: %f\n", AT_GraphNodeNames[i], AT_GraphPerf[i], AT_GraphOperInfosNames[i], ((float) AT_GraphOperInfosNames[i])/ AT_GraphPerf[i]);
        TotalCycles += AT_GraphPerf[i]; TotalOper += AT_GraphOperInfosNames[i];
    }
    printf("\n");
    printf(" | %7d | %7d | %7d | %8d | %7d |", pi_perf_read(PI_PERF_INSTR), pi_perf_read(PI_PERF_ACTIVE_CYCLES), pi_perf_read(PI_PERF_TCDM_CONT), pi_perf_read(PI_PERF_LD_STALL), pi_perf_read(PI_PERF_IMISS));
    printf("\n");
#endif
}

}