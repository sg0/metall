// Copyright 2019 Lawrence Livermore National Security, LLC and other Metall Project Developers.
// See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: (Apache-2.0 OR MIT)

#ifndef METALL_KERNEL_MANAGER_KERNEL_DEFS_HPP
#define METALL_KERNEL_MANAGER_KERNEL_DEFS_HPP

#ifndef METALL_DEFAULT_VM_RESERVE_SIZE
#if defined(__linux__)
#define METALL_DEFAULT_VM_RESERVE_SIZE (1ULL << 43ULL)
#elif defined(__APPLE__)
#define METALL_DEFAULT_VM_RESERVE_SIZE (1ULL << 42ULL)
#endif
#endif

#ifndef METALL_MAX_SEGMENT_SIZE
#define METALL_MAX_SEGMENT_SIZE (1ULL << 48ULL)
#endif

#ifndef METALL_INITIAL_SEGMENT_SIZE
#define METALL_INITIAL_SEGMENT_SIZE (1ULL << 28ULL)
#endif

#endif //METALL_KERNEL_MANAGER_KERNEL_DEFS_HPP
