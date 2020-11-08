
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
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Test
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
