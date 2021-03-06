#include <Benchmarks.h>
#include <Constants.h>
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

void project_main()
{
    printf("Initializing devices\n");
    Core::Device::CPU::set_fabric_voltage(1.2);
    Core::Device::CPU::set_cluster_voltage(1.2);
    Core::Device::CPU::set_fabric_frequency(250);
    Core::Device::CPU::set_cluster_frequency(175);
    Core::Heap::L2Heap l2heap;
    Core::Heap::L1Heap l1heap;
    Core::Device::Timer timer;

#ifdef BENCHMARKING_POWER
    auto* uart_or_error = Core::Device::UART::initialize();
    if (!uart_or_error)
        assert_not_reached_gap8();
    auto& uart = *uart_or_error;
    printf("Initialized UART\n");

    uart.write("+");
    pi_time_wait_us(1000000);
    uart.write("-");
#endif // BENCHMARKING_POWER

#ifdef BENCHMARKING_WIFI_STREAMER
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

    auto* frame_streamer_or_error = Core::Device::FrameStreamer::initialize(wifi, camera, MODEL_WIDTH, MODEL_HEIGHT);
    if (!frame_streamer_or_error)
        assert_not_reached_gap8();
    auto& frame_streamer = *frame_streamer_or_error;
    printf("Initialized frame streamer\n");

    auto camera_frame_buffer = Core::Containers::create_vector_on_heap<uint8_t, Core::Heap::L2Heap>(
        camera.get_image_width() * camera.get_image_height());
#else
    auto camera_frame_buffer = Core::Containers::create_vector_on_heap<uint8_t, Core::Heap::L2Heap>(
        CAMERA_WIDTH * CAMERA_HEIGHT);
#endif // BENCHMARKING_WIFI_STREAMER
    printf("Allocated camera output frame buffer\n");

    auto model_frame_buffer = Core::Containers::create_vector_on_heap<uint8_t, Core::Heap::L2Heap>(
        MODEL_WIDTH * MODEL_HEIGHT);
    printf("Allocated neural network input frame buffer\n");

    auto* cluster_or_error = Core::Device::Cluster::initialize();
    if (!cluster_or_error)
        assert_not_reached_gap8();
    auto& cluster = *cluster_or_error;
    printf("Initialized cluster\n");
    assert_gap8(cluster.open_cluster());

    Model::CollisionModel cm(camera_frame_buffer, model_frame_buffer, cluster);

#ifdef BENCHMARKING_MODEL
#    ifdef BENCHMARKING_POWER
    uart.write("+");
#    endif // BENCHMARKING_POWER
    timer.reset_timer();
    assert_gap8(cm.run_model());
    unsigned int total_time = timer.get_elapsed_time_us();
#    ifdef BENCHMARKING_POWER
    uart.write("-");
#    endif // BENCHMARKING_POWER
    cm.close_model();
    printf("Elapsed Time: %u uSec, FC Frequency as %u MHz, CL Frequency = %u MHz, PERIIPH Frequency = %u\n", total_time, Core::Device::CPU::get_fabric_frequency(), Core::Device::CPU::get_cluster_frequency(), Core::Device::CPU::get_peripheral_frequency());
#endif // BENCHMARKING_MODEL

#if defined(BENCHMARKING_WIFI_STREAMER)
    pi_task_t* streamer_task;
    while (true) {
#endif // BENCHMARKING_WIFI_STREAMER

#if defined(BENCHMARKING_WIFI_STREAMER)
        camera.stream(camera_frame_buffer, [&]() {
            assert_gap8(cm.run_model());
            assert_gap8(streamer_task = frame_streamer.send_frame_async(model_frame_buffer, [] {}));
            pi_task_wait_on(streamer_task);
        });
    }
#endif // BENCHMARKING_WIFI_STREAMER

    l2heap.deallocate(model_frame_buffer.data(), MODEL_WIDTH * MODEL_HEIGHT);
    l2heap.deallocate(camera_frame_buffer.data(), CAMERA_WIDTH * CAMERA_HEIGHT);
    assert_gap8(cluster.close_cluster());
}