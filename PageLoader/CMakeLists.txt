project(PageLoader)

add_library(
        PageLoader SHARED

        Page.hpp
        Page.cpp

        PageLoader.hpp
        PageLoader.cpp
)

target_link_libraries(PageLoader -lcurl)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")