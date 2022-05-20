#include "Timer.h"

namespace Core::Device {

Timer::Timer()
{
    m_starting_time = rt_time_get_us();
}

void Timer::reset_timer()
{
    m_starting_time = rt_time_get_us();
}

[[nodiscard]] unsigned int Timer::get_time_us()
{
    return rt_time_get_us();
}

[[nodiscard]] unsigned int Timer::get_elapsed_time_us()
{
    return rt_time_get_us() - m_starting_time;
}

}