#include <cudl.h>
#include <stdint.h>

CUDL_ADD_UNIT(v, uint32_t)
CUDL_ADD_NO_TRANSFORM_OP(v, _add, +)

static void bar(void) {
    cudl_v_t v1 = cudl_v(10);
    cudl_v_t v2 = cudl_v(42);
    cudl_v_t result = cudl_v_add(v1, v2); // result will contain 52.
}
/**
 * @example add_no_transform_op_example.c
 * Example to show how to use the #CUDL_ADD_NO_TRANSFORM_OP.
 */
