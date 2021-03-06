project(Generator
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SCHEME_FILE "${CMAKE_CURRENT_SOURCE_DIR}/scheme-72.tl" CACHE STRING "Input Telegram scheme file")

if(TELEGRAMQT_BUILD_TESTS)
    enable_testing()

    add_subdirectory(tests)
endif()

set(generator_SOURCES
    main.cpp
    Generator.cpp
    Generator.hpp
)

add_executable(generator ${generator_SOURCES})

set(generator_TEMPLATES
    templates/ClientRpcLayerTemplate.cpp
    templates/ClientRpcLayerTemplate.hpp
    templates/LICENSE.template
    templates/ServerOperationFactory.cpp
    templates/ServerOperationFactory.hpp
)

target_compile_definitions(generator PRIVATE
    QT_RESTRICTED_CAST_FROM_ASCII
)

target_link_libraries(generator
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    ZLIB::ZLIB
)

add_custom_target(run_codegen
    COMMAND generator --generate-from-text ${SCHEME_FILE} -I ${CMAKE_SOURCE_DIR}/TelegramQt
    DEPENDS generator
    SOURCES ${SCHEME_FILE} ${generator_TEMPLATES}
    VERBATIM
)
