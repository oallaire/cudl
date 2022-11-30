#include <cudl.h>
#include <stdint.h>

CUDL_ADD_UNIT(v, uint32_t)
CUDL_ADD_UNIT(mv, uint32_t)

CUDL_ADD_CONVERSION_FACTOR(v, mv, 1000)
CUDL_ADD_CONVERSION_FRACTION_FACTOR(mv, v, 1, 1000)

static void bar(void) {
    cudl_v_t volts = cudl_v(10);
    cudl_mv_t mvolts = cudl_from_v_to_mv(volts);      // mvolts will be equal to 10000 internally.
    cudl_v_t other_volts = cudl_from_mv_to_v(mvolts); // other_volts will be equal to 10 internally.
}
/**
 * @example add_conversion_example.c
 * Example to show how to use the #CUDL_ADD_CONVERSION_FACTOR and #CUDL_ADD_CONVERSION_FRACTION_FACTOR.
 */
