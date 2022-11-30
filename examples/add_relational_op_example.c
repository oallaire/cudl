#include <cudl.h>
#include <stdint.h>

CUDL_ADD_UNIT(v, uint32_t)
CUDL_ADD_RELATIONAL_OP(v, _eq, ==)

static void bar(void) {
    cudl_v_t v1 = cudl_v(10);
    cudl_v_t v2 = cudl_v(11);
    bool result = cudl_v_eq(v1, v2); // result will contain false.
}
/**
 * @example add_relational_op_example.c
 * Example to show how to use the #CUDL_ADD_RELATIONAL_OP.
 */
