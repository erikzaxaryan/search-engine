project(Parser)

add_library(
        Parser SHARED

        HTML_Parse.hpp
        HTML_Parse.cpp
)

target_link_libraries(Parser -lgumbo)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")