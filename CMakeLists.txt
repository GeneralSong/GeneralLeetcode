cmake_minimum_required(VERSION 2.6)

project(GeneralLeetcode)
set(TARGET_NAME leetcode)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)  #设置可执行文件的输出目录
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)  #设置库文件的输出目录


# use $<0:.> to make vs not append Debug/Release after the path
set(CMAKE_BUILD_TYPE "Release") # Release Debug
#set(CMAKE_DEBUG_POSTFIX "d")

# you have add link directories before add target
#opencv3.4.6
#include_directories("/usr/local/include")
#include_directories("/usr/local/include/opencv")
#include_directories("/usr/local/include/opencv2")
#link_directories("/usr/local/lib")
#set(OPENCV_LIBS opencv_core opencv_imgcodecs
#                opencv_highgui opencv_imgproc
#                opencv_videoio)
#link_libraries(${OPENCV_LIBS})

#caffe
#include_directories("${PROJECT_SOURCE_DIR}/3rdparty/Caffe-Mobilenet-YOLOV3/include")
#link_directories("${PROJECT_SOURCE_DIR}/3rdparty/Caffe-Mobilenet-YOLOV3/lib")
#set(CAFFE_LIBS caffe)
#link_libraries(${CAFFE_LIBS})

#cuda cudnn
#include_directories("/usr/local/cuda/include")
#link_directories("/usr/local/cuda/lib64")
#set(CUDA_LIBS cudart cublas curand)
#link_libraries(${CUDA_LIBS})

#caffe addition
#set(CAFFE_ADD_LIBS glog gflags protobuf boost_system boost_thread lmdb leveldb stdc++ cblas atlas cudnn)
#link_libraries(${CAFFE_ADD_LIBS})

#include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src")

file(GLOB SOURCE ./src/*.cpp)

add_definitions(-std=c++11)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
#add_executable(${TARGET_NAME} ${SOURCE})
#add_executable(${TARGET_NAME} ${SOURCE}) #编译生成可执行文件
#add_library(${TARGET_NAME} SHARED ${SOURCE} )#生成动态库
add_library(${TARGET_NAME} STATIC ${SOURCE} )#生成静态库







