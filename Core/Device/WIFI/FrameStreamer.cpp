#include "FrameStreamer.h"

using namespace etl;

namespace Core::Device {

static FrameStreamer* g_frame_streamer = nullptr;
static pi_task_t frame_streamer_callback_task;
static char* g_streamer_name = "FrameStreamer";

/*
 * Unfortunately there's no way to pass a lambda directly
 * as a callback, so we have to provide a C wrapper
 */
void frame_streamer_c_callback(void* arg)
{
    delegate<void(void)>* callback = reinterpret_cast<delegate<void(void)>*>(arg);
    (*callback)();
}

[[nodiscard]] FrameStreamer* FrameStreamer::initialize(WIFI& wifi, Camera& camera, int width, int height)
{
    if (g_frame_streamer)
        return nullptr;

    if (!(g_frame_streamer = create_singleton_l2<FrameStreamer>()))
        return nullptr;

    frame_streamer_conf_init(&(g_frame_streamer->m_config));

    g_frame_streamer->m_config.transport = &(wifi.m_wifi_device);
    g_frame_streamer->m_config.format = FRAME_STREAMER_FORMAT_JPEG;
    g_frame_streamer->m_config.width = width;
    g_frame_streamer->m_config.height = height;
    g_frame_streamer->m_config.depth = 1;
    g_frame_streamer->m_config.name = g_streamer_name;
    g_frame_streamer->m_width = width;
    g_frame_streamer->m_height = height;

    if (!(g_frame_streamer->m_frame_streamer_meta = frame_streamer_open(&(g_frame_streamer->m_config))))
        return nullptr;

    pi_buffer_set_format(&g_frame_streamer->m_buffer, width, height, 1, PI_BUFFER_FORMAT_GRAY);

    return g_frame_streamer;
}

FrameStreamer& FrameStreamer::self()
{
    return *g_frame_streamer;
}

bool FrameStreamer::send_frame(vector_ext<uint8_t>& frame_data)
{
    pi_buffer_t buffer;

    pi_buffer_init(&m_buffer, PI_BUFFER_TYPE_L2, frame_data.data());

    if (frame_streamer_send(m_frame_streamer_meta, &buffer))
        return false;
    return true;
}

pi_task_t* FrameStreamer::send_frame_async(vector_ext<uint8_t>& frame_data, delegate<void(void)> callback)
{
    pi_task_callback(&frame_streamer_callback_task, frame_streamer_c_callback, reinterpret_cast<void*>(&callback));

    pi_buffer_init(&m_buffer, PI_BUFFER_TYPE_L2, frame_data.data());

    if (frame_streamer_send_async(m_frame_streamer_meta, &m_buffer, &frame_streamer_callback_task))
        return nullptr;
    return &frame_streamer_callback_task;
}

}
