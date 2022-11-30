#include <cudl.h>
#include <stdint.h>

CUDL_ADD_UNIT(v, uint8_t)
CUDL_ADD_BITWISE_NOT_OP(v, _bnot)

static void bar(void) {
    cudl_v_t v1 = cudl_v(10);
    cudl_v_t result = cudl_v_bnot(v1); // result will contain 245.
}
/**
 * @example add_no_unit_op_example.c
 * Example to show how to use the #CUDL_ADD_NO_UNIT_OP.
 */
