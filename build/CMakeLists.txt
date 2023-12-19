cmake_minimum_required(VERSION 3.10)

project(kirill_lab)

set(SOURCES 
  "individual_project.cpp"
)

file(GLOB TEXT_FILES ${CMAKE_SOURCE_DIR}/*.txt)
file(GLOB INI_FILES ${CMAKE_SOURCE_DIR}/*.ini)

add_custom_target(
    CopyFilesTarget
    COMMAND ${CMAKE_COMMAND} -E copy ${TEXT_FILES} ${CMAKE_BINARY_DIR}
    DEPENDS ${TEXT_FILES}
)

add_custom_target(
    CopyIniFilesTarget
    COMMAND ${CMAKE_COMMAND} -E copy ${INI_FILES} ${CMAKE_BINARY_DIR}
    DEPENDS ${INI_FILES}
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_dependencies(${PROJECT_NAME} CopyFilesTarget)
add_dependencies(${PROJECT_NAME} CopyIniFilesTarget) 


