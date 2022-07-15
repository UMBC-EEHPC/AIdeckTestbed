#pragma once

#include "WIFI.h"
#include <Core/Containers/HeapVector.h>
#include <Core/Device/Camera/Camera.h>
#include <Core/Support/Singleton.h>
#include <Core/Support/gap_sdk.h>

namespace Core::Device {

class FrameStreamer {
    SINGLETON_CLASS_WITH_ARGS(FrameStreamer, WIFI& wifi, Camera& camera, int width, int height)
public:
    bool send_frame(etl::vector_ext<uint8_t>& frame_data);
    pi_task_t* send_frame_async(etl::vector_ext<uint8_t>& frame_data, etl::delegate<void(void)> callback);

private:
    int m_width;
    int m_height;
};

}
