#pragma once

extern "C" L1_CL_MEM AT_L1_POINTER ptq_int8_L1_Memory;
extern "C" L2_MEM AT_L2_POINTER ptq_int8_L2_Memory;

extern "C" L1_CL_MEM AT_L1_POINTER Resize_L1_Memory;
extern "C" L2_MEM AT_L2_POINTER Resize_L2_Memory;

extern "C" {

extern int ptq_int8CNN_Construct();
extern int ptq_int8CNN_Destruct();
extern int ptq_int8CNN(unsigned char* __restrict__ Input_1, signed char* __restrict__ Output_1);
extern void ResizeImage(unsigned char* In, unsigned char* Out);
extern unsigned int AT_GraphPerf[16];
extern char* AT_GraphNodeNames[16];
extern unsigned int AT_GraphOperInfosNames[16];
}
