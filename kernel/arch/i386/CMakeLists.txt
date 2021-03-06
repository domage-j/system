##
## arch/i386/CMakeLists.txt - i386 project
## System sources under license MIT
##

cmake_minimum_required(VERSION 3.11...3.16)
project(libi386
        VERSION 1.0
        DESCRIPTION "i386 loader."
        LANGUAGES C ASM_NASM)

##################
## i386 sources ##
##################

set(SOURCES
        i386_entry.c
        cpu/asm/dt_flush.asm
        cpu/asm/interrupt.asm
        cpu/apic/apic.h
        cpu/apic/apic.c
        cpu/pic/pic.c
        cpu/pic/pic_disable.asm
        cpu/pic/ports.c
        cpu/registers/msr.c
        cpu/registers/msr.h
        cpu/registers/cr.c
        cpu/registers/dump_regs.c
        cpu/gdt.c
        cpu/idt.c
        cpu/isr.c
        memory/physical.h
        memory/virtual.h
        memory/memory_init.c
        memory/memory_layout.c
        memory/boot/boot_memory.h
        memory/boot/boot_paging.c
        memory/physical/physical_memory_init.c
        memory/physical/physical_memory.c
        memory/virtual/virtual_memory_init.c
        memory/virtual/heap.c
        memory/virtual/mmap.c
        memory/virtual/page_fault_handler.c
        memory/virtual/paging.c
        drivers/monitor/init.c
        drivers/monitor/monitor.h
        drivers/monitor/monitor.c
        drivers/timer_example/timer.c
        cpu/apic/apic.c
        cpu/registers/msr.c
        cpu/registers/msr.h)

##################
## i386 targets ##
##################

add_library(i386 ${SOURCES})
add_dependencies(i386 Library::c_abi Library::cpuid Library::system)
target_link_libraries(i386
        PUBLIC
            Library::c_abi
            Library::system
            Library::cpuid)
target_include_directories(i386
        PUBLIC
            ${kernel_INCLUDE_DIRS}
            ${cpuid_INCLUDE_DIRS}
            ${system_INCLUDE_DIRS}
        PRIVATE
            include
            ${CMAKE_CURRENT_SOURCE_DIR})

############################
## crt0 object            ##
############################

add_library(Kernel::arch ALIAS i386)

add_library(c_RUNTIME OBJECT init/cert0.asm)
target_include_directories(c_RUNTIME PUBLIC init)

############################
## Exported variables     ##
############################

set(loader_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/generic.ld CACHE INTERNAL "")
##set(loader_CERT0 $<TARGET_OBJECTS:cert0> CACHE INTERNAL "")
