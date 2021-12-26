#include "FrameStreamer.h"

using namespace etl;

namespace Core::Device {

static FrameStreamer* g_frame_streamer = nullptr;
static char* g_streamer_name = "FrameStreamer";

[[nodiscard]] FrameStreamer* FrameStreamer::initialize(WIFI& wifi, Camera& camera) {
    if (g_frame_streamer)
        return nullptr;

    if (!(g_frame_streamer = create_singleton_l2<FrameStreamer>()))
        return nullptr;

    frame_streamer_conf_init(&(g_frame_streamer->m_config));

    g_frame_streamer->m_config.transport = &(wifi.m_wifi_device);
    g_frame_streamer->m_config.format = FRAME_STREAMER_FORMAT_JPEG;
    g_frame_streamer->m_config.width = camera.get_image_width();
    g_frame_streamer->m_config.height = camera.get_image_height();
    g_frame_streamer->m_config.depth = 1;
    g_frame_streamer->m_config.name = g_streamer_name;

    if (!(g_frame_streamer->m_frame_streamer_meta = frame_streamer_open(&(g_frame_streamer->m_config))))
        return nullptr;

    return g_frame_streamer;
}

FrameStreamer& FrameStreamer::self() {
    return *g_frame_streamer;
}

bool FrameStreamer::send_frame(vector_ext<char>& frame_data) {
    pi_buffer_t buffer;
    pi_buffer_init(&buffer, PI_BUFFER_TYPE_L2, frame_data.data());
    pi_buffer_set_format(
        &buffer, 
        Core::Device::Camera::self().get_image_width(), 
        Core::Device::Camera::self().get_image_height(), 
        1, 
        PI_BUFFER_FORMAT_GRAY
    );

    if (frame_streamer_send(m_frame_streamer_meta, &buffer))
        return false;
    return true;
}

}
