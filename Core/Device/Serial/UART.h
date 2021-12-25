#pragma once

#include <Core/Support/gap_sdk.h>
#include <Core/Heap/L2Heap.h>
#include <Core/Sync/Sync.h>

#define MAX_BUFFER_LEN 1000

extern "C" {

extern int vsnprintf (char * s, size_t n, const char * format, va_list arg );

}

namespace Core::Device::Serial {

class UART {
    public:
        UART();

        int write(char const* string, ...);

        static UART& self();
        ~UART();
    private:
        char* m_buffer;
        struct pi_device uart;
        struct pi_uart_conf config;
};

}