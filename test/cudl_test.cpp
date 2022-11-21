#include <gtest/gtest.h>
#include <cudl.h>
#include <cstdint>

CUDL_ADD_UNIT(v, uint32_t)
CUDL_ADD_UNIT(mv, uint32_t)

CUDL_ADD_CONVERSION_FACTOR(v, mv, 1000)
CUDL_ADD_CONVERSION_FRACTION_FACTOR(mv, v, 1, 1000)

TEST(test_cudl, whenUsingNopUnits_valueRemainsTheSame)
{
    cudl_v_t volts = cudl_v(10);
    ASSERT_EQ(CUDL_GET(volts), 10);
}

TEST(test_cudl, whenUsingVolts_canConvertToMillivolts)
{
    cudl_v_t volts = cudl_v(10);
    cudl_mv_t mvolts = cudl_from_v_to_mv(volts);
    ASSERT_EQ(CUDL_GET(mvolts), 10000);
}

TEST(test_cudl, whenUsingMillivolts_canConvertToVolts)
{
    cudl_mv_t mvolts = cudl_mv(5000);

    cudl_v_t volts = cudl_from_mv_to_v(mvolts);
    ASSERT_EQ(CUDL_GET(volts), 5);
}
