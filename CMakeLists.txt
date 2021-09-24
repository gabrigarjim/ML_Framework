
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(dummy)
set (CMAKE_CXX_STANDARD 11)


link_directories("/usr/local/lib" "/home/gabri/Analysis/AI_ML/headers" "/home/gabri/Analysis/AI_ML/models")

add_executable(pca models/pca.cc)
