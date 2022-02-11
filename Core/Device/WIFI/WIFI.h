#pragma once

#include "WIFISettings.h"
#include <Core/Containers/HeapVector.h>
#include <Core/Support/Singleton.h>
#include <Core/Support/gap_sdk.h>

namespace Core::Device {

class FrameStreamer;

class WIFI {
    SINGLETON_CLASS(WIFI)
public:
private:
    pi_device m_wifi_device;
    pi_nina_w10_conf m_config;

    friend FrameStreamer;
};

}