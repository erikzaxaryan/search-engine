project(DBConnector)

add_library(
        DBConnector SHARED

        DBConnector.hpp
        DBConnector.cpp
)

target_link_libraries(DBConnector -lmysqlcppconn)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")