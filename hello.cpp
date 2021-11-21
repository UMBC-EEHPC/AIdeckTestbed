extern "C" {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wregister"
#include <stdio.h>
#include <stdint.h>
#include <pmsis.h>
#pragma GCC diagnostic pop
}

/* All data transferred between peripherals and 
 * the processor must be stored in L2 memory:
 * https://greenwaves-technologies.com/manuals/BUILD/PMSIS_API/html/group__GAP8__INFO.html
 */
PI_L2 uint8_t value;

void hello_uart()
{
	struct pi_uart_conf config;
	struct pi_device uart;

	value = 123;

	/*
	 * Create a UART config struct, layout is described here:
	 * https://greenwaves-technologies.com/manuals/BUILD/PMSIS_API/html/structpi__uart__conf.html
	 */
	pi_uart_conf_init(&config);

	// We're only planning on transmitting.
	config.enable_tx = 1;
	config.enable_rx = 0;

	// Silicon Graphics hardware tends to default to 9600 baud,
	// so why not use it here as well?
	config.baudrate_bps = 9600;

	// Open UART device.
	pi_open_from_conf(&uart, &config);

	// Fingers crossed!
	printf("Opening UART!\n"); 
	if (pi_uart_open(&uart)) {
		printf("Failed to open UART.\n");
		pmsis_exit(-1);
	}

	// We're ready, let's write.
	printf("Writing %c to UART...\n", value);
	pi_uart_write_byte(&uart, &value);

	// Free up UART resources.
	pi_uart_close(&uart);

	printf("Exiting!\n");
	pmsis_exit(0);
}

int main() 
{
	/* 
	 * GAP8 devices require this function in order to start up
	 * required peripherals and kernel features:
	 * https://greenwaves-technologies.com/manuals/BUILD/PMSIS_API/html/group__Task.html
	 */
	return pmsis_kickoff((void*)hello_uart);
}