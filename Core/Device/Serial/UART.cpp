#include "UART.h"

using namespace etl;

namespace Core::Device {
    
static UART* g_uart = nullptr;

[[nodiscard]] UART* UART::initialize() {
    if (g_uart)
        return nullptr;

    if (!(g_uart = create_singleton_l2<UART>()))
        return nullptr;
    
    pi_uart_conf_init(&(g_uart->m_config));

    g_uart->m_config.enable_tx = 1;
	g_uart->m_config.enable_rx = 0;
    g_uart->m_config.baudrate_bps = 9600;
    
    pi_open_from_conf(&(g_uart->m_uart), &(g_uart->m_config));

    if (!(g_uart->m_buffer = static_cast<char*>(Core::Heap::L2Heap::self().allocate(MAX_BUFFER_LEN))))
        return nullptr;

    if (pi_uart_open(&(g_uart->m_uart)))
        return nullptr;

    return g_uart;
}

UART& UART::self() { 
    return *g_uart; 
}

int UART::write(char const* string, ...) {
    va_list va;
    va_start(va, string);
    int len = vsnprintf(m_buffer, MAX_BUFFER_LEN, string, va);
    va_end(va);

    MEMORY_BARRIER()

    if (len < 0)
        return len;
    
    if (pi_uart_write(&m_uart, m_buffer, len))
        printf("\nFailed while writing %s:\n", m_buffer);

    return 0;
}

UART::~UART() {
    pi_uart_close(&m_uart);
    Core::Heap::L2Heap::self().deallocate(g_uart, sizeof(UART));
    g_uart = nullptr;
}

}