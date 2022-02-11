#pragma once

#include <Core/Support/Singleton.h>
#include <Core/Support/gap_sdk.h>

namespace Core::Device {

class Timer {
public:
    Timer();

    void reset_timer();
    [[nodiscard]] unsigned int get_time_us();
    [[nodiscard]] unsigned int get_elapsed_time_us();

    ~Timer() = default;

private:
    uint32_t m_starting_time;
};

}