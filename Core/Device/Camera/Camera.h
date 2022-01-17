#pragma once

#include <Core/Support/gap_sdk.h>
#include <Core/Support/Singleton.h>
#include <Core/Containers/HeapVector.h>

namespace Core::Device {

class Camera {
    SINGLETON_CLASS(Camera)
    public:
        void capture_image(etl::vector_ext<uint8_t>& buffer);

        constexpr int get_image_width() { return 324; }
        constexpr int get_image_height() { return 244; }
    private:
        pi_device m_camera_device;
        pi_himax_conf m_config;
};

}
