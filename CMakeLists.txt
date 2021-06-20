cmake_minimum_required(VERSION 3.16.3)
project(Crawler)

set(CMAKE_CXX_STANDARD 17)

include_directories("PageLoader")
include_directories("Parser")
include_directories("LinkStore")
include_directories("WebsiteStore")
include_directories("DataStore")
include_directories("DBConnector")

add_executable(${PROJECT_NAME} Crawler.cpp)

add_subdirectory(PageLoader)
add_subdirectory(Parser)
add_subdirectory(LinkStore)
add_subdirectory(WebsiteStore)
add_subdirectory(DataStore)
add_subdirectory(DBConnector)

set_target_properties(PageLoader PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/PageLoader/libPageLoader.so"
        )

set_target_properties(Parser PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Parser/libParser.so"
        )

set_target_properties(LinkStore PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/LinkStore/libLinkStore.so"
        )

set_target_properties(WebsiteStore PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/WebsiteStore/libWebsiteStore.so"
        )

set_target_properties(DataStore PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/DataStore/libDataStore.so"
        )

set_target_properties(DBConnector PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/DBConnector/libDBConnector.so"
    )

target_link_libraries(${PROJECT_NAME} PageLoader Parser LinkStore WebsiteStore DataStore DBConnector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")