#include <cudl.h>

CUDL_ADD_UNIT(my_unit, int)

static void bar(void) {
    // This type and function will now exist
    cudl_my_unit_t foo = cudl_my_unit(5); // Foo will be equal to 5
}
/**
 * @example add_unit_example.c
 * Example to show how to use the #CUDL_ADD_UNIT.
 */
