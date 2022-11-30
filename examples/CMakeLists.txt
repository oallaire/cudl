project(cudl-examples LANGUAGES C)

add_executable(${PROJECT_NAME} main.c add_unit_with_init_op_example.c add_unit_example.c add_conversion_example.c add_no_transform_op_example.c add_no_unit_op_example.c add_relational_op_example.c add_bitwise_not_op_example.c)
target_link_libraries(${PROJECT_NAME} cudl::lib)
