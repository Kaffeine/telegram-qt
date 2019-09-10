find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(ZLIB REQUIRED)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(test_keys_data STATIC
    keys_data.cpp
    keys_data.qrc
)

target_include_directories(test_keys_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_keys_data LINK_PUBLIC
    Qt5::Core
    ZLIB::ZLIB
)
