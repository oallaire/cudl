#include <cudl.h>
#include <stdint.h>

CUDL_ADD_UNIT(v, uint32_t)
CUDL_ADD_NO_UNIT_OP(v, _mul, *, uint32_t)

static void bar(void) {
    cudl_v_t v1 = cudl_v(10);
    cudl_v_t result = cudl_v_mul(v1, 2); // result will contain 20.
}
/**
 * @example add_no_unit_op_example.c
 * Example to show how to use the #CUDL_ADD_NO_UNIT_OP.
 */
