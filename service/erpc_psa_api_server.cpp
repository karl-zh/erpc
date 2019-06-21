/*
 * Generated by erpcgen 1.7.1 on Fri Jun 21 16:29:45 2019.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#include "erpc_psa_api_server.h"
#include <new>
#include "erpc_port.h"
#include "erpc_manually_constructed.h"

#if 10701 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif

using namespace erpc;
using namespace std;

#if ERPC_NESTED_CALLS_DETECTION
extern bool nestingDetection;
#endif

static ManuallyConstructed<MatrixMultiplyService_service> s_MatrixMultiplyService_service;

static ManuallyConstructed<PsaFrameworkVersionService_service> s_PsaFrameworkVersionService_service;

static ManuallyConstructed<PsaVersionService_service> s_PsaVersionService_service;

static ManuallyConstructed<PsaConnectService_service> s_PsaConnectService_service;

static ManuallyConstructed<PsaCallService_service> s_PsaCallService_service;

static ManuallyConstructed<PsaCloseService_service> s_PsaCloseService_service;



// Constant variable definitions
#pragma weak matrix_size
extern const int32_t matrix_size = 5;


// Call the correct server shim based on method unique ID.
erpc_status_t MatrixMultiplyService_service::handleInvocation(uint32_t methodId, uint32_t sequence, Codec * codec, MessageBufferFactory *messageFactory)
{
    switch (methodId)
    {
        case kMatrixMultiplyService_erpcMatrixMultiply_id:
            return erpcMatrixMultiply_shim(codec, messageFactory, sequence);

        default:
            return kErpcStatus_InvalidArgument;
    }
}

// Server shim for erpcMatrixMultiply of MatrixMultiplyService interface.
erpc_status_t MatrixMultiplyService_service::erpcMatrixMultiply_shim(Codec * codec, MessageBufferFactory *messageFactory, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;

    Matrix matrix1;
    Matrix matrix2;
    Matrix result_matrix;

    // startReadMessage() was already called before this shim was invoked.

    for (uint32_t arrayCount0 = 0; arrayCount0 < 5; ++arrayCount0)
    {
        for (uint32_t arrayCount1 = 0; arrayCount1 < 5; ++arrayCount1)
        {
            codec->read(&matrix1[arrayCount0][arrayCount1]);
        }
    }

    for (uint32_t arrayCount0 = 0; arrayCount0 < 5; ++arrayCount0)
    {
        for (uint32_t arrayCount1 = 0; arrayCount1 < 5; ++arrayCount1)
        {
            codec->read(&matrix2[arrayCount0][arrayCount1]);
        }
    }

    err = codec->getStatus();
    if (!err)
    {
        // Invoke the actual served function.
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = true;
#endif
        erpcMatrixMultiply(matrix1, matrix2, result_matrix);
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = false;
#endif

        // preparing MessageBuffer for serializing data
        err = messageFactory->prepareServerBufferForSend(codec->getBuffer());
    }

    if (!err)
    {
        // preparing codec for serializing data
        codec->reset();

        // Build response message.
        codec->startWriteMessage(kReplyMessage, kMatrixMultiplyService_service_id, kMatrixMultiplyService_erpcMatrixMultiply_id, sequence);

        for (uint32_t arrayCount0 = 0; arrayCount0 < 5; ++arrayCount0)
        {
            for (uint32_t arrayCount1 = 0; arrayCount1 < 5; ++arrayCount1)
            {
                codec->write(result_matrix[arrayCount0][arrayCount1]);
            }
        }

        err = codec->getStatus();
    }

    return err;
}

// Call the correct server shim based on method unique ID.
erpc_status_t PsaFrameworkVersionService_service::handleInvocation(uint32_t methodId, uint32_t sequence, Codec * codec, MessageBufferFactory *messageFactory)
{
    switch (methodId)
    {
        case kPsaFrameworkVersionService_psa_framework_version_id:
            return psa_framework_version_shim(codec, messageFactory, sequence);

        default:
            return kErpcStatus_InvalidArgument;
    }
}

// Server shim for psa_framework_version of PsaFrameworkVersionService interface.
erpc_status_t PsaFrameworkVersionService_service::psa_framework_version_shim(Codec * codec, MessageBufferFactory *messageFactory, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;

    uint32_t result;

    // startReadMessage() was already called before this shim was invoked.

    err = codec->getStatus();
    if (!err)
    {
        // Invoke the actual served function.
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = true;
#endif
        result = psa_framework_version();
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = false;
#endif

        // preparing MessageBuffer for serializing data
        err = messageFactory->prepareServerBufferForSend(codec->getBuffer());
    }

    if (!err)
    {
        // preparing codec for serializing data
        codec->reset();

        // Build response message.
        codec->startWriteMessage(kReplyMessage, kPsaFrameworkVersionService_service_id, kPsaFrameworkVersionService_psa_framework_version_id, sequence);

        codec->write(result);

        err = codec->getStatus();
    }

    return err;
}

// Call the correct server shim based on method unique ID.
erpc_status_t PsaVersionService_service::handleInvocation(uint32_t methodId, uint32_t sequence, Codec * codec, MessageBufferFactory *messageFactory)
{
    switch (methodId)
    {
        case kPsaVersionService_psa_version_id:
            return psa_version_shim(codec, messageFactory, sequence);

        default:
            return kErpcStatus_InvalidArgument;
    }
}

// Server shim for psa_version of PsaVersionService interface.
erpc_status_t PsaVersionService_service::psa_version_shim(Codec * codec, MessageBufferFactory *messageFactory, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;

    uint32_t sid;
    uint32_t result;

    // startReadMessage() was already called before this shim was invoked.

    codec->read(&sid);

    err = codec->getStatus();
    if (!err)
    {
        // Invoke the actual served function.
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = true;
#endif
        result = psa_version(sid);
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = false;
#endif

        // preparing MessageBuffer for serializing data
        err = messageFactory->prepareServerBufferForSend(codec->getBuffer());
    }

    if (!err)
    {
        // preparing codec for serializing data
        codec->reset();

        // Build response message.
        codec->startWriteMessage(kReplyMessage, kPsaVersionService_service_id, kPsaVersionService_psa_version_id, sequence);

        codec->write(result);

        err = codec->getStatus();
    }

    return err;
}

// Call the correct server shim based on method unique ID.
erpc_status_t PsaConnectService_service::handleInvocation(uint32_t methodId, uint32_t sequence, Codec * codec, MessageBufferFactory *messageFactory)
{
    switch (methodId)
    {
        case kPsaConnectService_psa_connect_id:
            return psa_connect_shim(codec, messageFactory, sequence);

        default:
            return kErpcStatus_InvalidArgument;
    }
}

// Server shim for psa_connect of PsaConnectService interface.
erpc_status_t PsaConnectService_service::psa_connect_shim(Codec * codec, MessageBufferFactory *messageFactory, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;

    uint32_t sid;
    uint32_t minor_version;
    psa_handle_t result;

    // startReadMessage() was already called before this shim was invoked.

    codec->read(&sid);

    codec->read(&minor_version);

    err = codec->getStatus();
    if (!err)
    {
        // Invoke the actual served function.
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = true;
#endif
        result = psa_connect(sid, minor_version);
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = false;
#endif

        // preparing MessageBuffer for serializing data
        err = messageFactory->prepareServerBufferForSend(codec->getBuffer());
    }

    if (!err)
    {
        // preparing codec for serializing data
        codec->reset();

        // Build response message.
        codec->startWriteMessage(kReplyMessage, kPsaConnectService_service_id, kPsaConnectService_psa_connect_id, sequence);

        codec->write(result);

        err = codec->getStatus();
    }

    return err;
}

// Call the correct server shim based on method unique ID.
erpc_status_t PsaCallService_service::handleInvocation(uint32_t methodId, uint32_t sequence, Codec * codec, MessageBufferFactory *messageFactory)
{
    switch (methodId)
    {
        case kPsaCallService_psa_call_id:
            return psa_call_shim(codec, messageFactory, sequence);

        default:
            return kErpcStatus_InvalidArgument;
    }
}

// Server shim for psa_call of PsaCallService interface.
erpc_status_t PsaCallService_service::psa_call_shim(Codec * codec, MessageBufferFactory *messageFactory, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;

    psa_handle_t handle;
    uint32_t in_vec;
    uint32_t in_len;
    uint32_t out_vec;
    uint32_t out_len;
    psa_status_t result;

    // startReadMessage() was already called before this shim was invoked.

    codec->read(&handle);

    codec->read(&in_vec);

    codec->read(&in_len);

    codec->read(&out_vec);

    codec->read(&out_len);

    err = codec->getStatus();
    if (!err)
    {
        // Invoke the actual served function.
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = true;
#endif
        result = psa_call(handle, in_vec, in_len, out_vec, out_len);
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = false;
#endif

        // preparing MessageBuffer for serializing data
        err = messageFactory->prepareServerBufferForSend(codec->getBuffer());
    }

    if (!err)
    {
        // preparing codec for serializing data
        codec->reset();

        // Build response message.
        codec->startWriteMessage(kReplyMessage, kPsaCallService_service_id, kPsaCallService_psa_call_id, sequence);

        codec->write(result);

        err = codec->getStatus();
    }

    return err;
}

// Call the correct server shim based on method unique ID.
erpc_status_t PsaCloseService_service::handleInvocation(uint32_t methodId, uint32_t sequence, Codec * codec, MessageBufferFactory *messageFactory)
{
    switch (methodId)
    {
        case kPsaCloseService_psa_close_id:
            return psa_close_shim(codec, messageFactory, sequence);

        default:
            return kErpcStatus_InvalidArgument;
    }
}

// Server shim for psa_close of PsaCloseService interface.
erpc_status_t PsaCloseService_service::psa_close_shim(Codec * codec, MessageBufferFactory *messageFactory, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;

    psa_handle_t handle;

    // startReadMessage() was already called before this shim was invoked.

    codec->read(&handle);

    err = codec->getStatus();
    if (!err)
    {
        // Invoke the actual served function.
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = true;
#endif
        psa_close(handle);
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = false;
#endif

        // preparing MessageBuffer for serializing data
        err = messageFactory->prepareServerBufferForSend(codec->getBuffer());
    }

    if (!err)
    {
        // preparing codec for serializing data
        codec->reset();

        // Build response message.
        codec->startWriteMessage(kReplyMessage, kPsaCloseService_service_id, kPsaCloseService_psa_close_id, sequence);

        err = codec->getStatus();
    }

    return err;
}

erpc_service_t create_MatrixMultiplyService_service()
{
    s_MatrixMultiplyService_service.construct();
    return s_MatrixMultiplyService_service.get();
}

erpc_service_t create_PsaFrameworkVersionService_service()
{
    s_PsaFrameworkVersionService_service.construct();
    return s_PsaFrameworkVersionService_service.get();
}

erpc_service_t create_PsaVersionService_service()
{
    s_PsaVersionService_service.construct();
    return s_PsaVersionService_service.get();
}

erpc_service_t create_PsaConnectService_service()
{
    s_PsaConnectService_service.construct();
    return s_PsaConnectService_service.get();
}

erpc_service_t create_PsaCallService_service()
{
    s_PsaCallService_service.construct();
    return s_PsaCallService_service.get();
}

erpc_service_t create_PsaCloseService_service()
{
    s_PsaCloseService_service.construct();
    return s_PsaCloseService_service.get();
}
