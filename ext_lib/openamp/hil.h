#ifndef _HIL_H_
#define _HIL_H_

/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**************************************************************************
 * FILE NAME
 *
 *       hil.h
 *
 * DESCRIPTION
 *
 *       This file defines interface layer to access hardware features. This
 *       interface is used by both RPMSG and remoteproc components.
 *
 ***************************************************************************/


#if defined __cplusplus
extern "C" {
#endif

/* Configurable parameters */
#define HIL_MAX_CORES                   2
#define HIL_MAX_NUM_VRINGS              2
#define HIL_MAX_NUM_CHANNELS            1
/* Reserved CPU id */
#define HIL_RSVD_CPU_ID                 0xffffffff

struct hil_proc;

typedef void (*hil_proc_vdev_rst_cb_t)(struct hil_proc *proc, int id);

/**
 * struct proc_shm
 *
 * This structure is maintained by hardware interface layer for
 * shared memory information. The shared memory provides buffers
 * for use by the vring to exchange messages between the cores.
 *
 */
struct proc_shm {
	/* Start address of shared memory used for buffers. */
	void *start_addr;
	/* Start physical address of shared memory used for buffers. */
	metal_phys_addr_t start_paddr;
	/* sharmed memory I/O region */
	struct metal_io_region *io;
	/* sharmed memory metal device */
	struct metal_device *dev;
	/* Size of shared memory. */
	unsigned long size;
};

/**
* struct proc_intr
*
* This structure is maintained by hardware interface layer for
* notification(interrupts) mechanism. The most common notification mechanism
* is Inter-Processor Interrupt(IPI). There can be other mechanism depending
* on SoC architecture.
*
*/
struct proc_intr {
	/* Interrupt number for vring - use for IPI */
	unsigned int vect_id;
	/* Interrupt priority */
	unsigned int priority;
	/* Interrupt trigger type */
	unsigned int trigger_type;
	/* IPI metal device */
	struct metal_device *dev;
	/* IPI device I/O */
	struct metal_io_region *io;
	/* Private data */
	void *data;
};

/**
* struct proc_vring
*
* This structure is maintained by hardware interface layer to keep
* vring physical memory and notification info.
*
*/
struct proc_vring {
	/* Pointer to virtqueue encapsulating the vring */
	struct virtqueue *vq;
	/* Vring logical address */
	void *vaddr;
	/* Vring metal device */
	struct metal_device *dev;
	/* Vring I/O region */
	struct metal_io_region *io;
	/* Number of vring descriptors */
	unsigned short num_descs;
	/* Vring alignment */
	unsigned long align;
	/* Vring interrupt control block */
	struct proc_intr intr_info;
};

/**
 * struct proc_vdev
 *
 * This structure represents a virtio HW device for remote processor.
 * Currently only one virtio device per processor is supported.
 *
 */
struct proc_vdev {
	/* Address for the vdev info */
	void *vdev_info;
	/* Vdev interrupt control block */
	struct proc_intr intr_info;
	/* Vdev reset callback */
	hil_proc_vdev_rst_cb_t rst_cb;
	/* Number of vrings */
	unsigned int num_vrings;
	/* Virtio device features */
	unsigned int dfeatures;
	/* Virtio gen features */
	unsigned int gfeatures;
	/* Vring info control blocks */
	struct proc_vring vring_info[HIL_MAX_NUM_VRINGS];
};

/**
 * struct proc_chnl
 *
 * This structure represents channel IDs that would be used by
 * the remote in the name service message. This will be extended
 * further to support static channel creation.
 *
 */
struct proc_chnl {
	/* Channel ID */
	char name[32];
};

/**
* struct hil_proc
*
* This structure represents a remote processor and encapsulates shared
* memory and notification info required for IPC.
*
*/
struct hil_proc {
	/* HIL CPU ID */
	unsigned long cpu_id;
	/* HIL platform ops table */
	struct hil_platform_ops *ops;
	/* Resource table metal device */
	struct metal_device *rsc_dev;
	/* Resource table I/O region */
	struct metal_io_region *rsc_io;
	/* Shared memory info */
	struct proc_shm sh_buff;
	/* Virtio device hardware info */
	struct proc_vdev vdev;
	/* Number of RPMSG channels */
	unsigned long num_chnls;
	/* RPMsg channels array */
	struct proc_chnl chnls[HIL_MAX_NUM_CHANNELS];
	/* Initialized status */
	int is_initialized;
	/* hil_proc lock */
	metal_mutex_t lock;
	/* private data */
	void *pdata;
	/* List node */
	struct metal_list node;
};


/**
 *
 * This structure is an interface between HIL and platform porting
 * component. It is required for the user to provide definitions of
 * these functions when framework is ported to new hardware platform.
 *
 */
struct hil_platform_ops {
	/**
	 * enable_interrupt()
	 *
	 * This function enables interrupt(IPI)
	 *
	 * @param intr - pointer to intr information
	 *
	 * @return  - execution status
	 */
	int (*enable_interrupt) (struct proc_intr *intr);

	/**
	 * notify()
	 *
	 * This function generates IPI to let the other side know that there is
	 * job available for it.
	 *
	 * @param proc - pointer to the hil_proc
	 * @param intr_info - pointer to interrupt info control block
	 */
	void (*notify) (struct hil_proc *proc, struct proc_intr * intr_info);

	/**
	 * boot_cpu
	 *
	 * This unction boots the remote processor.
	 *
	 * @param proc - pointer to the hil_proc
	 * @param start_addr - start address of remote cpu
	 *
	 * @return - execution status
	 */
	int (*boot_cpu) (struct hil_proc *proc, unsigned int start_addr);

	/**
	 * shutdown_cpu
	 *
	 *  This function shutdowns the remote processor.
	 *
	 * @param proc - pointer to the hil_proc
	 *
	 */
	void (*shutdown_cpu) (struct hil_proc *proc);

	/**
	 * poll
	 *
	 * This function polls the remote processor.
	 *
	 * @param proc	 - hil_proc to poll
	 * @param nonblock - 0 for blocking, non-0 for non-blocking.
	 *
	 * @return - 0 for no errors, non-0 for errors.
	 */
	int (*poll) (struct hil_proc *proc, int nonblock);

	/**
	 * alloc_shm
	 *
	 *  This function is to allocate shared memory
	 *
	 * @param[in] proc - pointer to the remote processor
	 * @param[in] pa - physical address
	 * @param[in] size - size of the shared memory
	 * @param[out] dev - pointer to the mem dev pointer
	 *
	 * @return - NULL, pointer to the I/O region
	 *
	 */
	struct metal_io_region *(*alloc_shm) (struct hil_proc *proc,
				metal_phys_addr_t pa,
				size_t size,
				struct metal_device **dev);

	/**
	 * release_shm
	 *
	 *  This function is to release shared memory
	 *
	 * @param[in] proc - pointer to the remote processor
	 * @param[in] dev - pointer to the mem dev
	 * @param[in] io - pointer to the I/O region
	 *
	 */
	void (*release_shm) (struct hil_proc *proc,
				struct metal_device *dev,
				struct metal_io_region *io);

	/**
	 * initialize
	 *
	 *  This function initialize remote processor with platform data.
	 *
	 * @param proc	 - hil_proc to poll
	 *
	 * @return NULL on failure, hil_proc pointer otherwise
	 *
	 */
	int (*initialize) (struct hil_proc *proc);

	/**
	 * release
	 *
	 *  This function is to release remote processor resource
	 *
	 * @param[in] proc - pointer to the remote processor
	 *
	 */
	void (*release) (struct hil_proc *proc);
};

/* Utility macros for register read/write */
#define         HIL_MEM_READ8(addr)         *(volatile unsigned char *)(addr)
#define         HIL_MEM_READ16(addr)        *(volatile unsigned short *)(addr)
#define         HIL_MEM_READ32(addr)        *(volatile unsigned long *)(addr)
#define         HIL_MEM_WRITE8(addr,data)   *(volatile unsigned char *)(addr) = (unsigned char)(data)
#define         HIL_MEM_WRITE16(addr,data)  *(volatile unsigned short *)(addr) = (unsigned short)(data)
#define         HIL_MEM_WRITE32(addr,data)  *(volatile unsigned long *)(addr) = (unsigned long)(data)

#if defined __cplusplus
}
#endif

#endif				/* _HIL_H_ */
