cmake_minimum_required(VERSION 3.1)
PROJECT(pushserver)

AUX_SOURCE_DIRECTORY(./ SRC_LIST1)
AUX_SOURCE_DIRECTORY(./socket SRC_LIST2)
AUX_SOURCE_DIRECTORY(../base/pb/protocol SRC_LIST3)


#SET(LIBRARY_OUTPUT_PATH ./)
SET(EXECUTABLE_OUTPUT_PATH  ./)
if(APPLE)
    SET(PB_LIB_DIR ../base/pb/lib/mac)
elseif(UNIX)
    SET(PB_LIB_DIR ../base/pb/lib/linux)
endif()

#ADD_DEFINITIONS( -g -W -Wall -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DAC_HAS_INFO
#-DAC_HAS_WARNING -DAC_HAS_ERROR -DAC_HAS_CRITICAL -DTIXML_USE_STL
#-DAC_HAS_DEBUG -DLINUX_DAEMON -std=c++11)

INCLUDE_DIRECTORIES(./
        /usr/local/openssl/include
        ../base/pb/protocol
        ../base/pb
        ../base/slog
        ../base
        )
#LINK_DIRECTORIES( ../lib)

add_library(ssl_lib STATIC IMPORTED)
set_target_properties(ssl_lib PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libssl.a)

add_library(crypto_lib STATIC IMPORTED)
set_target_properties(crypto_lib PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libcrypto.a)

add_library(protobuf_lib STATIC IMPORTED)
set_target_properties(protobuf_lib PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libprotobuf.a)

#ADD_XXXX必须在TARGET_LINK_LIBRARIES前面，否则会报错
#ADD_LIBRARY(${PROJECTNAME} SHARED/STATIC ${SRC_LIST})
ADD_EXECUTABLE(push_server ${SRC_LIST1} ${SRC_LIST2} ${SRC_LIST3})

TARGET_LINK_LIBRARIES(push_server
        pthread
        protobuf_lib
        base
        aprutil-1
        apr-1
        ssl_lib
        crypto_lib

        )
