/**
 * cpuid.h - cpuid main header
 * System sources under license MIT
 */

#ifndef LIBCPUID_CPUID_H
#define LIBCPUID_CPUID_H

#include <stdbool.h>
#include <stdint.h>

#include <compiler.h>

/********************************
 **     Structure and Enum     **
 ********************************/

typedef enum Cpuid_processor_vendor_e
{
	cpu_vendor_UNKNOW        = -1,
	cpu_vendor_AMD           = 0,
	cpu_vendor_INTEL         = 1,
	cpu_vendor_TRANSMETA     = 2,
	cpu_vendor_CYRIX         = 3,
	cpu_vendor_CENTAUR       = 4,
	cpu_vendor_NEXGEN        = 5,
	cpu_vendor_UMC           = 6,
	cpu_vendor_SIS           = 7,
	cpu_vendor_NSC           = 8,
	cpu_vendor_RISE          = 9,
	cpu_vendor_VORTEX        = 10,
	cpu_vendor_VIA           = 11,
	cpu_vendor_ZHAOXIN       = 12,
	cpu_vendor_HYGON         = 13,
	cpu_vendor_ELBRUS        = 14,
	cpu_vendor_VMWARE        = 15,
	cpu_vendor_XEN           = 16,
	cpu_vendor_MICROSOFT_HV  = 17,
	cpu_vendor_PARALLELS     = 18,
	cpu_vendor_QEMU          = 19,
	cpu_vendor_BHYVE         = 20,
	cpu_vendor_KVM           = 21,
	cpu_vendor_ACRN          = 22,
	cpu_vendor_QNX           = 23,
	cpu_vendor_APPLE_ROSETTA = 24,
	cpu_vendor_END,
	cpu_vendor_COUNT = cpu_vendor_END + 1,
} Cpuid_processor_vendor_t;

typedef struct Cpuid_capabilities_s
{
	// first double word from ecx 28 bits used
	uint32_t SSE3            : 1;
	uint32_t PCLMUL          : 1;
	uint32_t DTES64          : 1;
	uint32_t MONITOR         : 1;
	uint32_t DS_CPL          : 1;
	uint32_t VMX             : 1;
	uint32_t SMX             : 1;
	uint32_t EST             : 1;
	uint32_t TM2             : 1;
	uint32_t SSSE3           : 1;
	uint32_t CID             : 1;
	uint32_t FMA             : 1;
	uint32_t CX16            : 1;
	uint32_t ETPRD           : 1;
	uint32_t PDCM            : 1;
	uint32_t _reserved_pad_1 : 1;
	uint32_t PCIDE           : 1;
	uint32_t DCA             : 1;
	uint32_t SSE4_1          : 1;
	uint32_t SSE4_2          : 1;
	uint32_t x2APIC          : 1;
	uint32_t MOVBE           : 1;
	uint32_t POPCNT          : 1;
	uint32_t AES             : 1;
	uint32_t XSAVE           : 1;
	uint32_t OSXSAVE         : 1;
	uint32_t AVX             : 1;
	uint32_t _reserved_pad_2 : 5;

	// second double word from edx 32 bits used
	uint32_t FPU             : 1;
	uint32_t VME             : 1;
	uint32_t DE              : 1;
	uint32_t PSE             : 1;
	uint32_t TSC             : 1;
	uint32_t MSR             : 1;
	uint32_t PAE             : 1;
	uint32_t MCE             : 1;
	uint32_t CX8             : 1;
	uint32_t APIC            : 1;
	uint32_t _reserved_pad_3 : 1;
	uint32_t SEP             : 1;
	uint32_t MTRR            : 1;
	uint32_t PGE             : 1;
	uint32_t MCA             : 1;
	uint32_t CMOV            : 1;
	uint32_t PAT             : 1;
	uint32_t PSE36           : 1;
	uint32_t PSN             : 1;
	uint32_t CLF             : 1;
	uint32_t _reserved_pad_4 : 1;
	uint32_t DTES            : 1;
	uint32_t ACPI            : 1;
	uint32_t MMX             : 1;
	uint32_t FXSR            : 1;
	uint32_t SSE             : 1;
	uint32_t SSE2            : 1;
	uint32_t SS              : 1;
	uint32_t HTT             : 1;
	uint32_t TM1             : 1;
	uint32_t IA64            : 1;
	uint32_t PBE             : 1;
} Cpuid_capabilities_t;

/********************************
 **     Public functions       **
 ********************************/

/**
 * @brief Check if cpuid is supported.
 * @return 0 if unsupported, NON-0 otherwise
 */
int STDCALL cpuid_is_supported();

/**
 * @brief Get max EAX value for cpuid instruction.
 * @return maximum value for eax
 */
int STDCALL cpuid_max();

/**
 * @brief Retrieve the vendor code.
 * @return Cpuid_processor_vendor_t code
 */
Cpuid_processor_vendor_t STDCALL cpuid_get_vendor();

/**
 * @brief Return a vendor string.
 * @param aVendorCode - a valid vendor code
 * @return C-string or NULL
 */
const char* cpuid_get_vendor_string(Cpuid_processor_vendor_t aVendorCode);

/**
 * @brief Return the CPU model string.
 * @return C-string or NULL
 */
const char* STDCALL cpuid_get_model_string();

/**
 * @brief Retrieve capabilities
 * @return - capability struct, with present capabilities bit set
 */
Cpuid_capabilities_t CDECL cpuid_get_capabilities();

#endif // LIBCPUID_CPUID_H
