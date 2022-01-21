#pragma once

#include <Benchmarks.h>
#include <Core/Support/Kernel.h>
#include <Core/Support/Assertions.h>
#include <Core/Device/Cluster/Cluster.h>
#include <etl/vector.h>

extern "C" {

extern int ptq_int8CNN_Construct();
extern int ptq_int8CNN_Destruct();
extern int ptq_int8CNN(unsigned char * __restrict__ Input_1, signed char * __restrict__ Output_1);
extern void ResizeImage(unsigned char * In, unsigned char * Out);
extern unsigned int AT_GraphPerf[16];
extern char * AT_GraphNodeNames[16];
extern unsigned int AT_GraphOperInfosNames[16];

}

namespace Model {

class CollisionModel final : public Core::Support::Kernel {
	public:
		CollisionModel(etl::vector_ext<uint8_t>& frame_data, etl::vector_ext<uint8_t>& frame_resized);

		CollisionModel(CollisionModel const&) = delete;
        CollisionModel& operator=(CollisionModel const&) = delete;

		[[nodiscard]] bool open_model();
		void close_model();

		~CollisionModel();
	private:
		bool m_is_model_open;
};

}