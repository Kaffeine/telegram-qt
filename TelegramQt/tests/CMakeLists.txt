
find_package(Qt5 REQUIRED COMPONENTS Core Test)

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

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

foreach(test_name
    tst_CTelegramTransport
    tst_CTelegramConnection
    tst_CTelegramDispatcher
    tst_CTelegramStream
    tst_TelegramRemoteFile
    tst_utils
)
    FILE(GLOB TEST_SOURCES ${test_name}/*.cpp)
    add_executable(${test_name} ${TEST_SOURCES})
    target_link_libraries(${test_name}
        Qt5::Core
        Qt5::Test
        TelegramQt${QT_VERSION_MAJOR}
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
