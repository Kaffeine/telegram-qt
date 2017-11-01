project(GeneratorNG)

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

set(generator_SOURCES
    main.cpp
    GeneratorNG.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(generator-ng ${generator_SOURCES})

set_target_properties(generator-ng PROPERTIES AUTOMOC TRUE)

target_include_directories(generator-ng PRIVATE
    ${QT5_INCLUDES}
)

target_link_libraries(generator-ng LINK_PUBLIC
    Qt5::Core
    Qt5::Network
)
