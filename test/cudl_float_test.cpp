#include <gtest/gtest.h>
#include <cudl.h>
#include <cmath>

CUDL_ADD_UNIT(rad, double)
CUDL_ADD_COMMON_OPERATORS(rad, double)

CUDL_ADD_UNIT(deg, double)
CUDL_ADD_COMMON_OPERATORS(deg, double)

CUDL_ADD_CONVERSION_FRACTION_FACTOR(rad, deg, 180.0, M_PI)
CUDL_ADD_CONVERSION_FRACTION_FACTOR(deg, rad, M_PI, 180.0)

#define CUDL_FLOAT_TEST_ABS_ERROR 0.000001

TEST(cudl_float_test, whenUsingNopUnits_valueRemainsTheSame)
{
    cudl_rad_t rads = cudl_rad(M_PI);
    ASSERT_NEAR(CUDL_GET(rads), M_PI, CUDL_FLOAT_TEST_ABS_ERROR);
}

TEST(cudl_float_test, whenUsingRads_canConvertToDegs)
{
    cudl_rad_t rads = cudl_rad(M_PI);
    cudl_deg_t degs = cudl_from_rad_to_deg(rads);
    ASSERT_NEAR(CUDL_GET(degs), 180.0, CUDL_FLOAT_TEST_ABS_ERROR);

    rads = cudl_rad(M_PI / 4);
    degs = cudl_from_rad_to_deg(rads);
    ASSERT_NEAR(CUDL_GET(degs), 45.0, CUDL_FLOAT_TEST_ABS_ERROR);
}

TEST(cudl_float_test, whenUsingDegs_canConvertToRads)
{
    cudl_deg_t degs = cudl_deg(180.0);
    cudl_rad_t rads = cudl_from_deg_to_rad(degs);
    ASSERT_NEAR(CUDL_GET(rads), M_PI, CUDL_FLOAT_TEST_ABS_ERROR);

    degs = cudl_deg(45.0);
    rads = cudl_from_deg_to_rad(degs);
    ASSERT_NEAR(CUDL_GET(rads), M_PI / 4, CUDL_FLOAT_TEST_ABS_ERROR);
}

TEST(cudl_float_test, add)
{
    cudl_rad_t r1 = cudl_rad(M_PI / 2);
    cudl_rad_t r2 = cudl_rad(M_PI / 2);
    cudl_rad_t result = cudl_rad_add(r1, r2);
    ASSERT_NEAR(CUDL_GET(result), M_PI, CUDL_FLOAT_TEST_ABS_ERROR);
}

TEST(cudl_float_test, sub)
{
    cudl_rad_t r1 = cudl_rad(3.0 * M_PI / 2);
    cudl_rad_t r2 = cudl_rad(M_PI / 2);
    cudl_rad_t result = cudl_rad_sub(r1, r2);
    ASSERT_NEAR(CUDL_GET(result), M_PI, CUDL_FLOAT_TEST_ABS_ERROR);
}

TEST(cudl_float_test, multiply)
{
    cudl_rad_t r1 = cudl_rad(M_PI / 2);
    cudl_rad_t result = cudl_rad_mul(r1, 2.0);
    ASSERT_NEAR(CUDL_GET(result), M_PI, CUDL_FLOAT_TEST_ABS_ERROR);
}

TEST(cudl_float_test, divide)
{
    cudl_rad_t r1 = cudl_rad(M_PI * 2);
    cudl_rad_t result = cudl_rad_div(r1, 2.0);
    ASSERT_NEAR(CUDL_GET(result), M_PI, CUDL_FLOAT_TEST_ABS_ERROR);
}

TEST(cudl_float_test, equal)
{
    cudl_rad_t r1 = cudl_rad(M_PI);
    cudl_rad_t r2 = cudl_rad(M_PI);
    cudl_rad_t r3 = cudl_rad(M_PI / 2);

    ASSERT_TRUE(cudl_rad_eq(r1, r2));
    ASSERT_FALSE(cudl_rad_eq(r1, r3));
}

TEST(cudl_float_test, notEqual)
{
    cudl_rad_t r1 = cudl_rad(M_PI);
    cudl_rad_t r2 = cudl_rad(M_PI);
    cudl_rad_t r3 = cudl_rad(M_PI / 2);

    ASSERT_FALSE(cudl_rad_ne(r1, r2));
    ASSERT_TRUE(cudl_rad_ne(r1, r3));
}

TEST(cudl_float_test, lessThan)
{
    cudl_rad_t r1 = cudl_rad(M_PI);
    cudl_rad_t r2 = cudl_rad(M_PI / 2);
    cudl_rad_t r3 = cudl_rad(M_PI / 2);

    ASSERT_TRUE(cudl_rad_lt(r2, r1));
    ASSERT_FALSE(cudl_rad_lt(r1, r2));
    ASSERT_FALSE(cudl_rad_lt(r2, r3));
}

TEST(cudl_float_test, lessThanOrEqual)
{
    cudl_rad_t r1 = cudl_rad(M_PI);
    cudl_rad_t r2 = cudl_rad(M_PI / 2);
    cudl_rad_t r3 = cudl_rad(M_PI / 2);

    ASSERT_TRUE(cudl_rad_le(r2, r1));
    ASSERT_FALSE(cudl_rad_le(r1, r2));
    ASSERT_TRUE(cudl_rad_le(r2, r3));
}

TEST(cudl_float_test, greaterThan)
{
    cudl_rad_t r1 = cudl_rad(M_PI);
    cudl_rad_t r2 = cudl_rad(M_PI * 2);
    cudl_rad_t r3 = cudl_rad(M_PI * 2);

    ASSERT_TRUE(cudl_rad_gt(r2, r1));
    ASSERT_FALSE(cudl_rad_gt(r1, r2));
    ASSERT_FALSE(cudl_rad_gt(r2, r3));
}

TEST(cudl_float_test, greaterThanOrEqual)
{
    cudl_rad_t r1 = cudl_rad(M_PI);
    cudl_rad_t r2 = cudl_rad(M_PI * 2);
    cudl_rad_t r3 = cudl_rad(M_PI * 2);

    ASSERT_TRUE(cudl_rad_ge(r2, r1));
    ASSERT_FALSE(cudl_rad_ge(r1, r2));
    ASSERT_TRUE(cudl_rad_ge(r2, r3));
}
