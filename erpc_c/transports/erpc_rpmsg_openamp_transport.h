/*
 * Copyright (c) 2019 Linaro Limited
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _EMBEDDED_RPC__RPMSG_OPENAMP_TRANSPORT_H_
#define _EMBEDDED_RPC__RPMSG_OPENAMP_TRANSPORT_H_

#include "erpc_framed_transport.h"
#include "openamp/remoteproc.h"
#include "openamp/rpmsg.h"
//#include "openamp/hil.h"
#include <string>

/*!
 * @addtogroup rpmsg_openAMP_transport
 * @{
 * @file
 */

////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////

namespace erpc {
/*!
 * @brief RPMSG openAMP transport layer for host PC
 *
 * @ingroup rpmsg_openAMP_transport
 */
class RpmsgOpenAMPTransport : public FramedTransport
{
public:
    /*!
     * @brief Constructor.
     *
     * @param[in] portName Port name.
     * @param[in] baudRate Baudrate.
     */
    RpmsgOpenAMPTransport(void);

    /*!
     * @brief Destructor.
     */
    virtual ~RpmsgOpenAMPTransport(void);

    /*!
     * @brief Initialize Serial peripheral.
     *
     * @param[in] vtime Read timeout.
     * @param[in] vmin Read timeout min.
     *
     * @return Status of init function.
     */
    erpc_status_t init(rpmsg_endpoint *ep);

private:
    /*!
     * @brief Write data to rpmsg end point.
     *
     * @param[in] data Buffer to send.
     * @param[in] size Size of data to send.
     *
     * @retval kErpcStatus_ReceiveFailed rpmsg failed to receive data.
     * @retval kErpcStatus_Success Successfully received all data.
     */
    virtual erpc_status_t underlyingSend(const uint8_t *data, uint32_t size);

    /*!
     * @brief Receive data from rpmsg end point.
     *
     * @param[inout] data Preallocated buffer for receiving data.
     * @param[in] size Size of data to read.
     *
     * @retval kErpcStatus_ReceiveFailed rpmsg failed to receive data.
     * @retval kErpcStatus_Success Successfully received all data.
     */
    virtual erpc_status_t underlyingReceive(uint8_t *data, uint32_t size);

private:
	struct rpmsg_endpoint *ept;
};

} // namespace erpc

/*! @} */

/*!
 * @addtogroup port_rpmsg_openamp
 * @{
 * @file
 */

#if __cplusplus
extern "C" {
#endif

extern int rpmsg_openamp_send(struct rpmsg_endpoint *ept, const void *data,
			     int len);
extern int rpmsg_openamp_read(struct rpmsg_endpoint *ept, char *data,
			     int len);
extern void rpmsg_destroy_ept(struct rpmsg_endpoint *ept);

#if __cplusplus
}
#endif

/*! @} */

#endif // _EMBEDDED_RPC__RPMSG_OPENAMP_TRANSPORT_H_
