#include <gtest/gtest.h>
#include <cstdint>

#define CUDL_PREFIX utest_
#include <cudl.h>

CUDL_ADD_UNIT(v, uint32_t)
CUDL_ADD_UNIT(mv, uint32_t)

CUDL_ADD_CONVERSION_FACTOR(v, mv, 1000)
CUDL_ADD_CONVERSION_FRACTION_FACTOR(mv, v, 1, 1000)

TEST(test_cudl_prefix, whenUsingNopUnits_valueRemainsTheSame)
{
    utest_v_t volts = utest_v(10);
    ASSERT_EQ(CUDL_GET(volts), 10);
}

TEST(test_cudl_prefix, whenUsingVolts_canConvertToMillivolts)
{
    utest_v_t volts = utest_v(10);
    utest_mv_t mvolts = utest_from_v_to_mv(volts);
    ASSERT_EQ(CUDL_GET(mvolts), 10000);
}

TEST(test_cudl_prefix, whenUsingMillivolts_canConvertToVolts)
{
    utest_mv_t mvolts = utest_mv(5000);

    utest_v_t volts = utest_from_mv_to_v(mvolts);
    ASSERT_EQ(CUDL_GET(volts), 5);
}
