#pragma once

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
#endif
