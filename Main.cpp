#include <stdint.h>
#include <Core/Support/gap_sdk.h>
#include <Core/Heap/L2Heap.h>
#include <Core/Heap/L1Heap.h>
#include <Gapack/Matrix.h>

void program_main() {
	volatile Core::Heap::L2Heap l2heap;
	volatile Core::Heap::L1Heap l1heap;

	auto* uart_or_error = Core::Device::UART::initialize();
	if (!uart_or_error)
		assert_not_reached_gap8();
	auto& uart = *uart_or_error;
	uart.write("Initialized UART\n");
	
	Gapack::Matrix matrix({
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	});
	matrix.print();
	printf("Finished execution\n");
	pmsis_exit(0);
}

int main() {
	return pmsis_kickoff((void*)program_main);
}