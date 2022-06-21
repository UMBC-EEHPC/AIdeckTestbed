/*
 * Copyright (C) 2017 GreenWaves Technologies
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "AutoTilerLib.h"
#include "ResizeGenerator.h"

#include <Constants.h>

int main(int argc, char** argv)
{
    if (TilerParseOptions(argc, argv)) {
        printf("Failed to initialize or incorrect output arguments directory.\n");
        return 1;
    }
    SetInlineMode(ALWAYS_INLINE);
    SetSymbolNames("Resize_L1_Memory", "Resize_L2_Memory");
    SetSymbolDynamics();
    SetKernelOpts(KER_OPT_NONE, KER_OPT_BUFFER_PROMOTE);

    SetUsedFilesNames(0, 1, "ResizeBasicKernels.h");
    SetGeneratedFilesNames("ResizeKernels.c", "ResizeKernels.h");
    LoadResizeLibrary();

#if (CAMERA_WIDTH != MODEL_WIDTH && CAMERA_HEIGHT != MODEL_HEIGHT)
    GenerateResize("ResizeImage", CAMERA_WIDTH, CAMERA_HEIGHT, MODEL_WIDTH, MODEL_HEIGHT);
#else
    GenerateResize("ResizeImage", CAMERA_WIDTH, CAMERA_HEIGHT, 200, 200);
#endif

    GenerateTilingCode();
    return 0;
}