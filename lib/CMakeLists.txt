project(cudl-lib LANGUAGES C)

add_library(${PROJECT_NAME} INTERFACE cudl.h)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_C_STANDARD 17)

add_library(cudl::lib ALIAS ${PROJECT_NAME})
