/*
 * Remote remote_proc Framework
 *
 * Copyright(c) 2011 Texas Instruments, Inc.
 * Copyright(c) 2011 Google, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef REMOTEPROC_H
#define REMOTEPROC_H

//#include <openamp/rpmsg.h>
//#include <openamp/firmware.h>

#if defined __cplusplus
extern "C" {
#endif

/* IAR ARM build tools */

#ifndef OPENAMP_PACKED_BEGIN
#define OPENAMP_PACKED_BEGIN
#endif

#ifndef OPENAMP_PACKED_END
#define OPENAMP_PACKED_END __attribute__((__packed__))
#endif


/**
 * struct resource_table - firmware resource table header
 * @ver: version number
 * @num: number of resource entries
 * @reserved: reserved (must be zero)
 * @offset: array of offsets pointing at the various resource entries
 *
 * A resource table is essentially a list of system resources required
 * by the remote remote_proc. It may also include configuration entries.
 * If needed, the remote remote_proc firmware should contain this table
 * as a dedicated ".resource_table" ELF section.
 *
 * Some resources entries are mere announcements, where the host is informed
 * of specific remoteproc configuration. Other entries require the host to
 * do something (e.g. allocate a system resource). Sometimes a negotiation
 * is expected, where the firmware requests a resource, and once allocated,
 * the host should provide back its details (e.g. address of an allocated
 * memory region).
 *
 * The header of the resource table, as expressed by this structure,
 * contains a version number (should we need to change this format in the
 * future), the number of available resource entries, and their offsets
 * in the table.
 *
 * Immediately following this header are the resource entries themselves,
 * each of which begins with a resource entry header (as described below).
 */
OPENAMP_PACKED_BEGIN
struct resource_table {
	uint32_t ver;
	uint32_t num;
	uint32_t reserved[2];
	uint32_t offset[0];
} OPENAMP_PACKED_END;

/**
 * struct resc_table_info
 *
 * This structure is maintained by the remoteproc to allow applications
 * to pass resource table info during remote initialization.
 *
 * @rsc_tab : pointer to resource table control block
 * @size    : size of resource table.
 *
 */
struct rsc_table_info {
	struct resource_table *rsc_tab;
	int size;
};

#if defined __cplusplus
}
#endif

#endif				/* REMOTEPROC_H_ */
