#include <gtest/gtest.h>
#include <cudl.h>
#include <cstdint>

CUDL_ADD_UNIT(_v, uint32_t)
CUDL_ADD_UNIT(_mv, uint32_t)

CUDL_ADD_CONVERSION_FACTOR(_v, _mv, 1000)
CUDL_ADD_CONVERSION_FRACTION_FACTOR(_mv, _v, 1, 1000)

TEST(test_cudl, whenUsingNopUnits_valueRemainsTheSame)
{
    _v_t volts = _v(10);
    ASSERT_EQ(CUDL_GET(volts), 10);
}

TEST(test_cudl, whenUsingVolts_canConvertToMillivolts)
{
    _v_t volts = _v(10);
    _mv_t mvolts = from_v_to_mv(volts);
    ASSERT_EQ(CUDL_GET(mvolts), 10000);
}

TEST(test_cudl, whenUsingMillivolts_canConvertToVolts)
{
    _mv_t mvolts = _mv(5000);
    
    _v_t volts = from_mv_to_v(mvolts);
    ASSERT_EQ(CUDL_GET(volts), 5);
}
