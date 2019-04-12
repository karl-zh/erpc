/*
 * Copyright (c) 2015, Xilinx Inc. and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file	list.h
 * @brief	List primitives for libmetal.
 */

#ifndef __METAL_LIST__H__
#define __METAL_LIST__H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup list List Primitives
 *  @{ */

struct metal_list {
	struct metal_list *next, *prev;
};


#ifdef __cplusplus
}
#endif

#endif /* __METAL_LIST__H__ */
