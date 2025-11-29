//===- WinAdapter.h - Windows Adapter for non-Windows platforms -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines Windows-specific types, macros, and SAL annotations used
// in the codebase for non-Windows platforms.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_SUPPORT_WIN_ADAPTER_H
#define LLVM_SUPPORT_WIN_ADAPTER_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#include <atomic>
#include <cassert>
#include <climits>
#include <cstring>
#include <cwchar>
#include <fstream>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>

#ifndef _WIN32
// If it is GCC, there is no UUID support and we must emulate it.
// Clang support depends on the -fms-extensions compiler flag.
#if !defined(__clang__) || !defined(_MSC_EXTENSIONS)
#define __EMULATE_UUID 1
#endif // __clang__

#ifdef __EMULATE_UUID
#define __declspec(x)
#endif // __EMULATE_UUID

#define DECLSPEC_SELECTANY

#ifdef __EMULATE_UUID
#define uuid(id)
#endif // __EMULATE_UUID

#ifdef __EMULATE_UUID
struct GUID
#else  // __EMULATE_UUID
// These specific definitions are required by clang -fms-extensions.
typedef struct _GUID
#endif // __EMULATE_UUID
{
  uint32_t Data1;
  uint16_t Data2;
  uint16_t Data3;
  uint8_t Data4[8];
}
#ifdef __EMULATE_UUID
;
#else  // __EMULATE_UUID
GUID;
#endif // __EMULATE_UUID

#elif !defined(_MSC_VER)
#include <guiddef.h>

#define NOATOM 1
#define NOGDICAPMASKS 1
#define NOMETAFILE 1
#define NOOPENFILE 1
#define NORASTEROPS 1
#define NOSCROLL 1
#define NOSOUND 1
#define NOSYSMETRICS 1
#define NOWH 1
#define NOCOMM 1
#define NOKANJI 1
#define NOCRYPT 1
#define NOMCX 1
#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN 1
#define NONAMELESSSTRUCT 1

// Map these errors to equivalent errnos.
#define ERROR_NOT_CAPABLE EPERM
#define ERROR_UNHANDLED_EXCEPTION EBADF

#define STRSAFE_NO_DEPRECATE
#include <intsafe.h>
#include <strsafe.h>
#include <unknwn.h>
#undef MemoryFence
#undef IN
#undef OUT
#undef interface

// winnt.h conflicts with Coff.h, this is just a big #undef list.
//-------------------------------------------------------------
#undef IMAGE_DOS_SIGNATURE
#undef IMAGE_OS2_SIGNATURE
#undef IMAGE_OS2_SIGNATURE_LE
#undef IMAGE_VXD_SIGNATURE
#undef IMAGE_NT_SIGNATURE
#undef IMAGE_SIZEOF_FILE_HEADER
#undef IMAGE_FILE_RELOCS_STRIPPED
#undef IMAGE_FILE_EXECUTABLE_IMAGE
#undef IMAGE_FILE_LINE_NUMS_STRIPPED
#undef IMAGE_FILE_LOCAL_SYMS_STRIPPED
#undef IMAGE_FILE_AGGRESIVE_WS_TRIM
#undef IMAGE_FILE_LARGE_ADDRESS_AWARE
#undef IMAGE_FILE_BYTES_REVERSED_LO
#undef IMAGE_FILE_32BIT_MACHINE
#undef IMAGE_FILE_DEBUG_STRIPPED
#undef IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP
#undef IMAGE_FILE_NET_RUN_FROM_SWAP
#undef IMAGE_FILE_SYSTEM
#undef IMAGE_FILE_DLL
#undef IMAGE_FILE_UP_SYSTEM_ONLY
#undef IMAGE_FILE_BYTES_REVERSED_HI
#undef IMAGE_FILE_MACHINE_UNKNOWN
#undef IMAGE_FILE_MACHINE_I386
#undef IMAGE_FILE_MACHINE_R3000
#undef IMAGE_FILE_MACHINE_R4000
#undef IMAGE_FILE_MACHINE_R10000
#undef IMAGE_FILE_MACHINE_WCEMIPSV2
#undef IMAGE_FILE_MACHINE_ALPHA
#undef IMAGE_FILE_MACHINE_SH3
#undef IMAGE_FILE_MACHINE_SH3DSP
#undef IMAGE_FILE_MACHINE_SH3E
#undef IMAGE_FILE_MACHINE_SH4
#undef IMAGE_FILE_MACHINE_SH5
#undef IMAGE_FILE_MACHINE_ARM
#undef IMAGE_FILE_MACHINE_ARMV7
#undef IMAGE_FILE_MACHINE_ARMNT
#undef IMAGE_FILE_MACHINE_ARM64
#undef IMAGE_FILE_MACHINE_THUMB
#undef IMAGE_FILE_MACHINE_AM33
#undef IMAGE_FILE_MACHINE_POWERPC
#undef IMAGE_FILE_MACHINE_POWERPCFP
#undef IMAGE_FILE_MACHINE_IA64
#undef IMAGE_FILE_MACHINE_MIPS16
#undef IMAGE_FILE_MACHINE_ALPHA64
#undef IMAGE_FILE_MACHINE_MIPSFPU
#undef IMAGE_FILE_MACHINE_MIPSFPU16
#undef IMAGE_FILE_MACHINE_AXP64
#undef IMAGE_FILE_MACHINE_TRICORE
#undef IMAGE_FILE_MACHINE_CEF
#undef IMAGE_FILE_MACHINE_EBC
#undef IMAGE_FILE_MACHINE_AMD64
#undef IMAGE_FILE_MACHINE_M32R
#undef IMAGE_FILE_MACHINE_CEE
#undef IMAGE_NUMBEROF_DIRECTORY_ENTRIES
#undef IMAGE_SIZEOF_ROM_OPTIONAL_HEADER
#undef IMAGE_SIZEOF_STD_OPTIONAL_HEADER
#undef IMAGE_SIZEOF_NT_OPTIONAL32_HEADER
#undef IMAGE_SIZEOF_NT_OPTIONAL64_HEADER
#undef IMAGE_NT_OPTIONAL_HDR32_MAGIC
#undef IMAGE_NT_OPTIONAL_HDR64_MAGIC
#undef IMAGE_ROM_OPTIONAL_HDR_MAGIC
#undef IMAGE_SIZEOF_NT_OPTIONAL_HEADER
#undef IMAGE_NT_OPTIONAL_HDR_MAGIC
#undef IMAGE_SIZEOF_NT_OPTIONAL_HEADER
#undef IMAGE_NT_OPTIONAL_HDR_MAGIC
#undef IMAGE_FIRST_SECTION
#undef IMAGE_SUBSYSTEM_UNKNOWN
#undef IMAGE_SUBSYSTEM_NATIVE
#undef IMAGE_SUBSYSTEM_WINDOWS_GUI
#undef IMAGE_SUBSYSTEM_WINDOWS_CUI
#undef IMAGE_SUBSYSTEM_OS2_CUI
#undef IMAGE_SUBSYSTEM_POSIX_CUI
#undef IMAGE_SUBSYSTEM_NATIVE_WINDOWS
#undef IMAGE_SUBSYSTEM_WINDOWS_CE_GUI
#undef IMAGE_SUBSYSTEM_EFI_APPLICATION
#undef IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER
#undef IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER
#undef IMAGE_SUBSYSTEM_EFI_ROM
#undef IMAGE_SUBSYSTEM_XBOX
#undef IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION
#undef IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA
#undef IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
#undef IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY
#undef IMAGE_DLLCHARACTERISTICS_NX_COMPAT
#undef IMAGE_DLLCHARACTERISTICS_NO_ISOLATION
#undef IMAGE_DLLCHARACTERISTICS_NO_SEH
#undef IMAGE_DLLCHARACTERISTICS_NO_BIND
#undef IMAGE_DLLCHARACTERISTICS_APPCONTAINER
#undef IMAGE_DLLCHARACTERISTICS_WDM_DRIVER
#undef IMAGE_DLLCHARACTERISTICS_GUARD_CF
#undef IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE
#undef IMAGE_DIRECTORY_ENTRY_EXPORT
#undef IMAGE_DIRECTORY_ENTRY_IMPORT
#undef IMAGE_DIRECTORY_ENTRY_RESOURCE
#undef IMAGE_DIRECTORY_ENTRY_EXCEPTION
#undef IMAGE_DIRECTORY_ENTRY_SECURITY
#undef IMAGE_DIRECTORY_ENTRY_BASERELOC
#undef IMAGE_DIRECTORY_ENTRY_DEBUG
#undef IMAGE_DIRECTORY_ENTRY_ARCHITECTURE
#undef IMAGE_DIRECTORY_ENTRY_GLOBALPTR
#undef IMAGE_DIRECTORY_ENTRY_TLS
#undef IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG
#undef IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT
#undef IMAGE_DIRECTORY_ENTRY_IAT
#undef IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT
#undef IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR
#undef IMAGE_SIZEOF_SHORT_NAME
#undef IMAGE_SIZEOF_SECTION_HEADER
#undef IMAGE_SCN_TYPE_NO_PAD
#undef IMAGE_SCN_CNT_CODE
#undef IMAGE_SCN_CNT_INITIALIZED_DATA
#undef IMAGE_SCN_CNT_UNINITIALIZED_DATA
#undef IMAGE_SCN_LNK_OTHER
#undef IMAGE_SCN_LNK_INFO
#undef IMAGE_SCN_LNK_REMOVE
#undef IMAGE_SCN_LNK_COMDAT
#undef IMAGE_SCN_NO_DEFER_SPEC_EXC
#undef IMAGE_SCN_GPREL
#undef IMAGE_SCN_MEM_FARDATA
#undef IMAGE_SCN_MEM_PURGEABLE
#undef IMAGE_SCN_MEM_16BIT
#undef IMAGE_SCN_MEM_LOCKED
#undef IMAGE_SCN_MEM_PRELOAD
#undef IMAGE_SCN_ALIGN_1BYTES
#undef IMAGE_SCN_ALIGN_2BYTES
#undef IMAGE_SCN_ALIGN_4BYTES
#undef IMAGE_SCN_ALIGN_8BYTES
#undef IMAGE_SCN_ALIGN_16BYTES
#undef IMAGE_SCN_ALIGN_32BYTES
#undef IMAGE_SCN_ALIGN_64BYTES
#undef IMAGE_SCN_ALIGN_128BYTES
#undef IMAGE_SCN_ALIGN_256BYTES
#undef IMAGE_SCN_ALIGN_512BYTES
#undef IMAGE_SCN_ALIGN_1024BYTES
#undef IMAGE_SCN_ALIGN_2048BYTES
#undef IMAGE_SCN_ALIGN_4096BYTES
#undef IMAGE_SCN_ALIGN_8192BYTES
#undef IMAGE_SCN_ALIGN_MASK
#undef IMAGE_SCN_LNK_NRELOC_OVFL
#undef IMAGE_SCN_MEM_DISCARDABLE
#undef IMAGE_SCN_MEM_NOT_CACHED
#undef IMAGE_SCN_MEM_NOT_PAGED
#undef IMAGE_SCN_MEM_SHARED
#undef IMAGE_SCN_MEM_EXECUTE
#undef IMAGE_SCN_MEM_READ
#undef IMAGE_SCN_MEM_WRITE
#undef IMAGE_SCN_SCALE_INDEX
#undef IMAGE_SIZEOF_SYMBOL
#undef IMAGE_SYM_UNDEFINED
#undef IMAGE_SYM_ABSOLUTE
#undef IMAGE_SYM_DEBUG
#undef IMAGE_SYM_SECTION_MAX
#undef IMAGE_SYM_SECTION_MAX_EX
#undef IMAGE_SYM_TYPE_NULL
#undef IMAGE_SYM_TYPE_VOID
#undef IMAGE_SYM_TYPE_CHAR
#undef IMAGE_SYM_TYPE_SHORT
#undef IMAGE_SYM_TYPE_INT
#undef IMAGE_SYM_TYPE_LONG
#undef IMAGE_SYM_TYPE_FLOAT
#undef IMAGE_SYM_TYPE_DOUBLE
#undef IMAGE_SYM_TYPE_STRUCT
#undef IMAGE_SYM_TYPE_UNION
#undef IMAGE_SYM_TYPE_ENUM
#undef IMAGE_SYM_TYPE_MOE
#undef IMAGE_SYM_TYPE_BYTE
#undef IMAGE_SYM_TYPE_WORD
#undef IMAGE_SYM_TYPE_UINT
#undef IMAGE_SYM_TYPE_DWORD
#undef IMAGE_SYM_TYPE_PCODE
#undef IMAGE_SYM_DTYPE_NULL
#undef IMAGE_SYM_DTYPE_POINTER
#undef IMAGE_SYM_DTYPE_FUNCTION
#undef IMAGE_SYM_DTYPE_ARRAY
#undef IMAGE_SYM_CLASS_END_OF_FUNCTION
#undef IMAGE_SYM_CLASS_NULL
#undef IMAGE_SYM_CLASS_AUTOMATIC
#undef IMAGE_SYM_CLASS_EXTERNAL
#undef IMAGE_SYM_CLASS_STATIC
#undef IMAGE_SYM_CLASS_REGISTER
#undef IMAGE_SYM_CLASS_EXTERNAL_DEF
#undef IMAGE_SYM_CLASS_LABEL
#undef IMAGE_SYM_CLASS_UNDEFINED_LABEL
#undef IMAGE_SYM_CLASS_MEMBER_OF_STRUCT
#undef IMAGE_SYM_CLASS_ARGUMENT
#undef IMAGE_SYM_CLASS_STRUCT_TAG
#undef IMAGE_SYM_CLASS_MEMBER_OF_UNION
#undef IMAGE_SYM_CLASS_UNION_TAG
#undef IMAGE_SYM_CLASS_TYPE_DEFINITION
#undef IMAGE_SYM_CLASS_UNDEFINED_STATIC
#undef IMAGE_SYM_CLASS_ENUM_TAG
#undef IMAGE_SYM_CLASS_MEMBER_OF_ENUM
#undef IMAGE_SYM_CLASS_REGISTER_PARAM
#undef IMAGE_SYM_CLASS_BIT_FIELD
#undef IMAGE_SYM_CLASS_FAR_EXTERNAL
#undef IMAGE_SYM_CLASS_BLOCK
#undef IMAGE_SYM_CLASS_FUNCTION
#undef IMAGE_SYM_CLASS_END_OF_STRUCT
#undef IMAGE_SYM_CLASS_FILE
#undef IMAGE_SYM_CLASS_SECTION
#undef IMAGE_SYM_CLASS_WEAK_EXTERNAL
#undef IMAGE_SYM_CLASS_CLR_TOKEN
#undef IMAGE_SIZEOF_AUX_SYMBOL
#undef IMAGE_COMDAT_SELECT_NODUPLICATES
#undef IMAGE_COMDAT_SELECT_ANY
#undef IMAGE_COMDAT_SELECT_SAME_SIZE
#undef IMAGE_COMDAT_SELECT_EXACT_MATCH
#undef IMAGE_COMDAT_SELECT_ASSOCIATIVE
#undef IMAGE_COMDAT_SELECT_LARGEST
#undef IMAGE_COMDAT_SELECT_NEWEST
#undef IMAGE_WEAK_EXTERN_SEARCH_NOLIBRARY
#undef IMAGE_WEAK_EXTERN_SEARCH_LIBRARY
#undef IMAGE_WEAK_EXTERN_SEARCH_ALIAS
#undef IMAGE_SIZEOF_RELOCATION
#undef IMAGE_REL_I386_ABSOLUTE
#undef IMAGE_REL_I386_DIR16
#undef IMAGE_REL_I386_REL16
#undef IMAGE_REL_I386_DIR32
#undef IMAGE_REL_I386_DIR32NB
#undef IMAGE_REL_I386_SEG12
#undef IMAGE_REL_I386_SECTION
#undef IMAGE_REL_I386_SECREL
#undef IMAGE_REL_I386_TOKEN
#undef IMAGE_REL_I386_SECREL7
#undef IMAGE_REL_I386_REL32
#undef IMAGE_REL_MIPS_ABSOLUTE
#undef IMAGE_REL_MIPS_REFHALF
#undef IMAGE_REL_MIPS_REFWORD
#undef IMAGE_REL_MIPS_JMPADDR
#undef IMAGE_REL_MIPS_REFHI
#undef IMAGE_REL_MIPS_REFLO
#undef IMAGE_REL_MIPS_GPREL
#undef IMAGE_REL_MIPS_LITERAL
#undef IMAGE_REL_MIPS_SECTION
#undef IMAGE_REL_MIPS_SECREL
#undef IMAGE_REL_MIPS_SECRELLO
#undef IMAGE_REL_MIPS_SECRELHI
#undef IMAGE_REL_MIPS_TOKEN
#undef IMAGE_REL_MIPS_JMPADDR16
#undef IMAGE_REL_MIPS_REFWORDNB
#undef IMAGE_REL_MIPS_PAIR
#undef IMAGE_REL_ALPHA_ABSOLUTE
#undef IMAGE_REL_ALPHA_REFLONG
#undef IMAGE_REL_ALPHA_REFQUAD
#undef IMAGE_REL_ALPHA_GPREL32
#undef IMAGE_REL_ALPHA_LITERAL
#undef IMAGE_REL_ALPHA_LITUSE
#undef IMAGE_REL_ALPHA_GPDISP
#undef IMAGE_REL_ALPHA_BRADDR
#undef IMAGE_REL_ALPHA_HINT
#undef IMAGE_REL_ALPHA_INLINE_REFLONG
#undef IMAGE_REL_ALPHA_REFHI
#undef IMAGE_REL_ALPHA_REFLO
#undef IMAGE_REL_ALPHA_PAIR
#undef IMAGE_REL_ALPHA_MATCH
#undef IMAGE_REL_ALPHA_SECTION
#undef IMAGE_REL_ALPHA_SECREL
#undef IMAGE_REL_ALPHA_REFLONGNB
#undef IMAGE_REL_ALPHA_SECRELLO
#undef IMAGE_REL_ALPHA_SECRELHI
#undef IMAGE_REL_ALPHA_REFQ3
#undef IMAGE_REL_ALPHA_REFQ2
#undef IMAGE_REL_ALPHA_REFQ1
#undef IMAGE_REL_ALPHA_GPRELLO
#undef IMAGE_REL_ALPHA_GPRELHI
#undef IMAGE_REL_PPC_ABSOLUTE
#undef IMAGE_REL_PPC_ADDR64
#undef IMAGE_REL_PPC_ADDR32
#undef IMAGE_REL_PPC_ADDR24
#undef IMAGE_REL_PPC_ADDR16
#undef IMAGE_REL_PPC_ADDR14
#undef IMAGE_REL_PPC_REL24
#undef IMAGE_REL_PPC_REL14
#undef IMAGE_REL_PPC_TOCREL16
#undef IMAGE_REL_PPC_TOCREL14
#undef IMAGE_REL_PPC_ADDR32NB
#undef IMAGE_REL_PPC_SECREL
#undef IMAGE_REL_PPC_SECTION
#undef IMAGE_REL_PPC_IFGLUE
#undef IMAGE_REL_PPC_IMGLUE
#undef IMAGE_REL_PPC_SECREL16
#undef IMAGE_REL_PPC_REFHI
#undef IMAGE_REL_PPC_REFLO
#undef IMAGE_REL_PPC_PAIR
#undef IMAGE_REL_PPC_SECRELLO
#undef IMAGE_REL_PPC_SECRELHI
#undef IMAGE_REL_PPC_GPREL
#undef IMAGE_REL_PPC_TOKEN
#undef IMAGE_REL_PPC_TYPEMASK
#undef IMAGE_REL_PPC_NEG
#undef IMAGE_REL_PPC_BRTAKEN
#undef IMAGE_REL_PPC_BRNTAKEN
#undef IMAGE_REL_PPC_TOCDEFN
#undef IMAGE_REL_SH3_ABSOLUTE
#undef IMAGE_REL_SH3_DIRECT16
#undef IMAGE_REL_SH3_DIRECT32
#undef IMAGE_REL_SH3_DIRECT8
#undef IMAGE_REL_SH3_DIRECT8_WORD
#undef IMAGE_REL_SH3_DIRECT8_LONG
#undef IMAGE_REL_SH3_DIRECT4
#undef IMAGE_REL_SH3_DIRECT4_WORD
#undef IMAGE_REL_SH3_DIRECT4_LONG
#undef IMAGE_REL_SH3_PCREL8_WORD
#undef IMAGE_REL_SH3_PCREL8_LONG
#undef IMAGE_REL_SH3_PCREL12_WORD
#undef IMAGE_REL_SH3_STARTOF_SECTION
#undef IMAGE_REL_SH3_SIZEOF_SECTION
#undef IMAGE_REL_SH3_SECTION
#undef IMAGE_REL_SH3_SECREL
#undef IMAGE_REL_SH3_DIRECT32_NB
#undef IMAGE_REL_SH3_GPREL4_LONG
#undef IMAGE_REL_SH3_TOKEN
#undef IMAGE_REL_SHM_PCRELPT
#undef IMAGE_REL_SHM_REFLO
#undef IMAGE_REL_SHM_REFHALF
#undef IMAGE_REL_SHM_RELLO
#undef IMAGE_REL_SHM_RELHALF
#undef IMAGE_REL_SHM_PAIR
#undef IMAGE_REL_SH_NOMODE
#undef IMAGE_REL_ARM_ABSOLUTE
#undef IMAGE_REL_ARM_ADDR32
#undef IMAGE_REL_ARM_ADDR32NB
#undef IMAGE_REL_ARM_BRANCH24
#undef IMAGE_REL_ARM_BRANCH11
#undef IMAGE_REL_ARM_TOKEN
#undef IMAGE_REL_ARM_GPREL12
#undef IMAGE_REL_ARM_GPREL7
#undef IMAGE_REL_ARM_BLX24
#undef IMAGE_REL_ARM_BLX11
#undef IMAGE_REL_ARM_SECTION
#undef IMAGE_REL_ARM_SECREL
#undef IMAGE_REL_ARM_MOV32A
#undef IMAGE_REL_ARM_MOV32
#undef IMAGE_REL_ARM_MOV32T
#undef IMAGE_REL_THUMB_MOV32
#undef IMAGE_REL_ARM_BRANCH20T
#undef IMAGE_REL_THUMB_BRANCH20
#undef IMAGE_REL_ARM_BRANCH24T
#undef IMAGE_REL_THUMB_BRANCH24
#undef IMAGE_REL_ARM_BLX23T
#undef IMAGE_REL_THUMB_BLX23
#undef IMAGE_REL_AM_ABSOLUTE
#undef IMAGE_REL_AM_ADDR32
#undef IMAGE_REL_AM_ADDR32NB
#undef IMAGE_REL_AM_CALL32
#undef IMAGE_REL_AM_FUNCINFO
#undef IMAGE_REL_AM_REL32_1
#undef IMAGE_REL_AM_REL32_2
#undef IMAGE_REL_AM_SECREL
#undef IMAGE_REL_AM_SECTION
#undef IMAGE_REL_AM_TOKEN
#undef IMAGE_REL_AMD64_ABSOLUTE
#undef IMAGE_REL_AMD64_ADDR64
#undef IMAGE_REL_AMD64_ADDR32
#undef IMAGE_REL_AMD64_ADDR32NB
#undef IMAGE_REL_AMD64_REL32
#undef IMAGE_REL_AMD64_REL32_1
#undef IMAGE_REL_AMD64_REL32_2
#undef IMAGE_REL_AMD64_REL32_3
#undef IMAGE_REL_AMD64_REL32_4
#undef IMAGE_REL_AMD64_REL32_5
#undef IMAGE_REL_AMD64_SECTION
#undef IMAGE_REL_AMD64_SECREL
#undef IMAGE_REL_AMD64_SECREL7
#undef IMAGE_REL_AMD64_TOKEN
#undef IMAGE_REL_AMD64_SREL32
#undef IMAGE_REL_AMD64_PAIR
#undef IMAGE_REL_AMD64_SSPAN32
#undef IMAGE_REL_IA64_ABSOLUTE
#undef IMAGE_REL_IA64_IMM14
#undef IMAGE_REL_IA64_IMM22
#undef IMAGE_REL_IA64_IMM64
#undef IMAGE_REL_IA64_DIR32
#undef IMAGE_REL_IA64_DIR64
#undef IMAGE_REL_IA64_PCREL21B
#undef IMAGE_REL_IA64_PCREL21M
#undef IMAGE_REL_IA64_PCREL21F
#undef IMAGE_REL_IA64_GPREL22
#undef IMAGE_REL_IA64_LTOFF22
#undef IMAGE_REL_IA64_SECTION
#undef IMAGE_REL_IA64_SECREL22
#undef IMAGE_REL_IA64_SECREL64I
#undef IMAGE_REL_IA64_SECREL32
#undef IMAGE_REL_IA64_DIR32NB
#undef IMAGE_REL_IA64_SREL14
#undef IMAGE_REL_IA64_SREL22
#undef IMAGE_REL_IA64_SREL32
#undef IMAGE_REL_IA64_UREL32
#undef IMAGE_REL_IA64_PCREL60X
#undef IMAGE_REL_IA64_PCREL60B
#undef IMAGE_REL_IA64_PCREL60F
#undef IMAGE_REL_IA64_PCREL60I
#undef IMAGE_REL_IA64_PCREL60M
#undef IMAGE_REL_IA64_IMMGPREL64
#undef IMAGE_REL_IA64_TOKEN
#undef IMAGE_REL_IA64_GPREL32
#undef IMAGE_REL_IA64_ADDEND
#undef IMAGE_REL_CEF_ABSOLUTE
#undef IMAGE_REL_CEF_ADDR32
#undef IMAGE_REL_CEF_ADDR64
#undef IMAGE_REL_CEF_ADDR32NB
#undef IMAGE_REL_CEF_SECTION
#undef IMAGE_REL_CEF_SECREL
#undef IMAGE_REL_CEF_TOKEN
#undef IMAGE_REL_CEE_ABSOLUTE
#undef IMAGE_REL_CEE_ADDR32
#undef IMAGE_REL_CEE_ADDR64
#undef IMAGE_REL_CEE_ADDR32NB
#undef IMAGE_REL_CEE_SECTION
#undef IMAGE_REL_CEE_SECREL
#undef IMAGE_REL_CEE_TOKEN
#undef IMAGE_REL_M32R_ABSOLUTE
#undef IMAGE_REL_M32R_ADDR32
#undef IMAGE_REL_M32R_ADDR32NB
#undef IMAGE_REL_M32R_ADDR24
#undef IMAGE_REL_M32R_GPREL16
#undef IMAGE_REL_M32R_PCREL24
#undef IMAGE_REL_M32R_PCREL16
#undef IMAGE_REL_M32R_PCREL8
#undef IMAGE_REL_M32R_REFHALF
#undef IMAGE_REL_M32R_REFHI
#undef IMAGE_REL_M32R_REFLO
#undef IMAGE_REL_M32R_PAIR
#undef IMAGE_REL_M32R_SECTION
#undef IMAGE_REL_M32R_SECREL32
#undef IMAGE_REL_M32R_TOKEN
#undef IMAGE_REL_EBC_ABSOLUTE
#undef IMAGE_REL_EBC_ADDR32NB
#undef IMAGE_REL_EBC_REL32
#undef IMAGE_REL_EBC_SECTION
#undef IMAGE_REL_EBC_SECREL
#undef IMAGE_SIZEOF_BASE_RELOCATION
#undef IMAGE_REL_BASED_ABSOLUTE
#undef IMAGE_REL_BASED_HIGH
#undef IMAGE_REL_BASED_LOW
#undef IMAGE_REL_BASED_HIGHLOW
#undef IMAGE_REL_BASED_HIGHADJ
#undef IMAGE_REL_BASED_MIPS_JMPADDR
#undef IMAGE_REL_BASED_ARM_MOV32
#undef IMAGE_REL_BASED_THUMB_MOV32
#undef IMAGE_REL_BASED_MIPS_JMPADDR16
#undef IMAGE_REL_BASED_IA64_IMM64
#undef IMAGE_REL_BASED_DIR64
#undef IMAGE_ARCHIVE_START_SIZE
#undef IMAGE_ARCHIVE_START
#undef IMAGE_ARCHIVE_END
#undef IMAGE_ARCHIVE_PAD
#undef IMAGE_ARCHIVE_LINKER_MEMBER
#undef IMAGE_ARCHIVE_LONGNAMES_MEMBER
#undef IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR
#undef IMAGE_ORDINAL_FLAG64
#undef IMAGE_ORDINAL_FLAG32
#undef IMAGE_ORDINAL64
#undef IMAGE_ORDINAL32
#undef IMAGE_SNAP_BY_ORDINAL64
#undef IMAGE_SNAP_BY_ORDINAL32
#undef IMAGE_ORDINAL_FLAG
#undef IMAGE_ORDINAL
#undef IMAGE_SNAP_BY_ORDINAL
#undef IMAGE_ORDINAL_FLAG
#undef IMAGE_ORDINAL
#undef IMAGE_SNAP_BY_ORDINAL
#undef IMAGE_RESOURCE_NAME_IS_STRING
#undef IMAGE_RESOURCE_DATA_IS_DIRECTORY
#undef IMAGE_DEBUG_TYPE_UNKNOWN
#undef IMAGE_DEBUG_TYPE_COFF
#undef IMAGE_DEBUG_TYPE_CODEVIEW
#undef IMAGE_DEBUG_TYPE_FPO
#undef IMAGE_DEBUG_TYPE_MISC
#undef IMAGE_DEBUG_TYPE_EXCEPTION
#undef IMAGE_DEBUG_TYPE_FIXUP
#undef IMAGE_DEBUG_TYPE_OMAP_TO_SRC
#undef IMAGE_DEBUG_TYPE_OMAP_FROM_SRC
#undef IMAGE_DEBUG_TYPE_BORLAND
#undef IMAGE_DEBUG_TYPE_RESERVED10
#undef IMAGE_DEBUG_TYPE_CLSID
#undef IMAGE_DEBUG_MISC_EXENAME
#undef IMAGE_SEPARATE_DEBUG_SIGNATURE
#undef IMAGE_SEPARATE_DEBUG_FLAGS_MASK
#undef IMAGE_SEPARATE_DEBUG_MISMATCH
#endif

#ifndef _MSC_VER
// The following macros are defined to facilitate the lack of 'uuid' on Linux.

constexpr uint8_t nybble_from_hex(char c) {
  return ((c >= '0' && c <= '9')
              ? (c - '0')
              : ((c >= 'a' && c <= 'f')
                     ? (c - 'a' + 10)
                     : ((c >= 'A' && c <= 'F') ? (c - 'A' + 10)
                                               : /* Should be an error */ -1)));
}

constexpr uint8_t byte_from_hex(char c1, char c2) {
  return nybble_from_hex(c1) << 4 | nybble_from_hex(c2);
}

constexpr uint8_t byte_from_hexstr(const char str[2]) {
  return nybble_from_hex(str[0]) << 4 | nybble_from_hex(str[1]);
}

constexpr GUID guid_from_string(const char str[37]) {
  return GUID{static_cast<uint32_t>(byte_from_hexstr(str)) << 24 |
                  static_cast<uint32_t>(byte_from_hexstr(str + 2)) << 16 |
                  static_cast<uint32_t>(byte_from_hexstr(str + 4)) << 8 |
                  byte_from_hexstr(str + 6),
              static_cast<uint16_t>(
                  static_cast<uint16_t>(byte_from_hexstr(str + 9)) << 8 |
                  byte_from_hexstr(str + 11)),
              static_cast<uint16_t>(
                  static_cast<uint16_t>(byte_from_hexstr(str + 14)) << 8 |
                  byte_from_hexstr(str + 16)),
              {byte_from_hexstr(str + 19), byte_from_hexstr(str + 21),
               byte_from_hexstr(str + 24), byte_from_hexstr(str + 26),
               byte_from_hexstr(str + 28), byte_from_hexstr(str + 30),
               byte_from_hexstr(str + 32), byte_from_hexstr(str + 34)}};
}
#endif // _MSC_VER

#ifndef _WIN32
#define COM_NO_WINDOWS_H // needed to inform d3d headers that this isn't windows

//===----------------------------------------------------------------------===//
//
//                             Begin: Macro Definitions
//
//===----------------------------------------------------------------------===//
#define C_ASSERT(expr) static_assert((expr), "")

#define CoTaskMemAlloc malloc
#define CoTaskMemFree free

#define ARRAYSIZE(array) (sizeof(array) / sizeof(array[0]))

#define _countof(a) (sizeof(a) / sizeof(*(a)))

#define STDMETHODCALLTYPE
#define STDMETHODIMP_(type) type STDMETHODCALLTYPE
#define STDMETHODIMP STDMETHODIMP_(HRESULT)
#define STDMETHOD_(type, name) virtual STDMETHODIMP_(type) name
#define STDMETHOD(name) STDMETHOD_(HRESULT, name)
#define EXTERN_C extern "C"

#define UNREFERENCED_PARAMETER(P) (void)(P)

#define RtlEqualMemory(Destination, Source, Length)                            \
  (!memcmp((Destination), (Source), (Length)))
#define RtlMoveMemory(Destination, Source, Length)                             \
  memmove((Destination), (Source), (Length))
#define RtlCopyMemory(Destination, Source, Length)                             \
  memcpy((Destination), (Source), (Length))
#define RtlFillMemory(Destination, Length, Fill)                               \
  memset((Destination), (Fill), (Length))
#define RtlZeroMemory(Destination, Length) memset((Destination), 0, (Length))
#define MoveMemory RtlMoveMemory
#define CopyMemory RtlCopyMemory
#define FillMemory RtlFillMemory
#define ZeroMemory RtlZeroMemory

#define FALSE 0
#define TRUE 1

// We ignore the code page completely on Linux.
#define GetConsoleOutputCP() 0

#define _HRESULT_TYPEDEF_(_sc) ((HRESULT)_sc)
#define DISP_E_BADINDEX _HRESULT_TYPEDEF_(0x8002000BL)
#define REGDB_E_CLASSNOTREG _HRESULT_TYPEDEF_(0x80040154L)

// This is an unsafe conversion. If needed, we can later implement a safe
// conversion that throws exceptions for overflow cases.
#define UIntToInt(uint_arg, int_ptr_arg) *int_ptr_arg = uint_arg

#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR) - 1)

// Use errno to implement {Get|Set}LastError
#define GetLastError() errno
#define SetLastError(ERR) errno = ERR

// Map these errors to equivalent errnos.
#define ERROR_SUCCESS 0L
#define ERROR_ARITHMETIC_OVERFLOW EOVERFLOW
#define ERROR_FILE_NOT_FOUND ENOENT
#define ERROR_FUNCTION_NOT_CALLED ENOSYS
#define ERROR_IO_DEVICE EIO
#define ERROR_INSUFFICIENT_BUFFER ENOBUFS
#define ERROR_INVALID_HANDLE EBADF
#define ERROR_INVALID_PARAMETER EINVAL
#define ERROR_OUT_OF_STRUCTURES ENOMEM
#define ERROR_NOT_CAPABLE EPERM
#define ERROR_NOT_FOUND ENOTSUP
#define ERROR_UNHANDLED_EXCEPTION EBADF
#define ERROR_BROKEN_PIPE EPIPE

// Used by HRESULT <--> WIN32 error code conversion
#define SEVERITY_ERROR 1
#define FACILITY_WIN32 7
#define HRESULT_CODE(hr) ((hr) & 0xFFFF)
#define MAKE_HRESULT(severity, facility, code)                                 \
  ((HRESULT)(((unsigned long)(severity) << 31) |                               \
             ((unsigned long)(facility) << 16) | ((unsigned long)(code))))

#define FILE_TYPE_UNKNOWN 0x0000
#define FILE_TYPE_DISK 0x0001
#define FILE_TYPE_CHAR 0x0002
#define FILE_TYPE_PIPE 0x0003
#define FILE_TYPE_REMOTE 0x8000

#define FILE_ATTRIBUTE_NORMAL 0x00000080
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define INVALID_FILE_ATTRIBUTES ((DWORD) - 1)

#define STDOUT_FILENO 1
#define STDERR_FILENO 2

// STGTY ENUMS
#define STGTY_STORAGE 1
#define STGTY_STREAM 2
#define STGTY_LOCKBYTES 3
#define STGTY_PROPERTY 4

// Storage errors
#define STG_E_INVALIDFUNCTION 1L
#define STG_E_ACCESSDENIED 2L

#define STREAM_SEEK_SET 0
#define STREAM_SEEK_CUR 1
#define STREAM_SEEK_END 2

#define HEAP_NO_SERIALIZE 0x1
#define HEAP_ZERO_MEMORY 0x8

#define MB_ERR_INVALID_CHARS 0x00000008 // error for invalid chars

// File IO

#define CREATE_ALWAYS 2
#define CREATE_NEW 1
#define OPEN_ALWAYS 4
#define OPEN_EXISTING 3
#define TRUNCATE_EXISTING 5

#define FILE_SHARE_DELETE 0x00000004
#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002

#define GENERIC_READ 0x80000000
#define GENERIC_WRITE 0x40000000

#define _atoi64 atoll
#define sprintf_s snprintf
#define _strdup strdup
#define _strnicmp strnicmp

#define vsnprintf_s vsnprintf
#define strcat_s strcat
#define strcpy_s(dst, n, src) strncpy(dst, src, n)
#define _vscwprintf vwprintf
#define vswprintf_s vswprintf
#define swprintf_s swprintf

#define StringCchCopyW(dst, n, src) wcsncpy(dst, src, n)

#define OutputDebugStringW(msg) fputws(msg, stderr)

#define UInt32Add UIntAdd
#define Int32ToUInt32 IntToUInt

//===--------------------- HRESULT Related Macros -------------------------===//

#define S_OK ((HRESULT)0L)
#define S_FALSE ((HRESULT)1L)

#define E_ABORT (HRESULT)0x80004004
#define E_ACCESSDENIED (HRESULT)0x80070005
#define E_BOUNDS (HRESULT)0x8000000B
#define E_FAIL (HRESULT)0x80004005
#define E_HANDLE (HRESULT)0x80070006
#define E_INVALIDARG (HRESULT)0x80070057
#define E_NOINTERFACE (HRESULT)0x80004002
#define E_NOTIMPL (HRESULT)0x80004001
#define E_NOT_VALID_STATE (HRESULT)0x8007139F
#define E_OUTOFMEMORY (HRESULT)0x8007000E
#define E_POINTER (HRESULT)0x80004003
#define E_UNEXPECTED (HRESULT)0x8000FFFF

#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
#define FAILED(hr) (((HRESULT)(hr)) < 0)

#define HRESULT_FROM_WIN32(x)                                                  \
  (HRESULT)(x) <= 0 ? (HRESULT)(x)                                             \
                    : (HRESULT)(((x) & 0x0000FFFF) | (7 << 16) | 0x80000000)

//===----------------------------------------------------------------------===//
//
//                         Begin: Disable SAL Annotations
//
//===----------------------------------------------------------------------===//
#define _In_
#define _In_z_
#define _In_opt_
#define _In_opt_count_(size)
#define _In_opt_z_
#define _In_count_(size)
#define _In_bytecount_(size)

#define _Out_
#define _Out_opt_
#define _Outptr_
#define _Outptr_opt_
#define _Outptr_result_z_
#define _Outptr_opt_result_z_
#define _Outptr_result_maybenull_
#define _Outptr_result_nullonfailure_
#define _Outptr_result_buffer_maybenull_(ptr)
#define _Outptr_result_buffer_(ptr)

#define _COM_Outptr_
#define _COM_Outptr_opt_
#define _COM_Outptr_result_maybenull_
#define _COM_Outptr_opt_result_maybenull_

#define THIS_
#define THIS
#define PURE = 0

#define _Maybenull_

#define __debugbreak()

// GCC produces erros on calling convention attributes.
#ifdef __GNUC__
#define __cdecl
#define __CRTDECL
#define __stdcall
#define __vectorcall
#define __thiscall
#define __fastcall
#define __clrcall
#endif // __GNUC__

//===----------------------------------------------------------------------===//
//
//                             Begin: Type Definitions
//
//===----------------------------------------------------------------------===//

typedef unsigned char BYTE, UINT8;
typedef unsigned char *LPBYTE;

typedef BYTE BOOLEAN;
typedef BOOLEAN *PBOOLEAN;

typedef bool BOOL;
typedef BOOL *LPBOOL;

typedef int INT;
typedef long LONG;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef long long LONGLONG;
typedef long long LONG_PTR;
typedef unsigned long long ULONG_PTR;
typedef unsigned long long ULONGLONG;

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef DWORD *LPDWORD;

typedef uint32_t UINT32;
typedef uint64_t UINT64;

typedef signed char INT8, *PINT8;
typedef signed int INT32, *PINT32;

typedef size_t SIZE_T;
typedef const char *LPCSTR;
typedef const char *PCSTR;

typedef int errno_t;

typedef wchar_t WCHAR;
typedef wchar_t *LPWSTR;
typedef wchar_t *PWCHAR;
typedef const wchar_t *LPCWSTR;
typedef const wchar_t *PCWSTR;

typedef WCHAR OLECHAR;
typedef OLECHAR *BSTR;
typedef OLECHAR *LPOLESTR;
typedef char *LPSTR;

typedef void *LPVOID;
typedef const void *LPCVOID;

typedef std::nullptr_t nullptr_t;

typedef signed int HRESULT;

//===--------------------- Handle Types -----------------------------------===//

typedef void *HANDLE;
typedef void *RPC_IF_HANDLE;

#define DECLARE_HANDLE(name)                                                   \
  struct name##__ {                                                            \
    int unused;                                                                \
  };                                                                           \
  typedef struct name##__ *name
DECLARE_HANDLE(HINSTANCE);

typedef void *HMODULE;

#define STD_INPUT_HANDLE ((DWORD) - 10)
#define STD_OUTPUT_HANDLE ((DWORD) - 11)
#define STD_ERROR_HANDLE ((DWORD) - 12)

//===--------------------- ID Types and Macros for COM --------------------===//

typedef GUID CLSID;
typedef const GUID &REFGUID;
typedef const GUID &REFCLSID;

typedef GUID IID;
typedef IID *LPIID;
typedef const IID &REFIID;
inline bool IsEqualGUID(REFGUID rguid1, REFGUID rguid2) {
  // Optimization:
  if (&rguid1 == &rguid2)
    return true;

  return !memcmp(&rguid1, &rguid2, sizeof(GUID));
}

inline bool operator==(REFGUID guidOne, REFGUID guidOther) {
  return !!IsEqualGUID(guidOne, guidOther);
}

inline bool operator!=(REFGUID guidOne, REFGUID guidOther) {
  return !(guidOne == guidOther);
}

inline bool IsEqualIID(REFIID riid1, REFIID riid2) {
  return IsEqualGUID(riid1, riid2);
}

inline bool IsEqualCLSID(REFCLSID rclsid1, REFCLSID rclsid2) {
  return IsEqualGUID(rclsid1, rclsid2);
}

//===--------------------- Struct Types -----------------------------------===//

typedef struct _FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

typedef struct _BY_HANDLE_FILE_INFORMATION {
  DWORD dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD dwVolumeSerialNumber;
  DWORD nFileSizeHigh;
  DWORD nFileSizeLow;
  DWORD nNumberOfLinks;
  DWORD nFileIndexHigh;
  DWORD nFileIndexLow;
} BY_HANDLE_FILE_INFORMATION, *PBY_HANDLE_FILE_INFORMATION,
    *LPBY_HANDLE_FILE_INFORMATION;

typedef struct _WIN32_FIND_DATAW {
  DWORD dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD nFileSizeHigh;
  DWORD nFileSizeLow;
  DWORD dwReserved0;
  DWORD dwReserved1;
  WCHAR cFileName[260];
  WCHAR cAlternateFileName[14];
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    DWORD HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER;

typedef LARGE_INTEGER *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
  struct {
    DWORD LowPart;
    DWORD HighPart;
  } u;
  ULONGLONG QuadPart;
} ULARGE_INTEGER;

typedef ULARGE_INTEGER *PULARGE_INTEGER;

typedef struct tagSTATSTG {
  LPOLESTR pwcsName;
  DWORD type;
  ULARGE_INTEGER cbSize;
  FILETIME mtime;
  FILETIME ctime;
  FILETIME atime;
  DWORD grfMode;
  DWORD grfLocksSupported;
  CLSID clsid;
  DWORD grfStateBits;
  DWORD reserved;
} STATSTG;

enum tagSTATFLAG {
  STATFLAG_DEFAULT = 0,
  STATFLAG_NONAME = 1,
  STATFLAG_NOOPEN = 2
};

//===--------------------- UUID Related Macros ----------------------------===//

#ifdef __EMULATE_UUID

// The following macros are defined to facilitate the lack of 'uuid' on Linux.

template <typename interface> inline GUID __emulated_uuidof();

#define CROSS_PLATFORM_UUIDOF(interface, spec)                                 \
  struct interface;                                                            \
  template <> inline GUID __emulated_uuidof<interface>() {                     \
    static const IID _IID = guid_from_string(spec);                            \
    return _IID;                                                               \
  }

#define __uuidof(T) __emulated_uuidof<typename std::decay<T>::type>()

#define IID_PPV_ARGS(ppType)                                                   \
  __uuidof(decltype(**(ppType))), reinterpret_cast<void **>(ppType)

#else // __EMULATE_UUID

#ifndef CROSS_PLATFORM_UUIDOF
// Warning: This macro exists in dxcapi.h as well
#define CROSS_PLATFORM_UUIDOF(interface, spec)                                 \
  struct __declspec(uuid(spec)) interface;
#endif

template <typename T> inline void **IID_PPV_ARGS_Helper(T **pp) {
  return reinterpret_cast<void **>(pp);
}
#define IID_PPV_ARGS(ppType) __uuidof(**(ppType)), IID_PPV_ARGS_Helper(ppType)

#endif // __EMULATE_UUID

// Needed for d3d headers, but fail to create actual interfaces
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)           \
  const GUID name = {l, w1, w2, {b1, b2, b3, b4, b5, b6, b7, b8}}
#define DECLSPEC_UUID(x)
#define MIDL_INTERFACE(x) struct DECLSPEC_UUID(x)
#define DECLARE_INTERFACE(iface) struct iface
#define DECLARE_INTERFACE_(iface, parent) DECLARE_INTERFACE(iface) : parent

//===--------------------- COM Interfaces ---------------------------------===//

CROSS_PLATFORM_UUIDOF(IUnknown, "00000000-0000-0000-C000-000000000046")
struct IUnknown {
  IUnknown() {};
  virtual HRESULT QueryInterface(REFIID riid, void **ppvObject) = 0;
  virtual ULONG AddRef() = 0;
  virtual ULONG Release() = 0;
  template <class Q> HRESULT QueryInterface(Q **pp) {
    return QueryInterface(__uuidof(Q), (void **)pp);
  }
};

CROSS_PLATFORM_UUIDOF(INoMarshal, "ECC8691B-C1DB-4DC0-855E-65F6C551AF49")
struct INoMarshal : public IUnknown {};

CROSS_PLATFORM_UUIDOF(IMalloc, "00000002-0000-0000-C000-000000000046")
struct IMalloc : public IUnknown {
  virtual void *Alloc(SIZE_T size) = 0;
  virtual void *Realloc(void *ptr, SIZE_T size) = 0;
  virtual void Free(void *ptr) = 0;
  virtual SIZE_T GetSize(void *pv) = 0;
  virtual int DidAlloc(void *pv) = 0;
  virtual void HeapMinimize(void) = 0;
};

CROSS_PLATFORM_UUIDOF(ISequentialStream, "0C733A30-2A1C-11CE-ADE5-00AA0044773D")
struct ISequentialStream : public IUnknown {
  virtual HRESULT Read(void *pv, ULONG cb, ULONG *pcbRead) = 0;
  virtual HRESULT Write(const void *pv, ULONG cb, ULONG *pcbWritten) = 0;
};

CROSS_PLATFORM_UUIDOF(IStream, "0000000c-0000-0000-C000-000000000046")
struct IStream : public ISequentialStream {
  virtual HRESULT Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin,
                       ULARGE_INTEGER *plibNewPosition) = 0;
  virtual HRESULT SetSize(ULARGE_INTEGER libNewSize) = 0;
  virtual HRESULT CopyTo(IStream *pstm, ULARGE_INTEGER cb,
                         ULARGE_INTEGER *pcbRead,
                         ULARGE_INTEGER *pcbWritten) = 0;

  virtual HRESULT Commit(DWORD grfCommitFlags) = 0;

  virtual HRESULT Revert(void) = 0;

  virtual HRESULT LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb,
                             DWORD dwLockType) = 0;

  virtual HRESULT UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb,
                               DWORD dwLockType) = 0;

  virtual HRESULT Stat(STATSTG *pstatstg, DWORD grfStatFlag) = 0;

  virtual HRESULT Clone(IStream **ppstm) = 0;
};

// These don't need stub implementations as they come from the DirectX Headers
// They still need the __uuidof() though
CROSS_PLATFORM_UUIDOF(ID3D12LibraryReflection,
                      "8E349D19-54DB-4A56-9DC9-119D87BDB804")
CROSS_PLATFORM_UUIDOF(ID3D12ShaderReflection,
                      "5A58797D-A72C-478D-8BA2-EFC6B0EFE88E")

//===--------------------------- BSTR Allocation --------------------------===//

void SysFreeString(BSTR bstrString);
// Allocate string with length prefix
BSTR SysAllocStringLen(const OLECHAR *strIn, UINT ui);

//===--------------------------- BSTR Length ------------------------------===//
unsigned int SysStringLen(const BSTR bstrString);

//===--------------------- UTF-8 Related Types ----------------------------===//

// Code Page
#define CP_ACP 0
#define CP_UTF8 65001 // UTF-8 translation.

#endif

#ifndef CROSS_PLATFORM_UUIDOF
// Warning: This macro exists in dxcapi.h as well
#define CROSS_PLATFORM_UUIDOF(interface, spec)                                 \
  extern "C++" {                                                               \
  struct __declspec(uuid(spec)) interface;                                     \
  template<> struct __mingw_uuidof_s<interface> {                              \
    static constexpr IID __uuid_inst = guid_from_string(spec);                 \
  };                                                                           \
  template <> constexpr const GUID &__mingw_uuidof<interface>() {              \
    return __mingw_uuidof_s<interface>::__uuid_inst;                           \
  }                                                                            \
  template <> constexpr const GUID &__mingw_uuidof<interface *>() {            \
    return __mingw_uuidof_s<interface>::__uuid_inst;                           \
  }                                                                            \
  }
#endif

#if !defined(_MSC_VER)
#define DXC_FAILED(hr) (((HRESULT)(hr)) < 0)
#define ATLASSERT assert

// Event Tracing for Windows (ETW) provides application programmers the ability
// to start and stop event tracing sessions, instrument an application to
// provide trace events, and consume trace events.
#define DxcEtw_DXCompilerCreateInstance_Start()
#define DxcEtw_DXCompilerCreateInstance_Stop(hr)
#define DxcEtw_DXCompilerCompile_Start()
#define DxcEtw_DXCompilerCompile_Stop(hr)
#define DxcEtw_DXCompilerDisassemble_Start()
#define DxcEtw_DXCompilerDisassemble_Stop(hr)
#define DxcEtw_DXCompilerPreprocess_Start()
#define DxcEtw_DXCompilerPreprocess_Stop(hr)
#define DxcEtw_DxcValidation_Start()
#define DxcEtw_DxcValidation_Stop(hr)

#define OutputDebugStringA(msg) fputs(msg, stderr)
#define OutputDebugFormatA(...) fprintf(stderr, __VA_ARGS__)

//===--------------------- COM Pointer Types ------------------------------===//
class CAllocator {
public:
  static void *Reallocate(void *p, size_t nBytes) throw();
  static void *Allocate(size_t nBytes) throw();
  static void Free(void *p) throw();
};

template <class T> class CComPtrBase {
protected:
  CComPtrBase() throw() { p = nullptr; }
  CComPtrBase(T *lp) throw() {
    p = lp;
    if (p != nullptr)
      p->AddRef();
  }
  void Swap(CComPtrBase &other) {
    T *pTemp = p;
    p = other.p;
    other.p = pTemp;
  }

public:
  ~CComPtrBase() throw() {
    if (p) {
      p->Release();
      p = nullptr;
    }
  }
  operator T *() const throw() { return p; }
  T &operator*() const { return *p; }
  T *operator->() const { return p; }
  T **operator&() throw() {
    assert(p == nullptr);
    return &p;
  }
  bool operator!() const throw() { return (p == nullptr); }
  bool operator<(T *pT) const throw() { return p < pT; }
  bool operator!=(T *pT) const { return !operator==(pT); }
  bool operator==(T *pT) const throw() { return p == pT; }

  // Release the interface and set to nullptr
  void Release() throw() {
    T *pTemp = p;
    if (pTemp) {
      p = nullptr;
      pTemp->Release();
    }
  }

  // Attach to an existing interface (does not AddRef)
  void Attach(T *p2) throw() {
    if (p) {
      ULONG ref = p->Release();
      (void)(ref);
      // Attaching to the same object only works if duplicate references are
      // being coalesced.  Otherwise re-attaching will cause the pointer to be
      // released and may cause a crash on a subsequent dereference.
      assert(ref != 0 || p2 != p);
    }
    p = p2;
  }

  // Detach the interface (does not Release)
  T *Detach() throw() {
    T *pt = p;
    p = nullptr;
    return pt;
  }

  HRESULT CopyTo(T **ppT) throw() {
    assert(ppT != nullptr);
    if (ppT == nullptr)
      return E_POINTER;
    *ppT = p;
    if (p)
      p->AddRef();
    return S_OK;
  }

  template <class Q> HRESULT QueryInterface(Q **pp) const throw() {
    assert(pp != nullptr);
    return p->QueryInterface(__uuidof(Q), (void **)pp);
  }

  T *p;
};

template <class T> class CComPtr : public CComPtrBase<T> {
public:
  CComPtr() throw() {}
  CComPtr(T *lp) throw() : CComPtrBase<T>(lp) {}
  CComPtr(const CComPtr<T> &lp) throw() : CComPtrBase<T>(lp.p) {}
  T *operator=(T *lp) throw() {
    if (*this != lp) {
      CComPtr(lp).Swap(*this);
    }
    return *this;
  }

  inline bool IsEqualObject(IUnknown *pOther) throw() {
    if (this->p == nullptr && pOther == nullptr)
      return true; // They are both NULL objects

    if (this->p == nullptr || pOther == nullptr)
      return false; // One is NULL the other is not

    CComPtr<IUnknown> punk1;
    CComPtr<IUnknown> punk2;
    this->p->QueryInterface(__uuidof(IUnknown), (void **)&punk1);
    pOther->QueryInterface(__uuidof(IUnknown), (void **)&punk2);
    return punk1 == punk2;
  }

  void ComPtrAssign(IUnknown **pp, IUnknown *lp, REFIID riid) {
    IUnknown *pTemp = *pp; // takes ownership
    if (lp == nullptr || FAILED(lp->QueryInterface(riid, (void **)pp)))
      *pp = nullptr;
    if (pTemp)
      pTemp->Release();
  }

  template <typename Q> T *operator=(const CComPtr<Q> &lp) throw() {
    if (!this->IsEqualObject(lp)) {
      ComPtrAssign((IUnknown **)&this->p, lp, __uuidof(T));
    }
    return *this;
  }

  // NOTE: This conversion constructor is not part of the official CComPtr spec;
  // however, it is needed to convert CComPtr<Q> to CComPtr<T> where T derives
  // from Q on Clang. MSVC compiles this conversion as first a call to
  // CComPtr<Q>::operator T*, followed by CComPtr<T>(T*), but Clang fails to
  // compile with error: no viable conversion from 'CComPtr<Q>' to 'CComPtr<T>'.
  template <typename Q>
  CComPtr(const CComPtr<Q> &lp) throw() : CComPtrBase<T>(lp.p) {}

  T *operator=(const CComPtr<T> &lp) throw() {
    if (*this != lp) {
      CComPtr(lp).Swap(*this);
    }
    return *this;
  }

  CComPtr(CComPtr<T> &&lp) throw() : CComPtrBase<T>() { lp.Swap(*this); }

  T *operator=(CComPtr<T> &&lp) throw() {
    if (*this != lp) {
      CComPtr(static_cast<CComPtr &&>(lp)).Swap(*this);
    }
    return *this;
  }
};

template <class T> class CSimpleArray : public std::vector<T> {
public:
  bool Add(const T &t) {
    this->push_back(t);
    return true;
  }
  int GetSize() { return this->size(); }
  T *GetData() { return this->data(); }
  void RemoveAll() { this->clear(); }
};

template <class T, class Allocator = CAllocator> class CHeapPtrBase {
protected:
  CHeapPtrBase() throw() : m_pData(NULL) {}
  CHeapPtrBase(CHeapPtrBase<T, Allocator> &p) throw() {
    m_pData = p.Detach(); // Transfer ownership
  }
  explicit CHeapPtrBase(T *pData) throw() : m_pData(pData) {}

public:
  ~CHeapPtrBase() throw() { Free(); }

protected:
  CHeapPtrBase<T, Allocator> &operator=(CHeapPtrBase<T, Allocator> &p) throw() {
    if (m_pData != p.m_pData)
      Attach(p.Detach()); // Transfer ownership
    return *this;
  }

public:
  operator T *() const throw() { return m_pData; }
  T *operator->() const throw() {
    assert(m_pData != NULL);
    return m_pData;
  }

  T **operator&() throw() {
    assert(m_pData == NULL);
    return &m_pData;
  }

  // Allocate a buffer with the given number of bytes
  bool AllocateBytes(size_t nBytes) throw() {
    assert(m_pData == NULL);
    m_pData = static_cast<T *>(Allocator::Allocate(nBytes * sizeof(char)));
    if (m_pData == NULL)
      return false;

    return true;
  }

  // Attach to an existing pointer (takes ownership)
  void Attach(T *pData) throw() {
    Allocator::Free(m_pData);
    m_pData = pData;
  }

  // Detach the pointer (releases ownership)
  T *Detach() throw() {
    T *pTemp = m_pData;
    m_pData = NULL;
    return pTemp;
  }

  // Free the memory pointed to, and set the pointer to NULL
  void Free() throw() {
    Allocator::Free(m_pData);
    m_pData = NULL;
  }

  // Reallocate the buffer to hold a given number of bytes
  bool ReallocateBytes(size_t nBytes) throw() {
    T *pNew;
    pNew =
        static_cast<T *>(Allocator::Reallocate(m_pData, nBytes * sizeof(char)));
    if (pNew == NULL)
      return false;
    m_pData = pNew;

    return true;
  }

public:
  T *m_pData;
};

template <typename T, class Allocator = CAllocator>
class CHeapPtr : public CHeapPtrBase<T, Allocator> {
public:
  CHeapPtr() throw() {}
  CHeapPtr(CHeapPtr<T, Allocator> &p) throw() : CHeapPtrBase<T, Allocator>(p) {}
  explicit CHeapPtr(T *p) throw() : CHeapPtrBase<T, Allocator>(p) {}
  CHeapPtr<T> &operator=(CHeapPtr<T, Allocator> &p) throw() {
    CHeapPtrBase<T, Allocator>::operator=(p);
    return *this;
  }

  // Allocate a buffer with the given number of elements
  bool Allocate(size_t nElements = 1) throw() {
    size_t nBytes = nElements * sizeof(T);
    return this->AllocateBytes(nBytes);
  }

  // Reallocate the buffer to hold a given number of elements
  bool Reallocate(size_t nElements) throw() {
    size_t nBytes = nElements * sizeof(T);
    return this->ReallocateBytes(nBytes);
  }
};

#define CComHeapPtr CHeapPtr

// RAII style mechanism for setting/unsetting a locale for the specified Windows
// codepage
#ifdef __linux__
class ScopedLocale {
  locale_t Utf8Locale = nullptr;
  locale_t PrevLocale = nullptr;

public:
  explicit ScopedLocale(uint32_t CodePage) {
    assert((CodePage == CP_UTF8) &&
           "Support for Linux only handles UTF8 code pages");
    Utf8Locale = newlocale(LC_CTYPE_MASK, "C.UTF-8", NULL);
    if (!Utf8Locale)
      Utf8Locale = newlocale(LC_CTYPE_MASK, "C.utf8", NULL);
    if (!Utf8Locale)
      Utf8Locale = newlocale(LC_CTYPE_MASK, "en_US.UTF-8", NULL);
    assert(Utf8Locale && "Failed to create UTF-8 locale");
    if (!Utf8Locale)
      return;
    PrevLocale = uselocale(Utf8Locale);
    assert(PrevLocale && "Failed to set locale to UTF-8");
    if (!PrevLocale) {
      freelocale(Utf8Locale);
      Utf8Locale = nullptr;
    }
  }
  ~ScopedLocale() {
    if (PrevLocale != nullptr)
      uselocale(PrevLocale);
    if (Utf8Locale)
      freelocale(Utf8Locale);
    PrevLocale = nullptr;
    Utf8Locale = nullptr;
  }
};
#else
class ScopedLocale {
  const char *m_prevLocale;

public:
  explicit ScopedLocale(uint32_t codePage)
      : m_prevLocale(setlocale(LC_ALL, nullptr)) {
    assert((codePage == CP_UTF8) &&
           "Support for Linux only handles UTF8 code pages");
    setlocale(LC_ALL, "en_US.UTF-8");
  }
  ~ScopedLocale() {
    if (m_prevLocale != nullptr) {
      setlocale(LC_ALL, m_prevLocale);
    }
  }
};
#endif // __linux__

// The t_nBufferLength parameter is part of the published interface, but not
// used here.
template <int t_nBufferLength = 128> class CW2AEX {
public:
  CW2AEX(LPCWSTR psz) {
    ScopedLocale locale(CP_UTF8);

    if (!psz) {
      m_psz = NULL;
      return;
    }

    int len = (wcslen(psz) + 1) * 4;
    m_psz = new char[len];
    std::wcstombs(m_psz, psz, len);
  }

  ~CW2AEX() { delete[] m_psz; }

  operator LPSTR() const { return m_psz; }

  char *m_psz;
};
typedef CW2AEX<> CW2A;

// The t_nBufferLength parameter is part of the published interface, but not
// used here.
template <int t_nBufferLength = 128> class CA2WEX {
public:
  CA2WEX(LPCSTR psz) {
    ScopedLocale locale(CP_UTF8);

    if (!psz) {
      m_psz = NULL;
      return;
    }

    int len = strlen(psz) + 1;
    m_psz = new wchar_t[len];
    std::mbstowcs(m_psz, psz, len);
  }

  ~CA2WEX() { delete[] m_psz; }

  operator LPWSTR() const { return m_psz; }

  wchar_t *m_psz;
};

typedef CA2WEX<> CA2W;

//===--------- File IO Related Types ----------------===//

class CHandle {
public:
  CHandle(HANDLE h);
  ~CHandle();
  operator HANDLE() const throw();

private:
  HANDLE m_h;
};

/////////////////////////////////////////////////////////////////////////////
// CComBSTR

class CComBSTR {
public:
  BSTR m_str;
  CComBSTR() : m_str(nullptr) {};
  CComBSTR(int nSize, LPCWSTR sz);
  ~CComBSTR() throw() { SysFreeString(m_str); }
  unsigned int Length() const throw() { return SysStringLen(m_str); }
  operator BSTR() const throw() { return m_str; }

  bool operator==(const CComBSTR &bstrSrc) const throw();

  BSTR *operator&() throw() { return &m_str; }

  BSTR Detach() throw() {
    BSTR s = m_str;
    m_str = NULL;
    return s;
  }

  void Empty() throw() {
    SysFreeString(m_str);
    m_str = NULL;
  }
};

//===--------- Convert argv to wchar ----------------===//
class WArgV {
  std::vector<std::wstring> WStringVector;
  std::vector<const wchar_t *> WCharPtrVector;

public:
  WArgV(int argc, const char **argv);
  const wchar_t **argv() { return WCharPtrVector.data(); }
};
#endif // !defined(_MSC_VER)

#endif // __cplusplus
#endif // LLVM_SUPPORT_WIN_ADAPTER_H
