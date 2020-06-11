
find_package(Qt5 REQUIRED COMPONENTS Core Test)
find_package(ZLIB REQUIRED)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# the RPATH to be used when installing
SET(CMAKE_INSTALL_RPATH "")

# don't add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

add_library(TelegramQt${QT_VERSION_MAJOR}Test INTERFACE)
add_library(TelegramQt${QT_VERSION_MAJOR}::Test ALIAS TelegramQt${QT_VERSION_MAJOR}Test)

target_include_directories(TelegramQt${QT_VERSION_MAJOR}Test INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

set(test_extra_META_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/TestAuthProvider.hpp
)

QT5_WRAP_CPP(test_extra_MOC_SOURCES ${test_extra_META_HEADERS})

foreach(test_name
    tst_all
    tst_ConnectionApi
    tst_FilesApi
    tst_MessagesApi
)
    add_executable(${test_name} ${test_name}/${test_name}.cpp ${test_extra_MOC_SOURCES})
    target_link_libraries(${test_name} PRIVATE
        Qt5::Core
        Qt5::Test
        TelegramQt${QT_VERSION_MAJOR}::Core
        TelegramQt${QT_VERSION_MAJOR}::Server
        TelegramQt${QT_VERSION_MAJOR}::Test
        test_keys_data
    )
    if(TELEGRAMQT_EXPORT_INTERNAL_API)
        target_compile_definitions(${test_name} PRIVATE
            TEST_PRIVATE_API
        )
    endif()

    add_test(NAME ${test_name} COMMAND ${test_name} -maxwarnings 0)
endforeach()

add_subdirectory(manual)
