project(
    'AIdeckTestbed', 
    'c', 
    'cpp',
    version : '1.0',
    default_options : [
        'b_lto=false',
        'b_pch=false',
        'b_staticpic=false',
        'buildtype=release',
        'cpp_rtti=false',
        'cpp_eh=none',
        'debug=false',
        'c_std=gnu99',
        'cpp_std=gnu++17'
    ],
    meson_version : '>=0.60.0'
)

GAP_SDK_Location = 'Toolchain/gap_sdk'
ETL_Location = 'Toolchain/etl/include'
GAP8_CXX_Compiler = meson.get_compiler('cpp', native: false)
GAP8_C_Compiler = meson.get_compiler('c', native: false)

Native_CXX_Compiler = meson.get_compiler('cpp', native: true)
Native_C_Compiler = meson.get_compiler('c', native: true)

GAP8_C_Flags = [
    '-gdwarf-2',
    '-gstrict-dwarf',
    '-march=rv32imcxgap8',
    '-DCONFIG_FLL_MAXDCO_FREQ=900000000',
    '-DUSE_HYPER',
    '-DAT_MODEL_PREFIX=ptq_int8',
    '-DAT_INPUT_HEIGHT=',
    '-DAT_INPUT_WIDTH=',
    '-DAT_INPUT_COLORS=',
    '-DMAIN_APP_STACK_SIZE=6144',
    '-DSLAVE_STACK_SIZE=3072',
    '-DAT_IMAGE=',
    '-DPRINTF_UART',
    '-DCONFIG_FREQUENCY_PERIPH=160000000',
    '-DCONFIG_FREQUENCY_FC=50000000',
    '-DCONFIG_FREQUENCY_CLUSTER=50000000',
    '-DCONFIG_FREQUENCY_SFU=50000000',
    '-DCONFIG_FAST_OSC_FREQUENCY=24576063',
    '-DCONFIG_FREQUENCY_FPGA=50000000',
    '-DCONFIG_MAX_FREQUENCY_PERIPH=0',
    '-DCONFIG_MAX_FREQUENCY_FC=0',
    '-DCONFIG_MAX_FREQUENCY_CLUSTER=0',
    '-DCONFIG_MAX_FREQUENCY_SFU=0',
    '-DPI_LOG_DEFAULT_LEVEL=PI_LOG_TRACE',
    '-DconfigUSE_TIMERS=1',
    '-DINCLUDE_xTimerPendFunctionCall=1',
    '-DCONFIG_FLL_MAXDCO_FREQ=900000000',
    '-fstack-protector-strong',
    '-DCONFIG_AI_DECK',
    '-DRT_FC_STACK_SIZE=2048',
    '-fno-jump-tables',
    '-fno-tree-loop-distribute-patterns',
    '-fno-delete-null-pointer-checks',
    '-fomit-frame-pointer',
    '-fdata-sections',
    '-ffunction-sections',
    '-mchip=gap8',
    '-mPE=8',
    '-mFC=1',
    '-D__riscv__',
    '-D__GAP__',
    '-D__GAP8__',
    '-D__FC_MALLOC_NATIVE__=0',
    '-D__L2_MALLOC_NATIVE__=0',
    '-D__PMSIS_L2_MALLOC_NATIVE__=0',
    '-DCHIP_VERSION=2',
    '-D__USE_TCDM_MALLOC__=1',
    '-DPMSIS_DRIVERS=1',
    '-D__RISCV_ARCH_GAP__=1',
    '-DPREEMPTION',
    '-D__FREERTOS__',
    '-mnativeomp',
    '-DFEATURE_CLUSTER=1'
]

GAP8_CXX_Flags = [
    GAP8_C_Flags,
    '-fpermissive',
    '-fno-exceptions'
]

GAP8_Link_Flags = [
    '-march=rv32imcxgap8',
    '-mPE=8',
    '-mFC=1',
    '-Wl,--as-needed',
    '-Wl,--gc-sections',
    #'-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/link.gap8_rev1.ld',
    '-T' + meson.project_source_root() / GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/src/device/ld/GAP8.ld',
    '-nostartfiles',
    '-nostdlib',
    '-fno-exceptions'
]

Includes = include_directories(
    './Source',
    './Source/Model',
    './Source/Model/Data',
    GAP_SDK_Location / 'rtos/freeRTOS/freertos_kernel/include',
    GAP_SDK_Location / 'rtos/freeRTOS/demos/gwt/config/gap8',
    GAP_SDK_Location / 'rtos/freeRTOS/freertos_kernel/portable/GCC/RI5CY-GAP8',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/include',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/include',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/include/driver',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/libs/include',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/libs/printf',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/include/',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_api/include/',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/include',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/include/cores/TARGET_RISCV_32',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/include/pmsis/implem',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/include/pmsis/targets',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/include',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/camera',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/include',
    GAP_SDK_Location / 'tools/autotiler_v3/Emulation',
    GAP_SDK_Location / 'libs/gap_lib/include',
    GAP_SDK_Location / 'libs/gap_lib/include/gaplib',
    GAP_SDK_Location / 'tools/autotiler_v3/Emulation',
    GAP_SDK_Location / 'tools/autotiler_v3/Autotiler',
    GAP_SDK_Location / 'tools/autotiler_v3/Generators/BilinearResizes',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Libraries',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_fp16',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8',
    ETL_Location
)

Native_C_Flags = []
Native_CXX_Flags = [
    Native_C_Flags
]

GenTile_Includes = include_directories(
    './Source',
    GAP_SDK_Location / 'tools/autotiler_v3/Autotiler',
    GAP_SDK_Location / 'tools/autotiler_v3/Emulation',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Generators',
    GAP_SDK_Location / 'tools/autotiler_v3/Generators/BilinearResizes',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_fp16',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Generators',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Generators_SQ8',
    GAP_SDK_Location / 'tools/autotiler_v3/Generators/BilinearResizes',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Libraries',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_fp16',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8'
)

Lib_gcc = GAP8_C_Compiler.find_library(
    'gcc',
    required: true
)

Lib_AutoTiler = Native_C_Compiler.find_library(
    'LibTile',
    dirs: meson.project_source_root() / GAP_SDK_Location / 'tools/autotiler_v3/Autotiler',
    required: true
)

Sources = files()

Toolchain_Sources = files(
    GAP_SDK_Location / 'libs/gap_lib/jpeg/dct.c',
    GAP_SDK_Location / 'libs/gap_lib/jpeg/jpeg_constants.c',
    GAP_SDK_Location / 'libs/gap_lib/jpeg/jpeg_encoder.c',
    GAP_SDK_Location / 'libs/gap_lib/jpeg/cluster.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/src/device/gap8_it.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/src/device/system_gap8.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/src/driver/gap_io.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/libs/src/errno.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/libs/src/stdlib.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/libs/src/string.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/cluster/malloc/cl_malloc.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/cluster/drivers/cluster_synchronisation/cl_to_fc_delegate.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/cluster/drivers/cluster_synchronisation/fc_to_cl_delegate.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/cluster/drivers/cluster_team/cl_team.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/cluster/drivers/delegate/hyperbus/hyperbus_cl_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/cluster/drivers/delegate/uart/uart_cl_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/cluster/drivers/dma/cl_dma_irq.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/fc_event/fc_event.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/fll/fll.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/gpio/gpio.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/pad/pad.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/pmu/pmu.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/pmu/pmu_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/pwm/pwm.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/pwm/pwm_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/rtc/rtc.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/rtc/rtc_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/timer/timer.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/hyperbus/hyperbus.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/hyperbus/hyperbus_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/cpi/cpi.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/cpi/cpi_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/dmacpy/dmacpy.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/dmacpy/dmacpy_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/i2c/i2c.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/i2c/i2c_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/i2s/i2s.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/i2s/i2s_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/spi/spi.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/spi/spi_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/uart/uart.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/drivers/udma/uart/uart_internal.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/flash/flash.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/partition/partition.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/partition/flash_partition.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/crc/md5.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/fs/fs.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/fs/lfs/lfs.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/fs/lfs/lfs_util.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/fs/lfs/pi_lfs.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/fs/read_fs/read_fs.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/fs/host_fs/host_fs.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/ota/ota.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/ota/ota_utility.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/ota/updater.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/bootloader/bootloader_utility.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/bsp/ai_deck.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/camera/camera.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/camera/himax/himax.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/flash/hyperflash/hyperflash.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/ram/hyperram/hyperram.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/ram/spiram/spiram.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/flash/spiflash/spiflash.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/ram/ram.c',
    GAP_SDK_Location / 'rtos/pmsis/pmsis_bsp/ram/alloc_extern.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/pi_log.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/event_kernel/event_kernel.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/malloc/cl_l1_malloc.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/malloc/fc_l1_malloc.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/malloc/l2_malloc.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/malloc/malloc_external.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/malloc/malloc_internal.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/malloc/pi_malloc.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/mem_slab/mem_slab.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/os/device.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/rtos/os/pmsis_task.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/pmsis/backend/pmsis_backend_native_task_api.c',
    GAP_SDK_Location / 'rtos/freeRTOS/freertos_kernel/portable/GCC/RI5CY-GAP8/port.c',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/libs/printf/printf.c',
    GAP_SDK_Location / 'rtos/freeRTOS/freertos_kernel/list.c',
    GAP_SDK_Location / 'rtos/freeRTOS/freertos_kernel/queue.c',
    GAP_SDK_Location / 'rtos/freeRTOS/freertos_kernel/tasks.c',
    GAP_SDK_Location / 'rtos/freeRTOS/freertos_kernel/timers.c',
    GAP_SDK_Location / 'rtos/freeRTOS/freertos_kernel/event_groups.c',
    GAP_SDK_Location / 'rtos/freeRTOS/freertos_kernel/stream_buffer.c',
    GAP_SDK_Location / 'rtos/freeRTOS/demos/gwt/config/gap8/FreeRTOS_util.c'
)

FreeRTOS_Assembly_Sources = files(
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/src/device/gap8_iet.S',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/src/device/startup_gap8.S',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/cluster/drivers/cluster_synchronisation/cluster_core.S',
    GAP_SDK_Location / 'rtos/freeRTOS/vendors/gwt/gap8/pmsis/util/asm_util.S',
    GAP_SDK_Location / 'rtos/freeRTOS/freertos_kernel/portable/GCC/RI5CY-GAP8/port_asm.S'
)

GenResize_Sources = files(
    'Source/Model/Data/ResizeModel.c'
)

Tile_Kernel_Sources = files(
    GAP_SDK_Location / 'libs/gap_lib/img_io/ImgIO.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries/SSD_BasicKernels.c',
    GAP_SDK_Location / 'tools/autotiler_v3/Generators/BilinearResizes/ResizeBasicKernels.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries/CNN_Copy.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/CNN_AT_Misc.c',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Libraries/CmplxFunctions.c',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Libraries/FFT_Library.c',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Libraries/MfccBasicKernels.c',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Libraries/PreProcessing.c',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Libraries/math_funcs.c',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Libraries/pulp_dsp/plp_cos_f32s_xpulpv2.c',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Libraries/pulp_dsp/plp_sin_f32s_xpulpv2.c',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Libraries/pulp_dsp/plp_common_tables.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/CNN_Activation_SQ8.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/CNN_Activation_HWC_SQ8.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/CNN_Bias_Linear_SQ8.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/CNN_Conv_SQ8.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/CNN_MatMul_Conv_SQ8.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/CNN_Pooling_SQ8.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/CNN_Conv_DW_SQ8.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/CNN_MatAlgebra_SQ8.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/CNN_SoftMax_SQ8.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Libraries_SQ8/RNN_SQ8.c'
)

GenTile_Sources = files(
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Generators/CNN_Generator_Util.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Generators/CNN_Copy_Generators.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Generators/SSD_Generators.c',
    GAP_SDK_Location / 'tools/autotiler_v3/Generators/BilinearResizes/ResizeGenerator.c',
    GAP_SDK_Location / 'tools/autotiler_v3/DSP_Generators/DSP_Generators.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Generators_SQ8/CNN_Generators_SQ8.c',
    GAP_SDK_Location / 'tools/autotiler_v3/CNN_Generators_SQ8/RNN_Generators_SQ8.c'
)

Prog_NNTOOL = find_program('nntool')
Prog_size = find_program('riscv32-unknown-elf-size')

L1_Reserved_Memory = '30000'
L2_Reserved_Memory = '190000'
L3_Reserved_Memory = '8000000'

subdir('Source')

Lib_AutoTilerGen = static_library(
    'AutoTilerGen',
    [
        GenTile_Sources
    ],
    dependencies: [
        Lib_AutoTiler
    ],
    include_directories: GenTile_Includes,
    c_args: [
        Native_C_Flags
    ],
    override_options: [
        'warning_level=0'
    ],
    native: true
)

GenResize_Binary = executable(
    'GenResize',
    [
        GenResize_Sources
    ],
    link_with: [
        Lib_AutoTilerGen
    ],
    include_directories: GenTile_Includes,
    c_args: [
        Native_C_Flags
    ],
    override_options: [
        'warning_level=0'
    ],
    native: true
)

GAP8_Resize_Sources = custom_target(
    'gap8_resize_sources',
    input: [
        GenResize_Binary
    ],
    output: [
        'ResizeKernels.c',
        'ResizeKernels.h',
        'ResizeBasicKernels.h'
    ],
    command: [
        GenResize_Binary,
        '--L1',
        L1_Reserved_Memory,
        '--L2',
        L2_Reserved_Memory,
        '--L3',
        L3_Reserved_Memory
    ]
)

Model_State_File = custom_target(
    'model_state_file',
    input: [
        'Source/Model/Data/nntool_script',
        'Source/Model/Data/ptq_int8.tflite'
    ],
    output: [
        'ptq_int8.json'
    ],
    command: [
        Prog_NNTOOL, 
        '-s', 
        '@INPUT0@',
        '@INPUT1@',
        '-q'
    ]
)

Model_Tensors = custom_target(
    'model_tensors_and_gentile_sources',
    input: [
        Model_State_File
    ],
    output: [
        'ptq_int8Model.c',
        'ptq_int8Info.h'
    ],
    command: [
        Prog_NNTOOL,
        '-g', 
        '-M',
        '.',
        '-m',
        '@OUTPUT0@',
        '-T',
        'tensors',
        '-H',
        '@OUTPUT1@',
        '@INPUT0@'
    ]
)

GenTile_Binary = executable(
    'GenTile',
    [
        Model_Tensors[0]
    ],
    link_with: [
        Lib_AutoTilerGen
    ],
    include_directories: GenTile_Includes,
    c_args: [
        Native_C_Flags
    ],
    override_options: [
        'warning_level=0'
    ],
    native: true
)

GAP8_Model_Sources = custom_target(
    'gap8_model_sources',
    input: [
        GenTile_Binary
    ],
    output: [
        'ptq_int8Kernels.c',
        'ptq_int8Kernels.h',
        'Expression_Kernels.c',
        'Expression_Kernels.h',
        'ptq_int8_L3_Flash_Const.dat'
    ],
    command: [
        GenTile_Binary,
        '-c',
        'tensors',
        '--L1',
        L1_Reserved_Memory,
        '--L2',
        L2_Reserved_Memory,
        '--L3',
        L3_Reserved_Memory
    ]
)

Lib_AutoTilerKernels_GVSOC = static_library(
    'AutoTilerKernels_GVSOC',
    [
        Tile_Kernel_Sources,
        Model_Tensors[1],
        GAP8_Model_Sources,
        GAP8_Resize_Sources
    ],
    dependencies: [
        Lib_gcc
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_GVSOC__',
        '-D__PLATFORM__=ARCHI_PLATFORM_GVSOC'
    ],
    link_args: [
        GAP8_Link_Flags,
        #'-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gvsoc.conf.ld'
    ],
    override_options: [
        'warning_level=0'
    ],
    native: false
)

Lib_Toolchain_GVSOC = static_library(
    'Toolchain_GVSOC',
    [
        Toolchain_Sources
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_GVSOC__',
        '-D__PLATFORM__=ARCHI_PLATFORM_GVSOC'
    ],
    link_args: [
        GAP8_Link_Flags
    ],
    override_options: [
        'warning_level=0'
    ],
    native: false
)

Lib_FreeRTOS_Assembly_GVSOC = static_library(
    'FreeRTOS_Assembly_GVSOC',
    [
        FreeRTOS_Assembly_Sources
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_GVSOC__',
        '-D__PLATFORM__=ARCHI_PLATFORM_GVSOC',
        '-DASSEMBLY_LANGUAGE'
    ],
    link_args: [
        GAP8_Link_Flags,
        #'-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gvsoc.conf.ld'
    ],
    override_options: [
        'warning_level=0'
    ],
    native: false
)

Project_GVSOC_Binary = executable(
    meson.project_name(),
    [
        Sources
    ],
    dependencies: [
        Lib_gcc
    ],
    link_with: [
        Lib_AutoTilerKernels_GVSOC,
        Lib_Toolchain_GVSOC,
        Lib_FreeRTOS_Assembly_GVSOC
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_GVSOC__',
        '-D__PLATFORM__=ARCHI_PLATFORM_GVSOC'
    ],
    cpp_args: [
        GAP8_CXX_Flags,
        '-D__PLATFORM_GVSOC__',
        '-D__PLATFORM__=ARCHI_PLATFORM_GVSOC'
    ],
    link_args: [
        GAP8_Link_Flags,
        #'-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gvsoc.conf.ld'
    ],
    native: false
)

Lib_AutoTilerKernels_AIdeck = static_library(
    'AutoTilerKernels_AIdeck',
    [
        Tile_Kernel_Sources,
        Model_Tensors[1],
        GAP8_Model_Sources,
        GAP8_Resize_Sources
    ],
    dependencies: [
        Lib_gcc
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_BOARD__',
        '-D__PLATFORM__=ARCHI_PLATFORM_BOARD'
    ],
    link_args: [
        GAP8_Link_Flags,
        #'-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gapuino.conf.ld'
    ],
    override_options: [
        'warning_level=0'
    ],
    native: false
)

Lib_Toolchain_AIdeck = static_library(
    'Toolchain_AIdeck',
    [
        Toolchain_Sources
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_BOARD__'
    ],
    link_args: [
        GAP8_Link_Flags
    ],
    override_options: [
        'warning_level=0'
    ],
    native: false
)

Lib_FreeRTOS_Assembly_AIdeck = static_library(
    'FreeRTOS_Assembly_AIdeck',
    [
        FreeRTOS_Assembly_Sources
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_BOARD__',
        '-DASSEMBLY_LANGUAGE'
    ],
    link_args: [
        GAP8_Link_Flags,
        #'-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gvsoc.conf.ld'
    ],
    override_options: [
        'warning_level=0'
    ],
    native: false
)

Project_AIdeck_Binary = executable(
    meson.project_name() + '-AIdeck',
    [
        Sources
    ],
    dependencies: [
        Lib_gcc
    ],
    link_with: [
        Lib_AutoTilerKernels_AIdeck,
        Lib_Toolchain_AIdeck,
        Lib_FreeRTOS_Assembly_AIdeck
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_BOARD__',
        '-D__PLATFORM__=ARCHI_PLATFORM_BOARD'
    ],
    cpp_args: [
        GAP8_CXX_Flags,
        '-D__PLATFORM_BOARD__',
        '-D__PLATFORM__=ARCHI_PLATFORM_BOARD'
    ],
    link_args: [
        GAP8_Link_Flags,
        #'-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gapuino.conf.ld'
    ],
    native: false
)

Target_GVSOC_size = run_target('size_gvsoc',
    command: [
        Prog_size, Project_GVSOC_Binary.full_path()
    ],
    depends: Project_GVSOC_Binary
)

Target_AIdeck_size = run_target('size_aideck',
    command: [
        Prog_size, Project_AIdeck_Binary.full_path()
    ],
    depends: Project_AIdeck_Binary
)

Target_GVSOC_disassemble = run_target('disassemble_gvsoc',
    command: [
        'Scripts/disassemble.sh',
        Project_GVSOC_Binary.full_path(),
        meson.project_name()
    ],
    depends: Project_GVSOC_Binary
)

Target_GVSOC_disassemble = run_target('disassemble_aideck',
    command: [
        'Scripts/disassemble.sh',
        Project_AIdeck_Binary.full_path(),
        meson.project_name() + '-AIdeck'
    ],
    depends: Project_AIdeck_Binary
)

Target_gvsoc = run_target('gvsoc',
    command: [
        'Scripts/run_in_gvsoc.sh',
        meson.project_build_root(),
        meson.project_name()
    ],
    depends: Project_GVSOC_Binary
)

Target_gvsoc = run_target('aideck',
    command: [
        'Scripts/run_in_board.sh',
        meson.project_build_root(),
        meson.project_name() + '-AIdeck'
    ],
    depends: Project_AIdeck_Binary
)