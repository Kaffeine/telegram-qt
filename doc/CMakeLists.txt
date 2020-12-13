find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Help)

# Documentation

# from https://github.com/fastogt/cmake/blob/master/integrate-qt.cmake
function(QUERY_QMAKE RESULT VAR)
  get_target_property(QMAKE_EXECUTABLE Qt${QT_VERSION_MAJOR}::qmake LOCATION)
  exec_program(${QMAKE_EXECUTABLE} ARGS "-query ${VAR}" RETURN_VALUE return_code OUTPUT_VARIABLE output)
  if(NOT return_code)
    file(TO_CMAKE_PATH "${output}" output)
    set(${RESULT} ${output} PARENT_SCOPE)
  endif()
endfunction()

set(QDOCCONFFILE ${CMAKE_CURRENT_SOURCE_DIR}/TelegramQt.qdocconf)
set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/output")
set(QHELPFILE ${OUTPUT_DIR}/${CMAKE_PROJECT_NAME}.qhp)
set(QCHFILE ${OUTPUT_DIR}/${CMAKE_PROJECT_NAME}.qch)

query_qmake(QT_INSTALL_BINS QT_INSTALL_BINS)
query_qmake(QT_INSTALL_DOCS QT_INSTALL_DOCS)
find_program(QDOC_EXECUTABLE qdoc
    "${QT_INSTALL_BINS}"
    NO_DEFAULT_PATH
)
find_program(QHELPGENERATOR_EXECUTABLE qhelpgenerator
    "${QT_INSTALL_BINS}"
    NO_DEFAULT_PATH
)

set(QDOC_QT_INCLUDES)
if(NOT Qt${QT_VERSION_MAJOR}_VERSION VERSION_LESS "5.11.0")
    set(QDOC_QT_INCLUDES)
    get_target_property(TelegramQt_INCLUDE_DIRS
        TelegramQt${QT_VERSION_MAJOR}::Core INCLUDE_DIRECTORIES)
    foreach(_INC
            ${${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}}
            ${Qt${QT_VERSION_MAJOR}Core_INCLUDE_DIRS}
            ${Qt${QT_VERSION_MAJOR}Network_INCLUDE_DIRS}
            ${TelegramQt_INCLUDE_DIRS}
            ${CMAKE_CURRENT_SOURCE_DIR}/includes
        )
        if(_INC MATCHES ".*INSTALL_INTERFACE.*")
            # We need the headers at the build stage. Omit the other stuff to not
            # break the doc command by empty -I arguments.
            continue()
        endif()
        set(QDOC_QT_INCLUDES ${QDOC_QT_INCLUDES} -I${_INC})
    endforeach()
    unset(TelegramQt_INCLUDE_DIRS)
endif()

set(VARS
    "QT_INSTALL_DOCS=${QT_INSTALL_DOCS}"
    "PROJECT_VERSION=${TelegramQt_VERSION}"
    "TelegramQt_SOURCE_DIR=${PROJECT_SOURCE_DIR}/TelegramQt"
)

add_custom_command(OUTPUT ${QCHFILE}
    ${EXPORT_VARS_COMMANDS}
    COMMAND ${VARS} ${QDOC_EXECUTABLE} ${QDOCCONFFILE}
        ${QDOC_QT_INCLUDES}
        --outputdir ${OUTPUT_DIR}
        --indexdir ${QT_INSTALL_DOCS}
        --no-link-errors
    COMMAND ${VARS} ${QHELPGENERATOR_EXECUTABLE} ${QHELPFILE} -o ${QCHFILE}
    DEPENDS ${QDOCCONFFILE}
    VERBATIM
)

add_custom_target(qch_docs ALL
    DEPENDS ${QCHFILE}
    SOURCES ${QDOCCONFFILE}
)

install(
    FILES ${QCHFILE}
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
    COMPONENT Data
)
