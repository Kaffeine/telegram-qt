find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(ZLIB REQUIRED)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

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

#set(test_keys_data_RESOURCES keys-data.qrc)
#set(test_keys_data_SOURCES keys-data.cpp)

#QT5_ADD_RESOURCES(test_keys_data_RCC ${test_keys_data_RESOURCES})

add_library(test_keys_data STATIC keys_data.cpp keys_data.qrc)

target_include_directories(test_keys_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(test_keys_data LINK_PUBLIC
    Qt5::Core
    ${ZLIB_LIBRARIES}
)
