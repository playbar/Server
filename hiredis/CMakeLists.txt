cmake_minimum_required(VERSION 3.1)
PROJECT(hiredis)

AUX_SOURCE_DIRECTORY(./ HIRREDIS_SRC)



SET(LIBRARY_OUTPUT_PATH ./)
#SET(EXECUTABLE_OUTPUT_PATH  ./bin)

ADD_DEFINITIONS( -g -W -Wall -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DAC_HAS_INFO
-DAC_HAS_WARNING -DAC_HAS_ERROR -DAC_HAS_CRITICAL -DTIXML_USE_STL
-DAC_HAS_DEBUG -DLINUX_DAEMON)

INCLUDE_DIRECTORIES(./
        /usr/local/include/apr-1
        /usr/local/include
        ../
        ./jsoncpp
        ./pb
        ./pb/protocol
        ../log4cxx/include
        )

LINK_DIRECTORIES(./ ${PB_LIB_DIR} ./slog/lib)

ADD_LIBRARY(hiredis STATIC
        ${HIRREDIS_SRC}
        )

#ADD_XXXX必须在TARGET_LINK_LIBRARIES前面，否则会报错
#ADD_LIBRARY(${PROJECTNAME} SHARED ${SRC_LIST})
#ADD_EXECUTABLE(${PROJECTNAME} ${SRC_LIST})

#TARGET_LINK_LIBRARIES(base pthread crypto)
