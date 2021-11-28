#include <stdint.h>
#include <Core/Support/gap_sdk.h>
#include <Core/Heap/L2Heap.h>

void program_main() {
	printf("Hello world!\n");
	pmsis_exit(0);
}

extern "C" {
int main() {
	return pmsis_kickoff((void*)program_main);
}
}