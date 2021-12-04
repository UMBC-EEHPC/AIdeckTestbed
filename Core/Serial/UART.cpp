#include "UART.h"

namespace Core::Serial {
    
static PI_L1 UART* g_uart = nullptr;

UART::UART() {
    assert_gap8(g_uart);

    pi_uart_conf_init(&config);

    config.enable_tx = 1;
	config.enable_rx = 0;
    config.baudrate_bps = 9600;
    
    pi_open_from_conf(&uart, &config);

    if (pi_uart_open(&uart)) {
		printf("Failed to open UART.\n");
		pmsis_exit(-1);
	}

    m_buffer = static_cast<char*>(Core::Heap::L2Heap::self().allocate(MAX_BUFFER_LEN));

    g_uart = this;
}

int UART::write(char const* string, ...) {
    va_list va;
    va_start(va, string);
    int len = vsnprintf(m_buffer, MAX_BUFFER_LEN, string, va);
    va_end(va);

    MEMORY_BARRIER()

    if (len < 0)
        return len;
    
    if (pi_uart_write(&uart, m_buffer, len))
        printf("\nFailed while writing %s:\n", m_buffer);

    return 0;
}

UART& UART::self() { 
    return *g_uart; 
}

UART::~UART() {
    pi_uart_close(&uart);
}

}