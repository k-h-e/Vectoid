set(CMAKE_C_COMPILER /Volumes/xtools/arm-none-linux-gnueabi/bin/arm-none-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER /Volumes/xtools/arm-none-linux-gnueabi/bin/arm-none-linux-gnueabi-g++)


project(Raspiator)
cmake_minimum_required(VERSION 3.0)


add_executable(raspiator

               src/triangle.c )


target_include_directories(raspiator PUBLIC

                           src )

target_link_libraries(raspiator PUBLIC
                      -L/Volumes/xtools/vc/lib -lGLESv2 -lEGL -lbcm_host -lvcos -lvchiq_arm )


set(CMAKE_C_FLAGS "-I/Volumes/xtools/vc/include -I/Volumes/xtools/vc/include/interface/vcos/pthreads -I/Volumes/xtools/vc/include/interface/vmcs_host/linux")
set(CMAKE_CXX_FLAGS "-std=c++11 -Ivc/include")

