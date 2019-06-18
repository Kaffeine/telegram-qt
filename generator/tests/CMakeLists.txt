
enable_testing()

add_executable(tst_generator
    tst_generator/tst_generator.cpp
    ../Generator.cpp
)

target_link_libraries(tst_generator
    Qt5::Core
    Qt5::Test
    ZLIB::ZLIB
)

add_test(NAME tst_generator COMMAND tst_generator)
