project(Generator
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(ENABLE_TESTS "Enable compilation of automated tests" FALSE)
set(SCHEME_FILE "${CMAKE_CURRENT_SOURCE_DIR}/scheme-72.tl" CACHE STRING "Input Telegram scheme file")

if (ENABLE_TESTS)
    add_subdirectory(tests)
endif()

set(generator_SOURCES
    main.cpp
    Generator.cpp
    Generator.hpp
)

add_executable(generator ${generator_SOURCES})

target_link_libraries(generator
    Qt5::Core
    Qt5::Network
    ZLIB::ZLIB
)

add_custom_target(run_codegen
    COMMAND generator --generate-from-text ${SCHEME_FILE} -I ${CMAKE_SOURCE_DIR}/TelegramQt
    DEPENDS generator
    SOURCES ${SCHEME_FILE}
    VERBATIM
)
