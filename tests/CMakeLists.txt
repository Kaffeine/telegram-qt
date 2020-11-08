
add_library(TelegramQt${QT_VERSION_MAJOR}Test INTERFACE)
add_library(TelegramQt${QT_VERSION_MAJOR}::Test ALIAS TelegramQt${QT_VERSION_MAJOR}Test)

target_include_directories(TelegramQt${QT_VERSION_MAJOR}Test INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

set(test_extra_META_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/TestAuthProvider.hpp
)

foreach(test_name
    tst_all
    tst_ConnectionApi
    tst_ContactsApi
    tst_FilesApi
    tst_MessagesApi
)
    add_executable(${test_name} ${test_name}/${test_name}.cpp ${test_extra_META_HEADERS})
    target_link_libraries(${test_name} PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Test
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
