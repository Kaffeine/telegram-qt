
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

foreach(test_name
    tst_crypto
    tst_CTelegramTransport
    tst_MTProtoStream
    tst_UniqueLazyPointer
    tst_utils
    tst_RpcError
    tst_RpcLayer
)
    FILE(GLOB TEST_SOURCES ${test_name}/*.cpp)
    add_executable(${test_name} ${TEST_SOURCES})
    target_link_libraries(${test_name}
        Qt5::Core
        Qt5::Test
        TelegramQt${QT_VERSION_MAJOR}::Core
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

target_sources(tst_CTelegramTransport PRIVATE
    utils/TestTransport.hpp
)

target_sources(tst_RpcLayer PRIVATE
    utils/TestTransport.hpp
)

target_link_libraries(tst_utils test_keys_data)
