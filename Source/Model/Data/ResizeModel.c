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

    GenerateResize("ResizeImage", 324, 244, 80, 60);

    GenerateTilingCode();
    return 0;
}