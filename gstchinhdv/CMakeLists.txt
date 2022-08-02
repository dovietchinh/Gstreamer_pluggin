cmake_minimum_required(VERSION 3.16)
project(gstchinhdv)

find_package(PkgConfig)
pkg_check_modules(GST gstreamer-1.0)
find_package(OpenCV)
add_library(gstchinhdv SHARED gstchinhdv.cpp )
target_include_directories(gstchinhdv PRIVATE ${GST_INCLUDE_DIRS} ./ ${OpenCV_INCLUDE_DIRS})
target_link_libraries(gstchinhdv ${OpenCV_LIBS} ${GST_LIBRARIES})

add_executable(test_plugin gstchinhdv_test.cpp)
target_include_directories(test_plugin PRIVATE ${GST_INCLUDE_DIRS})
target_link_libraries(test_plugin ${GST_LIBRARIES})

