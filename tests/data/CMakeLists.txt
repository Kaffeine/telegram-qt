
add_library(test_keys_data STATIC
    keys_data.cpp
    keys_data.qrc
)

target_include_directories(test_keys_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_keys_data LINK_PUBLIC
    Qt5::Core
    ZLIB::ZLIB
)
