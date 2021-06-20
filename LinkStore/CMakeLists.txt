project(LinkStore)

add_library(
        LinkStore SHARED

        Link.hpp
        Link.cpp

        LinkStatus.hpp

        LinkStore.hpp
        LinkStore.cpp
)

target_link_libraries(LinkStore)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")