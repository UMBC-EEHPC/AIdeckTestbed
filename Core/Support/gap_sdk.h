#pragma once

extern "C" {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wregister"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include <pmsis.h>
#include <bsp/transport/nina_w10.h>
#include <bsp/camera/himax.h>
#include <tools/frame_streamer.h>
#include <bsp/bsp.h>
#include "Gap.h"
#include "pulp.h"
#include "rt/rt_api.h"
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
}