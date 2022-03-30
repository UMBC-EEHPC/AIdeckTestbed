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
    '-march=rv32imcxgap8',
    '-DCONFIG_FLL_MAXDCO_FREQ=900000000',
    '-DUSE_HYPER',
    '-DAT_MODEL_PREFIX=ptq_int8',
    '-DAT_INPUT_HEIGHT=',
    '-DAT_INPUT_WIDTH=',
    '-DAT_INPUT_COLORS=',
    '-DSTACK_SIZE=6144',
    '-DSLAVE_STACK_SIZE=3072',
    '-DAT_IMAGE=',
    '-fstack-protector-strong',
    '-DCONFIG_AI_DECK',
    '-DRT_FC_STACK_SIZE=2048',
    '-fno-jump-tables',
    '-fno-tree-loop-distribute-patterns',
    '-fdata-sections',
    '-ffunction-sections',
    '-mchip=gap8',
    '-mPE=8',
    '-mFC=1',
    '-D__riscv__',
    '-D__GAP__',
    '-D__GAP8__',
    '-DCHIP_VERSION=2',
    '-mnativeomp',
    '-D__pulp__',
    '-DCONFIG_GAP',
    '-D__PULP_OS__',
    '-include',
    meson.project_source_root() / GAP_SDK_Location / 'install/GAP8_V2/include/rt/chips/gap_rev1/config.h'
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
    '-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/link.gap8_rev1.ld',
    '-nostartfiles',
    '-nostdlib',
    '-fno-exceptions'
]

Includes = include_directories(
    '.',
    './Model',
    './Model/Data',
    GAP_SDK_Location / 'install/GAP8_V2/include',
    GAP_SDK_Location / 'install/GAP8_V2/include/io',
    GAP_SDK_Location / 'install/workstation/include',
    GAP_SDK_Location / 'libs/frame_streamer/include',
    GAP_SDK_Location / 'tools/autotiler_v3/Emulation',
    GAP_SDK_Location / 'libs/gap_lib/include',
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
    '.',
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

Lib_pibsp = GAP8_C_Compiler.find_library(
    'pibsp', 
    dirs: meson.project_source_root() / GAP_SDK_Location / 'install/GAP8_V2/lib/gap/ai_deck', 
    required: true
)
Lib_rt = GAP8_C_Compiler.find_library(
    'librt', 
    dirs: meson.project_source_root() / GAP_SDK_Location / 'install/GAP8_V2/lib/gap',
    required: true,
    static: true
)
Lib_rtio = GAP8_C_Compiler.find_library(
    'librtio', 
    dirs: meson.project_source_root() / GAP_SDK_Location / 'install/GAP8_V2/lib/gap', 
    required: true
)
Lib_gaptools = GAP8_C_Compiler.find_library(
    'libgaptools',
    dirs: meson.project_source_root() / GAP_SDK_Location / 'install/GAP8_V2/lib/gap/ai_deck',
    required: true
)
Lib_gaplib = GAP8_C_Compiler.find_library(
    'libgaplib',
    dirs: meson.project_source_root() / GAP_SDK_Location / 'install/GAP8_V2/lib/gap/ai_deck',
    required: true
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

Sources = files(
    'Main.cpp',
    GAP_SDK_Location / 'gap8/rtos/pulp/pulp-os/kernel/conf.c'
)

GenResize_Sources = files(
    'Model/Data/ResizeModel.c'
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

subdir('Core')
subdir('Model')

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
        'Model/Data/nntool_script',
        'Model/Data/ptq_int8.tflite'
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
        Lib_pibsp, 
        Lib_rt, 
        Lib_rtio, 
        Lib_gaplib,
        Lib_gaptools,
        Lib_gcc
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_GVSOC__'
    ],
    link_args: [
        GAP8_Link_Flags,
        '-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gvsoc.conf.ld'
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
        Lib_pibsp, 
        Lib_rt, 
        Lib_rtio, 
        Lib_gaplib,
        Lib_gaptools,
        Lib_gcc
    ],
    link_with: [
        Lib_AutoTilerKernels_GVSOC
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_GVSOC__'
    ],
    cpp_args: [
        GAP8_CXX_Flags,
        '-D__PLATFORM_GVSOC__'
    ],
    link_args: [
        GAP8_Link_Flags,
        '-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gvsoc.conf.ld'
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
        Lib_pibsp, 
        Lib_rt, 
        Lib_rtio, 
        Lib_gaplib,
        Lib_gaptools,
        Lib_gcc
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_BOARD__',
        '-D__RT_IODEV__=2'
    ],
    link_args: [
        GAP8_Link_Flags,
        '-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gapuino.conf.ld'
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
        Lib_pibsp, 
        Lib_rt, 
        Lib_rtio,
        Lib_gaplib,
        Lib_gaptools, 
        Lib_gcc
    ],
    link_with: [
        Lib_AutoTilerKernels_AIdeck
    ],
    include_directories: Includes,
    c_args: [
        GAP8_C_Flags,
        '-D__PLATFORM_BOARD__',
        '-D__RT_IODEV__=2'
    ],
    cpp_args: [
        GAP8_CXX_Flags,
        '-D__PLATFORM_BOARD__',
        '-D__RT_IODEV__=2'
    ],
    link_args: [
        GAP8_Link_Flags,
        '-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gapuino.conf.ld'
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