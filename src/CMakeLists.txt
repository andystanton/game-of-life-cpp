FILE(GLOB_RECURSE project_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

SET(project_LIBS libglew_static glfw ${GLFW_LIBRARIES})

SET(project_BIN ${PROJECT_NAME})

SET(project_MAIN ${MAINFOLDER}/src/main.cpp)

FOREACH(sourceFile ${project_SRCS})
    IF(NOT(${sourceFile} STREQUAL ${project_MAIN}))
        SET(ALL_SRCS ${ALL_SRCS} ${sourceFile} CACHE INTERNAL "source file")
    ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${project_BIN} ${project_SRCS})

INCLUDE_DIRECTORIES(${GLFW_INCLUDE_PATH}
                    ${GLEW_INCLUDE_PATH}
                    ${GLM_INCLUDE_PATH})

TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})

COPY_FILES("${MAINFOLDER}/src/shaders" "${EXECUTABLE_OUTPUT_PATH}")

SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)

INSTALL(TARGETS ${project_BIN} DESTINATION bin)
