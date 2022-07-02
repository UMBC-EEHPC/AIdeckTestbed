#pragma once

#include <Constants.h>
#include <Core/Containers/HeapVector.h>
#include <Core/Support/Singleton.h>
#include <Core/Support/etl_includes.h>
#include <Core/Support/gap_sdk.h>

namespace Core::Device {

class Camera {
    SINGLETON_CLASS(Camera)
public:
    void capture_image(etl::vector_ext<uint8_t>& buffer);
    void stream(etl::vector_ext<uint8_t>& buffer, etl::delegate<void(void)> callback);

    const int get_image_width() { return CAMERA_WIDTH; }
    const int get_image_height() { return CAMERA_HEIGHT; }

private:
    pi_himax_conf m_config;
};

}
