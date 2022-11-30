#include <cudl.h>

#define ADD_2(_x) (_x + 2)
CUDL_ADD_UNIT_WITH_OP(my_unit, int, ADD_2)

static void bar(void) {
    // This type and function will now exist
    cudl_my_unit_t foo = cudl_my_unit(5); // Foo will be equal to 7
}
/**
 * @example add_unit_with_init_op_example.c
 * Example to show how to use the #CUDL_ADD_UNIT_WITH_OP.
 */
