project(DataStore)

add_library(
        DataStore SHARED

        Data.hpp
        Data.cpp

        DataStore.hpp
        DataStore.cpp
)

target_link_libraries(DataStore)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")