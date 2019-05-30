/*
 * Copyright (c) 2019 Linaro Limited
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "erpc_rpmsg_openamp_transport.h"
#include "erpc_message_buffer.h"
#include <cstdio>
#include <string>
//#include <termios.h>

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

RpmsgOpenAMPTransport::RpmsgOpenAMPTransport(void)
: ept(0)
{
}

RpmsgOpenAMPTransport::~RpmsgOpenAMPTransport(void)
{
	rpmsg_destroy_ept(ept);
}

erpc_status_t RpmsgOpenAMPTransport::init(rpmsg_endpoint *ep)
{
    ept = ep;
    return kErpcStatus_Success;
}

erpc_status_t RpmsgOpenAMPTransport::underlyingSend(const uint8_t *data, uint32_t size)
{
    uint32_t bytesWritten = rpmsg_openamp_send(ept, (char *)data, size);

//    uint32_t bytesWritten = serial_write(m_serialHandle, (char *)data, size);

    return size != bytesWritten ? kErpcStatus_SendFailed : kErpcStatus_Success;
}
erpc_status_t RpmsgOpenAMPTransport::underlyingReceive(uint8_t *data, uint32_t size)
{
    uint32_t bytesRead = rpmsg_openamp_read(ept, (char *)data, size);

    return size != bytesRead ? kErpcStatus_ReceiveFailed : kErpcStatus_Success;
}
