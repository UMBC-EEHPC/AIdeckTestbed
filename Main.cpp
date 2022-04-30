#include <Benchmarks.h>
#include <Core/Device/CPU/CPU.h>
#include <Core/Device/Camera/Camera.h>
#include <Core/Device/Cluster/Cluster.h>
#include <Core/Device/Serial/UART.h>
#include <Core/Device/Timer/Timer.h>
#include <Core/Device/WIFI/FrameStreamer.h>
#include <Core/Device/WIFI/WIFI.h>
#include <Core/Heap/L1Heap.h>
#include <Core/Heap/L2Heap.h>
#include <Core/Support/gap_sdk.h>
#include <Model/CollisionModel.h>
#include <stdint.h>

uint8_t g_net_decision = 0;

void program_main_2()
{
    printf("Initializing devices\n");
    Core::Device::CPU::set_fabric_voltage(1.2);
    Core::Device::CPU::set_cluster_voltage(1.2);
    Core::Device::CPU::set_fabric_frequency(250);
    Core::Device::CPU::set_cluster_frequency(175);
    Core::Heap::L2Heap l2heap;
    Core::Heap::L1Heap l1heap;
    Core::Device::Timer timer;

    auto* uart_or_error = Core::Device::UART::initialize();
    if (!uart_or_error)
        assert_not_reached_gap8();
    auto& uart = *uart_or_error;
    printf("Initialized UART\n");

    auto* camera_or_error = Core::Device::Camera::initialize();
    if (!camera_or_error)
        assert_not_reached_gap8();
    auto& camera = *camera_or_error;
    printf("Initialized camera\n");

    auto camera_frame_buffer = Core::Containers::create_vector_on_heap<uint8_t, Core::Heap::L2Heap>(
        camera.get_image_width() * camera.get_image_height());
    printf("Allocated camera output frame buffer\n");

    auto model_frame_buffer = Core::Containers::create_vector_on_heap<uint8_t, Core::Heap::L2Heap>(
        80 * 60);
    printf("Allocated neural network input frame buffer\n");

    auto* cluster_or_error = Core::Device::Cluster::initialize();
    if (!cluster_or_error)
        assert_not_reached_gap8();
    auto& cluster = *cluster_or_error;
    printf("Initialized cluster\n");
    assert_gap8(cluster.open_cluster());

    Model::CollisionModel cm(camera_frame_buffer, model_frame_buffer);

    while (true) {
        camera.stream(camera_frame_buffer, [&]() {
            assert_gap8(cluster.submit_kernel_synchronously(cm));
            uart.writeChar(g_net_decision);
        });
    }

    l2heap.deallocate(model_frame_buffer.data(), 80 * 60);
    l2heap.deallocate(camera_frame_buffer.data(), 324 * 244);
    assert_gap8(cluster.close_cluster());
}

/*
 * Didn't actually realize it at first, but pmsis_exit()
 * stops destructors that free any devices from working
 * properly because it will execute before any other destructors
 * Thus, move pmsis_exit into its own function
 */
void program_main()
{
    program_main_2();
    printf("Finished execution\n");
    pmsis_exit(0);
}

int main()
{
    return pmsis_kickoff((void*)program_main);
}