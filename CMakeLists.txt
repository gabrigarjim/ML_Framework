CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(califaNN)

set (CMAKE_CXX_STANDARD 11)

find_package(ROOT)

EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
EXECUTE_PROCESS(COMMAND root-config --libs  OUTPUT_VARIABLE ROOT_LIBRARIES OUTPUT_STRIP_TRAILING_WHITESPACE)
EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})


 IF(NOT DEFINED ENV{FAIRROOTPATH})
     MESSAGE(FATAL_ERROR "You did not define the environment variable FAIRROOTPATH which is needed to find FairRoot. Please set this variable and execute cmake again.")
  ENDIF(NOT DEFINED ENV{FAIRROOTPATH})
  SET(FAIRROOTPATH $ENV{FAIRROOTPATH})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_MODULE_PATH "${FAIRROOTPATH}/share/fairbase/cmake/modules"  ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${FAIRROOTPATH}/share/fairbase/cmake/modules_old"  ${CMAKE_MODULE_PATH})


IF(FAIRROOTPATH)
  Set(CheckSrcDir "${FAIRROOTPATH}/share/fairbase/cmake/checks")
ELSE(FAIRROOTPATH)
  Set(CheckSrcDir "${CMAKE_SOURCE_DIR}/cmake/checks")
ENDIF(FAIRROOTPATH)

if(FAIRROOTPATH)
  find_package(FairRoot)
endif(FAIRROOTPATH)


find_package(FairLogger 1.1.0 REQUIRED)

SET(R3BROOT_LIBRARIES $ENV{VMCWORKDIR})

message(STATUS "Getting R3BRoot : ${R3BROOT_LIBRARIES}")
message(STATUS "Getting FairRoot : ${FAIRROOTPATH}")


set(INCLUDE_DIRECTORIES
#put here all directories where header files are located

${R3BROOT_LIBRARIES}/r3bbase
${R3BROOT_LIBRARIES}/passive
${R3BROOT_LIBRARIES}/califa
${R3BROOT_LIBRARIES}/tracking
${R3BROOT_LIBRARIES}/califa/online
${R3BROOT_LIBRARIES}/califa/calibration
${R3BROOT_LIBRARIES}/califa/ana
${R3BROOT_LIBRARIES}/califa/pars
${R3BROOT_LIBRARIES}/califa/sim
${R3BROOT_LIBRARIES}/r3bdata/califaData
${R3BROOT_LIBRARIES}/r3bdata/amsData
${R3BROOT_LIBRARIES}/r3bdata
${R3BROOT_LIBRARIES}/r3bdata/wrData
/usr/local/include/google/tensorflow
/usr/local/include
/usr/local/include/google/protobuf
/usr/local/include/eigen3
/usr/local/include/google/tensorflow/tensorflow/contrib/makefile/downloads/absl
/home/gabri/CODE/FAIRSOFT/build_Feb21/include/root6/
/usr/local/include/google/tensorflow/tensorflow/lite/tools/make/downloads/eigen
/usr/local/include/google/tensorflow/tensorflow/lite/tools/make/downloads/absl
/usr/local/lib
/home/gabri/CODE/TensorFlow/tensorflow/bazel-bin
/usr/local/include/google/protobuf
/home/gabri/CODE/FAIRROOT/install_Feb21/include/
${PROJECT_SOURCE_DIR}/headers
${PROJECT_SOURCE_DIR}/sources
${PROJECT_SOURCE_DIR}/macros
)


set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})


add_executable(califaNN macros/convolutions.cc)
target_link_libraries(califaNN ${ROOT_LIBRARIES} tensorflow_cc tensorflow_framework)
