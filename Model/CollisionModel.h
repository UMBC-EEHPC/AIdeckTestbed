#pragma once

#include <Core/Support/Kernel.h>
#include <Core/Support/Assertions.h>
#include <Core/Device/Cluster/Cluster.h>

extern "C" {

extern int ptq_int8CNN_Construct();
extern int ptq_int8CNN_Destruct();
extern int ptq_int8CNN(unsigned char * __restrict__ Input_1, signed char * __restrict__ Output_1);
extern unsigned int AT_GraphPerf[16];
extern char * AT_GraphNodeNames[16];
extern unsigned int AT_GraphOperInfosNames[16];

}

namespace Model {

class CollisionModel final : public Core::Support::Kernel {
	public:
		CollisionModel();

		CollisionModel(CollisionModel const&) = delete;
        CollisionModel& operator=(CollisionModel const&) = delete;

		~CollisionModel();
	private:
		
};

}