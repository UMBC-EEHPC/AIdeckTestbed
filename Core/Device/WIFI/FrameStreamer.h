#pragma once

#include <Core/Support/gap_sdk.h>
#include <Core/Support/Singleton.h>
#include <Core/Containers/HeapVector.h>
#include <Core/Device/Camera/Camera.h>
#include "WIFI.h"

namespace Core::Device {

class FrameStreamer {
    SINGLETON_CLASS_WITH_ARGS(FrameStreamer, WIFI& wifi, Camera& camera, int width, int height)
    public:
        bool send_frame(etl::vector_ext<uint8_t>& frame_data);
    private:
        frame_streamer_conf m_config;
        frame_streamer_t* m_frame_streamer_meta;
        int m_width;
        int m_height;
};

}
