#include <stdint.h>
#include <Core/Support/gap_sdk.h>
#include <Core/Heap/L2Heap.h>
#include <Gapack/Matrix.h>

void program_main() {
	printf("Hello world!\n");
	
	Core::Heap::L2Heap();
	
	Gapack::Matrix matrix({
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	});
	matrix.print();
	pmsis_exit(0);
}

extern "C" {
int main() {
	return pmsis_kickoff((void*)program_main);
}
}