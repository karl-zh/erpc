INCLUDE(CMakeForceCompiler)

# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

#SET(ARMGCC_DIR "/usr/local/gcc-arm-none-eabi-7-2018-q2-update")

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)
#SET(ARMGCC_DIR "/usr/local/gcc-arm-none-eabi-7-2018-q2-update")
 
# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

# DEBUG LINK FILE
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/MCIMX6X_M4_ocram.ld  -static")

# RELEASE LINK FILE
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/MCIMX6X_M4_ocram.ld  -static")

# DEBUG ASM FLAGS
SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -g  -mcpu=cortex-m4  -mfloat-abi=softfp  -mfpu=fpv4-sp-d16  -mthumb  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# DEBUG C FLAGS
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g  -O0  -fno-strict-aliasing  -mcpu=cortex-m4  -mfloat-abi=softfp  -mfpu=fpv4-sp-d16  -mthumb  -MMD  -MP  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# DEBUG CXX FLAGS
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g  -O0  -fno-strict-aliasing  -mcpu=cortex-m4  -mfloat-abi=softfp  -mfpu=fpv4-sp-d16  -mthumb  -MMD  -MP  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu++11 -fno-exceptions -fno-rtti")

# DEBUG LD FLAGS
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g  -mcpu=cortex-m4  -mfloat-abi=softfp  -mfpu=fpv4-sp-d16  --specs=nano.specs  -lm  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -Os  -mthumb  -mapcs  -Xlinker --gc-sections  -Xlinker -static  -Xlinker -z  -Xlinker muldefs")

# RELEASE ASM FLAGS
SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mcpu=cortex-m4  -mfloat-abi=softfp  -mfpu=fpv4-sp-d16  -mthumb  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# RELEASE C FLAGS
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os  -fno-strict-aliasing  -mcpu=cortex-m4  -mfloat-abi=softfp  -mfpu=fpv4-sp-d16  -mthumb  -MMD  -MP  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# RELEASE CXX FLAGS
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os  -fno-strict-aliasing  -mcpu=cortex-m4  -mfloat-abi=softfp  -mfpu=fpv4-sp-d16  -mthumb  -MMD  -MP  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu++11  -fno-exceptions -fno-rtti")

# RELEASE LD FLAGS
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mcpu=cortex-m4  -mfloat-abi=softfp  -mfpu=fpv4-sp-d16  --specs=nano.specs  -lm  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -Os  -mthumb  -mapcs  -Xlinker --gc-sections  -Xlinker -static  -Xlinker -z  -Xlinker muldefs")

# ASM MACRO
SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG}  -D__DEBUG")

# C MACRO
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}  -D__DEBUG")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}  -DCPU_MCIMX6X_M4")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}  -DERPC_THREADS_ZEPHYR")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -D__NDEBUG")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -DCPU_MCIMX6X_M4")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -DERPC_THREADS_ZEPHYR")

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

INCLUDE_DIRECTORIES(${ProjDirPath}/../erpc_c/config)
INCLUDE_DIRECTORIES(${ProjDirPath}/../erpc_c/infra)
INCLUDE_DIRECTORIES(${ProjDirPath}/../erpc_c/port)
INCLUDE_DIRECTORIES(${ProjDirPath}/../erpc_c/setup)
INCLUDE_DIRECTORIES(${ProjDirPath}/../erpc_c/transports)
INCLUDE_DIRECTORIES(${ProjDirPath}/../erpc_c/include_arch_arm)
INCLUDE_DIRECTORIES(${ProjDirPath}/../erpc_c/include_ztest)
INCLUDE_DIRECTORIES(${ProjDirPath}/../service)
INCLUDE_DIRECTORIES(${ProjDirPath}/../ext_lib)

add_library(liberpc_server.a STATIC
    "${ProjDirPath}/../erpc_c/infra/erpc_server.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_server.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_simple_server.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_simple_server.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_client_manager.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_common.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_basic_codec.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_basic_codec.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_codec.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_version.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_message_buffer.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_message_buffer.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_crc16.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_framed_transport.cpp"
    "${ProjDirPath}/../erpc_c/port/erpc_config_internal.h"
    "${ProjDirPath}/../erpc_c/port/erpc_port.h"
    "${ProjDirPath}/../erpc_c/port/erpc_port_stdlib.cpp"
#    "${ProjDirPath}/../erpc_c/port/erpc_port_zephyr.cpp"
#    "${ProjDirPath}/../erpc_c/port/erpc_threading_zephyr.cpp"
    "${ProjDirPath}/../erpc_c/setup/erpc_server_setup.cpp"
    "${ProjDirPath}/../erpc_c/setup/erpc_server_setup.h"
    "${ProjDirPath}/../erpc_c/setup/erpc_client_setup.cpp"
    "${ProjDirPath}/../erpc_c/setup/erpc_setup_rpmsg_openamp.cpp"
    "${ProjDirPath}/../erpc_c/setup/erpc_setup_mbf_static.cpp"
    "${ProjDirPath}/../erpc_c/setup/erpc_mbf_setup.h"
    "${ProjDirPath}/../erpc_c/setup/erpc_transport_setup.h"
    "${ProjDirPath}/../erpc_c/transports/erpc_rpmsg_openamp_transport.cpp"
    "${ProjDirPath}/../erpc_c/config/erpc_config.h"

#    "${ProjDirPath}/../service/erpc_matrix_multiply.h"
#    "${ProjDirPath}/../service/erpc_matrix_multiply_server.h"
#    "${ProjDirPath}/../service/erpc_matrix_multiply_server.cpp"
#    "${ProjDirPath}/../service/erpc_matrix_multiply_client.cpp"

#    "${ProjDirPath}/../service/erpc_psa_client_api.h"
#    "${ProjDirPath}/../service/erpc_psa_client_api_server.h"
#    "${ProjDirPath}/../service/erpc_psa_client_api_server.cpp"
#    "${ProjDirPath}/../service/erpc_psa_client_api_client.cpp"

    "${ProjDirPath}/../service/erpc_psa_api.h"
    "${ProjDirPath}/../service/erpc_psa_api_server.h"
    "${ProjDirPath}/../service/erpc_psa_api_server.cpp"
#    "${ProjDirPath}/../service/erpc_psa_api_client.cpp"
)

#install (TARGETS liberpc_server.a ARCHIVE DESTINATION ${MAKE_INSTALL_PREFIX} )
install (TARGETS liberpc_server.a ARCHIVE DESTINATION lib LIBRARY DESTINATION lib COMPONENT library )

add_library(liberpc_client.a STATIC
    "${ProjDirPath}/../erpc_c/infra/erpc_server.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_server.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_simple_server.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_simple_server.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_client_manager.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_common.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_basic_codec.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_basic_codec.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_codec.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_version.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_message_buffer.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_message_buffer.h"
    "${ProjDirPath}/../erpc_c/infra/erpc_crc16.cpp"
    "${ProjDirPath}/../erpc_c/infra/erpc_framed_transport.cpp"
    "${ProjDirPath}/../erpc_c/port/erpc_config_internal.h"
    "${ProjDirPath}/../erpc_c/port/erpc_port.h"
#    "${ProjDirPath}/../erpc_c/port/erpc_port_stdlib.cpp"
    "${ProjDirPath}/../erpc_c/port/erpc_port_zephyr.cpp"
#    "${ProjDirPath}/../erpc_c/port/erpc_threading_zephyr.cpp"
    "${ProjDirPath}/../erpc_c/setup/erpc_server_setup.cpp"
    "${ProjDirPath}/../erpc_c/setup/erpc_server_setup.h"
    "${ProjDirPath}/../erpc_c/setup/erpc_client_setup.cpp"
    "${ProjDirPath}/../erpc_c/setup/erpc_setup_rpmsg_openamp.cpp"
    "${ProjDirPath}/../erpc_c/setup/erpc_setup_mbf_static.cpp"
    "${ProjDirPath}/../erpc_c/setup/erpc_mbf_setup.h"
    "${ProjDirPath}/../erpc_c/setup/erpc_transport_setup.h"
    "${ProjDirPath}/../erpc_c/transports/erpc_rpmsg_openamp_transport.cpp"
    "${ProjDirPath}/../erpc_c/config/erpc_config.h"

#    "${ProjDirPath}/../service/erpc_matrix_multiply.h"
#    "${ProjDirPath}/../service/erpc_matrix_multiply_server.h"
#    "${ProjDirPath}/../service/erpc_matrix_multiply_server.cpp"
#    "${ProjDirPath}/../service/erpc_matrix_multiply_client.cpp"

#    "${ProjDirPath}/../service/erpc_psa_client_api.h"
#    "${ProjDirPath}/../service/erpc_psa_client_api_server.h"
#    "${ProjDirPath}/../service/erpc_psa_client_api_server.cpp"
#    "${ProjDirPath}/../service/erpc_psa_client_api_client.cpp"

    "${ProjDirPath}/../service/erpc_psa_api.h"
    "${ProjDirPath}/../service/erpc_psa_api_server.h"
#    "${ProjDirPath}/../service/erpc_psa_api_server.cpp"
    "${ProjDirPath}/../service/erpc_psa_api_client.cpp"
)

install (TARGETS liberpc_client.a ARCHIVE DESTINATION lib LIBRARY DESTINATION lib COMPONENT library )
