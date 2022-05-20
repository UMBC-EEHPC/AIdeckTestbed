#pragma once

#include <Core/Heap/L2Heap.h>
#include <Core/Support/Singleton.h>
#include <Core/Support/gap_sdk.h>
#include <Core/Sync/Sync.h>
#include <etl/optional.h>

#define MAX_BUFFER_LEN 1000

extern "C" {

extern int vsnprintf(char* s, size_t n, const char* format, va_list arg);
}

namespace Core::Device {

class UART {
    SINGLETON_CLASS(UART)
public:
    int write(char const* string, ...);

    ~UART();

private:
    char* m_buffer;
    pi_device m_uart;
    pi_uart_conf m_config;
};

}