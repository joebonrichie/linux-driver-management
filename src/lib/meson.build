lib_sources = [
    'device.c',
    'drivers/gpu.c',
    'dm/display-manager.c',
    'dm/gdm.c',
    'dm/lightdm.c',
    'scanner.c',
    'scan/pci.c',
    'util.c',
]

libldm_includes = [
    include_directories('.'),
    config_h_dir,
]

libldm = static_library(
    'ldm',
    sources: lib_sources,
    include_directories: libldm_includes,
    dependencies: dep_pci,
    install: false,
)

link_libldm = declare_dependency(
    link_with: libldm,
    include_directories: libldm_includes,
)
