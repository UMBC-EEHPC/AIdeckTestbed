#include <stdint.h>
#include <Core/Device/Camera/Camera.h>
#include <Core/Device/Cluster/Cluster.h>
#include <Core/Device/Serial/UART.h>
#include <Core/Device/WIFI/WIFI.h>
#include <Core/Device/WIFI/FrameStreamer.h>
#include <Core/Heap/L2Heap.h>
#include <Core/Heap/L1Heap.h>
#include <Core/Support/gap_sdk.h>
#include <Gapack/Matrix.h>
#include <Model/CollisionModel.h>

void program_main_2() {
	Core::Heap::L2Heap l2heap;
	Core::Heap::L1Heap l1heap;

	auto* uart_or_error = Core::Device::UART::initialize();
	if (!uart_or_error)
		assert_not_reached_gap8();
	auto& uart = *uart_or_error;
	uart.write("Initialized UART\n");

#ifndef __PLATFORM_GVSOC__
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

	auto* frame_streamer_or_error = Core::Device::FrameStreamer::initialize(wifi, camera);
	if (!frame_streamer_or_error)
		assert_not_reached_gap8();
	auto& frame_streamer = *frame_streamer_or_error;
	printf("Initialized frame streamer\n");
#endif

	auto* cluster_or_error = Core::Device::Cluster::initialize();
	if (!cluster_or_error)
		assert_not_reached_gap8();
	auto& cluster = *cluster_or_error;
	printf("Initialized cluster\n");

	assert_gap8(cluster.open_cluster());
	Model::CollisionModel cm;
	assert_gap8(cluster.submit_kernel_synchronously(cm));
	assert_gap8(cluster.close_cluster());

#if 0
	auto frame_buffer = Core::Containers::create_vector_on_heap<char, Core::Heap::L2Heap>(
		camera.get_image_width() * camera.get_image_height()
	);
	printf("Allocated frame buffer\n");
	
	Gapack::Matrix matrix({
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	});
	matrix.print();

	while (true) {
		camera.capture_image(frame_buffer);
		frame_streamer.send_frame(frame_buffer);
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