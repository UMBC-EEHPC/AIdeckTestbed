#include "gap_sdk.h"

extern void project_main();

void intermediate_main()
{
    project_main();
    printf("Finished execution\n");
    pmsis_exit(0);
}

int main()
{
    return pmsis_kickoff(reinterpret_cast<void*>(intermediate_main));
}