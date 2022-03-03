
#ifndef __MNIST_H__
#define __MNIST_H__

#define __PREFIX(x) ptq_int8##x

#include "Gap.h"

#ifdef __EMUL__
#    include <fcntl.h>
#    include <string.h>
#    include <sys/param.h>
#    include <sys/stat.h>
#    include <sys/types.h>
#    include <unistd.h>
extern AT_HYPERFLASH_FS_EXT_ADDR_TYPE ptq_int8_L3_Flash;
#endif // __EMUL__

#if defined(USE_HYPER)
extern AT_HYPERFLASH_FS_EXT_ADDR_TYPE ptq_int8_L3_Flash;
#elif defined(USE_SPI)
extern AT_QSPIFLASH_FS_EXT_ADDR_TYPE ptq_int8_L3_Flash;
#endif // USE_HYPER

#endif // __MNIST_H__
