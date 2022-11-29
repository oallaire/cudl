#include <gtest/gtest.h>
#include <cudl.h>
#include <cstdint>

CUDL_ADD_UNIT(v, uint32_t)
CUDL_ADD_INTEGER_OPERATORS(v, uint32_t)

CUDL_ADD_UNIT(mv, uint32_t)

CUDL_ADD_CONVERSION_FACTOR(v, mv, 1000)
CUDL_ADD_CONVERSION_FRACTION_FACTOR(mv, v, 1, 1000)

TEST(cudl_integer_test, whenUsingNopUnits_valueRemainsTheSame)
{
    cudl_v_t volts = cudl_v(10);
    ASSERT_EQ(CUDL_GET(volts), 10);
}

TEST(cudl_integer_test, whenUsingVolts_canConvertToMillivolts)
{
    cudl_v_t volts = cudl_v(10);
    cudl_mv_t mvolts = cudl_from_v_to_mv(volts);
    ASSERT_EQ(CUDL_GET(mvolts), 10000);
}

TEST(cudl_integer_test, whenUsingMillivolts_canConvertToVolts)
{
    cudl_mv_t mvolts = cudl_mv(5000);

    cudl_v_t volts = cudl_from_mv_to_v(mvolts);
    ASSERT_EQ(CUDL_GET(volts), 5);
}

TEST(cudl_integer_test, add)
{
    cudl_v_t v1 = cudl_v(10);
    cudl_v_t v2 = cudl_v(42);
    cudl_v_t result = cudl_v_add(v1, v2);

    ASSERT_EQ(CUDL_GET(result), 52);
}

TEST(cudl_integer_test, sub)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t v2 = cudl_v(10);
    cudl_v_t result = cudl_v_sub(v1, v2);

    ASSERT_EQ(CUDL_GET(result), 32);
}

TEST(cudl_integer_test, multiply)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t result = cudl_v_mul(v1, 10);

    ASSERT_EQ(CUDL_GET(result), 420);
}

TEST(cudl_integer_test, divide)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t result = cudl_v_div(v1, 10);

    ASSERT_EQ(CUDL_GET(result), 4);
}

TEST(cudl_integer_test, modulo)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t result = cudl_v_mod(v1, 10);

    ASSERT_EQ(CUDL_GET(result), 2);
}

TEST(cudl_integer_test, equal)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t v2 = cudl_v(42);
    cudl_v_t v3 = cudl_v(43);

    ASSERT_TRUE(cudl_v_eq(v1, v2));
    ASSERT_FALSE(cudl_v_eq(v1, v3));
}

TEST(cudl_integer_test, notEqual)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t v2 = cudl_v(42);
    cudl_v_t v3 = cudl_v(43);

    ASSERT_FALSE(cudl_v_ne(v1, v2));
    ASSERT_TRUE(cudl_v_ne(v1, v3));
}

TEST(cudl_integer_test, lessThan)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t v2 = cudl_v(1);
    cudl_v_t v3 = cudl_v(1);

    ASSERT_TRUE(cudl_v_lt(v2, v1));
    ASSERT_FALSE(cudl_v_lt(v1, v2));
    ASSERT_FALSE(cudl_v_lt(v2, v3));
}

TEST(cudl_integer_test, lessThanOrEqual)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t v2 = cudl_v(1);
    cudl_v_t v3 = cudl_v(1);

    ASSERT_TRUE(cudl_v_le(v2, v1));
    ASSERT_FALSE(cudl_v_le(v1, v2));
    ASSERT_TRUE(cudl_v_le(v2, v3));
}

TEST(cudl_integer_test, greaterThan)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t v2 = cudl_v(100);
    cudl_v_t v3 = cudl_v(100);

    ASSERT_TRUE(cudl_v_gt(v2, v1));
    ASSERT_FALSE(cudl_v_gt(v1, v2));
    ASSERT_FALSE(cudl_v_gt(v2, v3));
}

TEST(cudl_integer_test, greaterThanOrEqual)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t v2 = cudl_v(100);
    cudl_v_t v3 = cudl_v(100);

    ASSERT_TRUE(cudl_v_ge(v2, v1));
    ASSERT_FALSE(cudl_v_ge(v1, v2));
    ASSERT_TRUE(cudl_v_ge(v2, v3));
}

TEST(cudl_integer_test, and)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t result = cudl_v_and(v1, 0xF);

    ASSERT_EQ(CUDL_GET(result), 10);
}

TEST(cudl_integer_test, or)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t result = cudl_v_or(v1, 0xF);

    ASSERT_EQ(CUDL_GET(result), 47);
}

TEST(cudl_integer_test, xor)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t result = cudl_v_xor(v1, 0xF);

    ASSERT_EQ(CUDL_GET(result), 37);
}

TEST(cudl_integer_test, bitShiftLeft)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t result = cudl_v_bsl(v1, 1);

    ASSERT_EQ(CUDL_GET(result), 84);
}

TEST(cudl_integer_test, bitShiftRight)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t result = cudl_v_bsr(v1, 1);

    ASSERT_EQ(CUDL_GET(result), 21);
}

TEST(cudl_integer_test, binaryNot)
{
    cudl_v_t v1 = cudl_v(42);
    cudl_v_t result = cudl_v_bnot(v1);

    ASSERT_EQ(CUDL_GET(result), UINT32_MAX - 42);
}
