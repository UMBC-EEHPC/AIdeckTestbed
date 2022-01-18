#include <stdint.h>
#include <Core/Device/Camera/Camera.h>
#include <Core/Device/Cluster/Cluster.h>
#include <Core/Device/CPU/CPU.h>
#include <Core/Device/Serial/UART.h>
#include <Core/Device/Timer/Timer.h>
#include <Core/Device/WIFI/WIFI.h>
#include <Core/Device/WIFI/FrameStreamer.h>
#include <Core/Heap/L2Heap.h>
#include <Core/Heap/L1Heap.h>
#include <Core/Support/gap_sdk.h>
#include <Gapack/Matrix.h>
#include <Model/CollisionModel.h>

void program_main_2() {
	printf("Initializing devices\n");
	Core::Heap::L2Heap l2heap;
	Core::Heap::L1Heap l1heap;

#ifndef __PLATFORM_GVSOC__
	auto* uart_or_error = Core::Device::UART::initialize();
	if (!uart_or_error)
		assert_not_reached_gap8();
	auto& uart = *uart_or_error;
	uart.write("Initialized UART\n");
	
	auto* camera_or_error = Core::Device::Camera::initialize();
	if (!camera_or_error)
		assert_not_reached_gap8();
	auto& camera = *camera_or_error;
	printf("Initialized camera\n");

	auto* wifi_or_error = Core::Device::WIFI::initialize();
	if (!wifi_or_error)
		assert_not_reached_gap8();
	auto& wifi = *wifi_or_error;
	printf("Initialized WIFI\n");

	auto* frame_streamer_or_error = Core::Device::FrameStreamer::initialize(wifi, camera, 200, 200);
	if (!frame_streamer_or_error)
		assert_not_reached_gap8();
	auto& frame_streamer = *frame_streamer_or_error;
	printf("Initialized frame streamer\n");
#endif

#ifndef __PLATFORM_GVSOC__
	auto camera_frame_buffer = Core::Containers::create_vector_on_heap<uint8_t, Core::Heap::L2Heap>(
		camera.get_image_width() * camera.get_image_height()
	);
#else
	auto camera_frame_buffer = Core::Containers::create_vector_on_heap<uint8_t, Core::Heap::L2Heap>(
		324*244
	);
#endif
	printf("Allocated camera output frame buffer\n");
	auto model_frame_buffer = Core::Containers::create_vector_on_heap<uint8_t, Core::Heap::L2Heap>(
		200 * 200
	);
	printf("Allocated neural network input frame buffer\n");

	auto* cluster_or_error = Core::Device::Cluster::initialize();
	if (!cluster_or_error)
		assert_not_reached_gap8();
	auto& cluster = *cluster_or_error;
	printf("Initialized cluster\n");
	assert_gap8(cluster.open_cluster());

#ifdef __PLATFORM_GVSOC__
	Model::CollisionModel cm(camera_frame_buffer, model_frame_buffer);
	Core::Device::Timer timer;
	timer.reset_timer();
	assert_gap8(cluster.submit_kernel_synchronously(cm));
	unsigned int total_time = timer.get_elapsed_time_us();
	printf("Elapsed Time: %u uSec, FC Frequency as %u MHz, CL Frequency = %u MHz, PERIIPH Frequency = %u\n", total_time, Core::Device::CPU::get_fabric_frequency(), Core::Device::CPU::get_cluster_frequency(), Core::Device::CPU::get_peripheral_frequency());
	cm.close_model();
	assert_gap8(cluster.close_cluster());
#endif

#ifndef __PLATFORM_GVSOC__	
	Gapack::Matrix matrix({
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	});
	matrix.print();

	Model::CollisionModel cm(camera_frame_buffer, model_frame_buffer);
	assert_gap8(cluster.submit_kernel_synchronously(cm));

	while (true) {
		camera.capture_image(camera_frame_buffer);
		assert_gap8(cluster.submit_kernel_synchronously(cm));
		frame_streamer.send_frame(model_frame_buffer);
	}
#endif
}

/*
 * Didn't actually realize it at first, but pmsis_exit()
 * stops destructors that free any devices from working
 * properly because it will execute before any other destructors
 * Thus, move pmsis_exit into its own function
 */
void program_main() {
	program_main_2();
	printf("Finished execution\n");
	pmsis_exit(0);
}

int main() {
	return pmsis_kickoff((void*)program_main);
}