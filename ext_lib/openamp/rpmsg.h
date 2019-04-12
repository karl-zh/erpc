/*
 * Remote processor messaging
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 * All rights reserved.
 * Copyright (c) 2016 Freescale Semiconductor, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RPMSG_H_
#define _RPMSG_H_

#include <openamp/rpmsg_core.h>

#if defined __cplusplus
extern "C" {
#endif

/* The feature bitmap for virtio rpmsg */
#define VIRTIO_RPMSG_F_NS	0	/* RP supports name service notifications */
#define RPMSG_NAME_SIZE     32
#define RPMSG_BUF_HELD      (1U << 31) /* Flag to suggest to hold the buffer */

#define RPMSG_LOCATE_DATA(p)  ((unsigned char *) p + sizeof (struct rpmsg_hdr))

/**
 * struct rpmsg_hdr - common header for all rpmsg messages
 * @src: source address
 * @dst: destination address
 * @reserved: reserved for future use
 * @len: length of payload (in bytes)
 * @flags: message flags
 *
 * Every message sent(/received) on the rpmsg bus begins with this header.
 */
OPENAMP_PACKED_BEGIN
struct rpmsg_hdr {
	uint32_t src;
	uint32_t dst;
	uint32_t reserved;
	uint16_t len;
	uint16_t flags;
} OPENAMP_PACKED_END;

/**
 * struct rpmsg_hdr_reserved - this is the "union" of the rpmsg_hdr->reserved
 * @rfu: reserved for future usage
 * @idx: index of a buffer (not to be returned back to the buffer's pool)
 *
 * This structure has been introduced to keep the backward compatibility. 
 * It could be integrated into rpmsg_hdr struct, replacing the reserved field.
 */
struct rpmsg_hdr_reserved
{
	uint16_t rfu; /* reserved for future usage */
	uint16_t idx;
};

/**
 * struct rpmsg_ns_msg - dynamic name service announcement message
 * @name: name of remote service that is published
 * @addr: address of remote service that is published
 * @flags: indicates whether service is created or destroyed
 *
 * This message is sent across to publish a new service, or announce
 * about its removal. When we receive these messages, an appropriate
 * rpmsg channel (i.e device) is created/destroyed. In turn, the ->probe()
 * or ->remove() handler of the appropriate rpmsg driver will be invoked
 * (if/as-soon-as one is registered).
 */
OPENAMP_PACKED_BEGIN
struct rpmsg_ns_msg {
	char name[RPMSG_NAME_SIZE];
	uint32_t addr;
	uint32_t flags;
} OPENAMP_PACKED_END;

/**
 * enum rpmsg_ns_flags - dynamic name service announcement flags
 *
 * @RPMSG_NS_CREATE: a new remote service was just created
 * @RPMSG_NS_DESTROY: a known remote service was just destroyed
 */
enum rpmsg_ns_flags {
	RPMSG_NS_CREATE = 0,
	RPMSG_NS_DESTROY = 1,
};

#define RPMSG_ADDR_ANY		0xFFFFFFFF

/**
 * rpmsg_channel - devices that belong to the rpmsg bus are called channels
 * @name: channel name
 * @src: local address
 * @dst: destination address
 * rdev: rpmsg remote device
 * @ept: the rpmsg endpoint of this channel
 * @state: channel state
 */
struct rpmsg_channel {
	char name[RPMSG_NAME_SIZE];
	uint32_t src;
	uint32_t dst;
	struct remote_device *rdev;
	struct rpmsg_endpoint *rp_ept;
	unsigned int state;
	struct metal_list node;
};

/**
 * channel_info - channel info
 * @name: channel name
 * @src: local address
 * @dst: destination address
 */

struct channel_info {
	char name[RPMSG_NAME_SIZE];
	uint32_t src;
	uint32_t dest;
};

/**
 * struct rpmsg_endpoint - binds a local rpmsg address to its user
 * @rp_chnl: rpmsg channel device
 * @cb: rx callback handler
 * @addr: local rpmsg address
 * @priv: private data for the driver's use
 *
 * In essence, an rpmsg endpoint represents a listener on the rpmsg bus, as
 * it binds an rpmsg address with an rx callback handler.
 *
 * Simple rpmsg drivers shouldn't use this struct directly, because
 * things just work: every rpmsg driver provides an rx callback upon
 * registering to the bus, and that callback is then bound to its rpmsg
 * address when the driver is probed. When relevant inbound messages arrive
 * (i.e. messages which their dst address equals to the src address of
 * the rpmsg channel), the driver's handler is invoked to process it.
 *
 * More complicated drivers though, that do need to allocate additional rpmsg
 * addresses, and bind them to different rx callbacks, must explicitly
 * create additional endpoints by themselves (see rpmsg_create_ept()).
 */
struct rpmsg_endpoint {
	struct rpmsg_channel *rp_chnl;
	rpmsg_rx_cb_t cb;
	uint32_t addr;
	void *priv;
	struct metal_list node;
};

int
rpmsg_send_offchannel_raw(struct rpmsg_channel *, uint32_t, uint32_t,
			  const void *, int, int);
/**
 * rpmsg_send() - send a message across to the remote processor
 * @rpdev: the rpmsg channel
 * @data: payload of message
 * @len: length of payload
 *
 * This function sends @data of length @len on the @rpdev channel.
 * The message will be sent to the remote processor which the @rpdev
 * channel belongs to, using @rpdev's source and destination addresses.
 * In case there are no TX buffers available, the function will block until
 * one becomes available, or a timeout of 15 seconds elapses. When the latter
 * happens, -ERESTARTSYS is returned.
 *
 * Can only be called from process context (for now).
 *
 * Returns number of bytes it has sent or negative error value on failure.
 */
static inline int rpmsg_sendto(struct rpmsg_channel *rpdev, const void *data,
			       int len, uint32_t dst)
{
	return rpmsg_send_offchannel_raw(rpdev, rpdev->src, dst, data,
					 len, RPMSG_TRUE);
}

#if defined __cplusplus
}
#endif

#endif				/* _RPMSG_H_ */
