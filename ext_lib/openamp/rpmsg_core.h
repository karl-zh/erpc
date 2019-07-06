/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RPMSG_CORE_H_
#define _RPMSG_CORE_H_

#include <openamp/rpmsg.h>
#include <metal/list.h>

#if defined __cplusplus
extern "C" {
#endif

/* Configurable parameters */
#define RPMSG_BUFFER_SIZE                       512
#define RPMSG_MAX_VQ_PER_RDEV                   2
#define RPMSG_NS_EPT_ADDR                       0x35
#define RPMSG_ADDR_BMP_SIZE                     4

/* Definitions for device types , null pointer, etc.*/
#define RPMSG_SUCCESS                           0
#define RPMSG_NULL                              (void *)0
#define RPMSG_REMOTE                            0
#define RPMSG_MASTER                            1
#define RPMSG_TRUE                              1
#define RPMSG_FALSE                             0

/* RPMSG channel states. */
#define RPMSG_CHNL_STATE_IDLE                   0
#define RPMSG_CHNL_STATE_NS                     1
#define RPMSG_CHNL_STATE_ACTIVE                 2

/* Remote processor/device states. */
#define RPMSG_DEV_STATE_IDLE                    0
#define RPMSG_DEV_STATE_ACTIVE                  1

/* Total tick count for 15secs - 1msec tick. */
#define RPMSG_TICK_COUNT                        15000

/* Time to wait - In multiple of 10 msecs. */
#define RPMSG_TICKS_PER_INTERVAL                10

/* Error macros. */
#define RPMSG_ERROR_BASE                        -2000
#define RPMSG_ERR_NO_MEM                        (RPMSG_ERROR_BASE - 1)
#define RPMSG_ERR_NO_BUFF                       (RPMSG_ERROR_BASE - 2)
#define RPMSG_ERR_MAX_VQ                        (RPMSG_ERROR_BASE - 3)
#define RPMSG_ERR_PARAM                         (RPMSG_ERROR_BASE - 4)
#define RPMSG_ERR_DEV_STATE                     (RPMSG_ERROR_BASE - 5)
#define RPMSG_ERR_BUFF_SIZE                     (RPMSG_ERROR_BASE - 6)
#define RPMSG_ERR_DEV_INIT                      (RPMSG_ERROR_BASE - 7)
#define RPMSG_ERR_DEV_ADDR                      (RPMSG_ERROR_BASE - 8)

/* Zero-Copy extension macros */
#define RPMSG_HDR_FROM_BUF(buf)             (struct rpmsg_hdr *)((char*)buf - \
                                            sizeof(struct rpmsg_hdr))

struct rpmsg_channel;
typedef void (*rpmsg_rx_cb_t) (struct rpmsg_channel *, void *, int, void *,
			       unsigned long);
#if defined __cplusplus
}
#endif

#endif				/* _RPMSG_CORE_H_ */
