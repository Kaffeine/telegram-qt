
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

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${ZLIB_INCLUDE_DIR}
)

add_executable(tst_generator
    tst_generator/tst_generator.cpp
    ../Generator.cpp
)

target_link_libraries(tst_generator LINK_PUBLIC
    Qt5::Core
    Qt5::Test
    ${ZLIB_LIBRARIES}
)

add_test(NAME tst_generator COMMAND tst_generator)
