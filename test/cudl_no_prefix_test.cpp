#include <gtest/gtest.h>
#include <cstdint>

#define CUDL_PREFIX
#include <cudl.h>

CUDL_ADD_UNIT(v, uint32_t)
CUDL_ADD_UNIT(mv, uint32_t)

CUDL_ADD_CONVERSION_FACTOR(v, mv, 1000)
CUDL_ADD_CONVERSION_FRACTION_FACTOR(mv, v, 1, 1000)

TEST(test_cudl_no_prefix, whenUsingNopUnits_valueRemainsTheSame)
{
    v_t volts = v(10);
    ASSERT_EQ(CUDL_GET(volts), 10);
}

TEST(test_cudl_no_prefix, whenUsingVolts_canConvertToMillivolts)
{
    v_t volts = v(10);
    mv_t mvolts = from_v_to_mv(volts);
    ASSERT_EQ(CUDL_GET(mvolts), 10000);
}

TEST(test_cudl_no_prefix, whenUsingMillivolts_canConvertToVolts)
{
    mv_t mvolts = mv(5000);

    v_t volts = from_mv_to_v(mvolts);
    ASSERT_EQ(CUDL_GET(volts), 5);
}
