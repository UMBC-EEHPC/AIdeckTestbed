#include <stdint.h>
#include <Core/Support/gap_sdk.h>
#include <Core/Heap/L2Heap.h>
#include <Core/Heap/L1Heap.h>
#include <Core/Device/Camera/Camera.h>
#include <Core/Device/WIFI/WIFI.h>
#include <Core/Device/WIFI/FrameStreamer.h>
#include <Core/Device/Serial/UART.h>
#include <Gapack/Matrix.h>

void program_main() {
	volatile Core::Heap::L2Heap l2heap;
	volatile Core::Heap::L1Heap l1heap;

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

	auto* frame_streamer_or_error = Core::Device::FrameStreamer::initialize(wifi, camera);
	if (!frame_streamer_or_error)
		assert_not_reached_gap8();
	auto& frame_streamer = *frame_streamer_or_error;
	printf("Initialized frame streamer\n");

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

	printf("Finished execution\n");
	pmsis_exit(0);
}

int main() {
	return pmsis_kickoff((void*)program_main);
}