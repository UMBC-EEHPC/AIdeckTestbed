#pragma once

#ifdef __PLATFORM_GVSOC__
#    define BENCHMARKING_MODEL
#else
//#    define BENCHMARKING_WIFI_STREAMER

//#    define BENCHMARKING_MODEL
//#    define BENCHMARKING_POWER

#    ifdef BENCHMARKING_WIFI_STREAMER
#        define BENCHMARKING_POWER
#    endif // BENCHMARKING_WIFI_STREAMER
#endif     // __PLATFORM_GVSOC__