cmake_minimum_required(VERSION 3.16)
project(gst_test)
set (CMAKE_CXX_STANDARD 17)

find_package(PkgConfig)
pkg_check_modules(GST gstreamer-1.0)
find_package(OpenCV)

add_subdirectory(gstchinhdv)


add_executable(app source/main.cpp)
target_include_directories(app PUBLIC ${GST_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} /usr/include)
target_link_libraries(app ${GST_LIBRARIES} ${OpenCV_LIBS} gflags)

