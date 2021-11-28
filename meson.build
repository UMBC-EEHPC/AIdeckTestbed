project(
    'AIdeckTestbed', 
    'c', 
    'cpp',
    version : '1.0',
    default_options : [
        'b_lto=false',
        'b_pch=false',
        'b_staticpic=false',
        'buildtype=debug',
        'cpp_rtti=false',
        'cpp_eh=none',
        'debug=true',
        'c_std=gnu99',
        'cpp_std=gnu++17'
    ],
    meson_version : '>=0.59.0'
)

GAP_SDK_Location = 'Toolchain/gap_sdk'
ETL_Location = 'Toolchain/etl/include'
CXX_Compiler = meson.get_compiler('cpp')
C_Compiler = meson.get_compiler('c')

add_project_arguments(
    '-fstack-protector-strong',
    '-DCONFIG_AI_DECK',
    '-DRT_FC_STACK_SIZE=2048',
    '-D__PLATFORM_GVSOC__',
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
    meson.project_source_root() / GAP_SDK_Location / 'install/GAP8_V2/include/rt/chips/gap_rev1/config.h',
    language: [
        'c', 
        'cpp'
    ],
    native: false
)
add_project_arguments(
    '-fpermissive',
    '-fno-exceptions',
    language: 'cpp',
    native: false
)
add_project_link_arguments(
  '-march=rv32imcxgap8',
  '-mPE=8',
  '-mFC=1',
  '-Wl,--as-needed',
  '-Wl,--gc-sections',
  '-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/link.gap8_rev1.ld',
  '-T' + meson.project_source_root() / GAP_SDK_Location / 'install/workstation/ld/gvsoc.conf.ld',
  '-nostartfiles',
  '-nostdlib',
  '-fno-exceptions',
  language: [
      'c',
      'cpp'
  ],
  native: false
)

Includes = include_directories(
    '.',
    GAP_SDK_Location / 'install/GAP8_V2/include',
    GAP_SDK_Location / 'install/GAP8_V2/include/io',
    GAP_SDK_Location / 'install/workstation/include',
    GAP_SDK_Location / 'tools/autotiler_v3/Emulation',
    ETL_Location
)

Lib_pibsp = C_Compiler.find_library(
    'pibsp', 
    dirs: meson.project_source_root() / GAP_SDK_Location / 'install/GAP8_V2/lib/gap/ai_deck', 
    required: true
)
Lib_rt = C_Compiler.find_library(
    'librt', 
    dirs: meson.project_source_root() / GAP_SDK_Location / 'install/GAP8_V2/lib/gap',
    required: true,
    static: true
)
Lib_rtio = C_Compiler.find_library(
    'librtio', 
    dirs: meson.project_source_root() / GAP_SDK_Location / 'install/GAP8_V2/lib/gap', 
    required: true
)
Lib_gcc = C_Compiler.find_library(
    'gcc',
    required: true
)

Linker_Scripts = files(
    GAP_SDK_Location / 'install/workstation/ld/link.gap8_rev1.ld',
    GAP_SDK_Location / 'install/workstation/ld/gvsoc.conf.ld'
)

Sources = files(
    'Main.cpp',
    GAP_SDK_Location / 'rtos/pulp/pulp-os/kernel/conf.c'
)

Prog_size = find_program('riscv32-unknown-elf-size')

subdir('Core')
subdir('Gapack')

# compile the main executable
Project_Binary = executable(
    meson.project_name(),
    [
        Sources, 
    ],
    dependencies: [
        Lib_pibsp, 
        Lib_rt, 
        Lib_rtio, 
        Lib_gcc
    ],
    include_directories: Includes
)

Target_size = run_target('size',
    command: [
        Prog_size, Project_Binary.full_path()
    ],
    depends: Project_Binary
)

Target_disassemble = run_target('disassemble',
    command: [
        'Scripts/disassemble.sh',
        Project_Binary.full_path(),
        meson.project_name()
    ],
    depends: Project_Binary
)

Target_gvsoc = run_target('gvsoc',
    command: [
        'Scripts/run_in_gvsoc.sh',
        meson.project_build_root(),
        meson.project_name()
    ],
    depends: Project_Binary
)