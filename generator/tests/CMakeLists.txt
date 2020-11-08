
add_executable(tst_generator
    tst_generator/tst_generator.cpp
    ../Generator.cpp
)

target_link_libraries(tst_generator
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Test
    ZLIB::ZLIB
)

add_test(NAME tst_generator COMMAND tst_generator)
