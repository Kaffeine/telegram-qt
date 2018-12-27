project(Generator
    LANGUAGES CXX
)

find_package(ZLIB REQUIRED)

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

set(generator_SOURCES
    main.cpp
    Generator.cpp
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${ZLIB_INCLUDE_DIR}
)

add_executable(generator ${generator_SOURCES})

set_target_properties(generator PROPERTIES AUTOMOC TRUE)

target_include_directories(generator PRIVATE
    ${QT5_INCLUDES}
)

target_link_libraries(generator LINK_PUBLIC
    Qt5::Core
    Qt5::Network
    ${ZLIB_LIBRARIES}
)
