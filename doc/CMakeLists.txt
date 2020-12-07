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

set(QDOCCONFFILE ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.qdocconf)
set(QHELPFILE  ${CMAKE_PROJECT_NAME}.qhp)
set(QCHFILE ${CMAKE_PROJECT_NAME}.qch)

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

set(VARS
    "QT_INSTALL_DOCS=${QT_INSTALL_DOCS}"
    "PROJECT_VERSION=${TelegramQt_VERSION}"
)

add_custom_command(OUTPUT ${QCHFILE}
    ${EXPORT_VARS_COMMANDS}
    COMMAND ${VARS} ${QDOC_EXECUTABLE} ${QDOCCONFFILE} --outputdir=${CMAKE_CURRENT_BINARY_DIR} -indexdir ${QT_INSTALL_DOCS} -no-link-errors
    COMMAND ${VARS} ${QHELPGENERATOR_EXECUTABLE} ${QHELPFILE} -o ${QCHFILE}
    DEPENDS ${QDOCCONFFILE}
    VERBATIM
)

add_custom_target(qch_docs ALL
    DEPENDS ${QCHFILE}
    SOURCES ${QDOCCONFFILE}
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${QCHFILE}
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
    COMPONENT Data
)
