/**
 * @file cudl.h
 * @author Olivier Allaire
 * @brief This library is meant to make units more usable in a C code base. It takes inspiration from the C++ user
 * defined literals. See the documentation for usage.
 */

#ifndef CUDL_H
#define CUDL_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * @brief Utility macro meant to easily rebuild the type name associated to the unit name. For internal use only.
 */
#define __CUDLE_UT(_name) _name##_t // NOLINT(bugprone-reserved-identifier)

/**
 * @brief Utility macro meant to allow reuse of other macros that requires an op. For internal use only.
 */
#define __CUDLE_NOP(_x) _x // NOLINT(bugprone-reserved-identifier)

#endif //DOXYGEN_SHOULD_SKIP_THIS

/**
 * @brief Function to add a unit.
 * @param _name The name of the unit. This will be used to define the unit type and the init function.
 * @code
ADD_2(_x) (_x + 2)
CUDL_ADD_UNIT_WITH_OP(my_unit, int, ADD_2)
// This type and function will now exist
my_unit_t foo = my_unit(5); // Foo will be equal to 7
 * @endcode
 * @param _type The underlying storage type to use.
 * @param _op Should be a macro or function that can take _type as an input and returns _type as a value.
 */
#define CUDL_ADD_UNIT_WITH_OP(_name, _type, _op)              \
typedef struct _name##_s { _type value; } __CUDLE_UT(_name);  \
static inline __CUDLE_UT(_name) _name(_type input_value) {    \
    __CUDLE_UT(_name) ct;                                     \
    ct.value = _op(input_value);                              \
    return ct;                                                \
}

/**
 * @brief Function to add a unit.
 * @param _name The name of the unit. This will be used to define the unit type and the init function.
 * @code
CUDL_ADD_UNIT(my_unit, int)
// This type and function will now exist
my_unit_t foo = my_unit(5); // Foo will be equal to 5
 * @endcode
 * @param _type The underlying storage type to use.
 */
#define CUDL_ADD_UNIT(_name, _type) CUDL_ADD_UNIT_WITH_OP(_name, _type, __CUDLE_NOP)

/**
 * @brief Utility macro to access the underlying value when usage requires to interact with non cudl variables.
 * @param _value This must be a unit type instance defined by CUDL_ADD_UNIT*.
 */
#define CUDL_GET(_value) (_value).value

/**
 * @brief This function allows to a conversion from one unit to another. It does this with a fraction. The from value
 * will be multiplied by _n and divided by _d.
 * @code
CUDL_ADD_UNIT(_v, uint32_t)
CUDL_ADD_UNIT(_mv, uint32_t)

CUDL_ADD_CONVERSION_FACTOR(_v, _mv, 1000)
CUDL_ADD_CONVERSION_FRACTION_FACTOR(_mv, _v, 1, 1000)

void foo(void) {
    _v_t volts = _v(10);
    _mv_t mvolts = from_v_to_mv(volts);      // mvolts will be equal to 10000 internally.
    _v_t other_volts = from_mv_to_v(mvolts); // other_volts will be equal to 10 internally.
}
 * @endcode
 * @param _from The unit to convert from. It is expected to be the same as the _name param used with CUDL_ADD_UNIT*.
 * @param _to The unit to convert to. It is expected to be the same as the _name param used with CUDL_ADD_UNIT*.
 * @param _explicative String to append to the beginning of the function name to make it unique.
 * @param _n Numerator of the fraction.
 * @param _d Denominator of the fraction.
 */
#define CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR(_from, _to, _explicative, _n, _d)       \
static inline __CUDLE_UT(_to) _explicative##_to(__CUDLE_UT(_from) from_value) {              \
    __CUDLE_UT(_to) to_value;                                                                \
    to_value.value = (from_value.value * _n) / _d;                                           \
    return to_value;                                                                         \
}

/**
 * @brief Simplified version of the #CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR to have a default explicative.
 * @param _from See #CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR documentation.
 * @param __to See #CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR documentation.
 * @param _n See #CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR documentation.
 * @param _d See #CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR documentation.
 */
#define CUDL_ADD_CONVERSION_FRACTION_FACTOR(_from, __to, _n, _d) \
CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR(_from, __to, from##_from##_to, _n, _d)

/**
 * @brief Simplified version of the #CUDL_ADD_CONVERSION_FRACTION_FACTOR to have a default divider of 1. In other words,
 * this adds a conversion that is a simple multiplication.
 * @param _from See #CUDL_ADD_CONVERSION_FRACTION_FACTOR documentation.
 * @param _to See #CUDL_ADD_CONVERSION_FRACTION_FACTOR documentation.
 * @param _factor The multiplication facto to convert _from to _to.
 */
#define CUDL_ADD_CONVERSION_FACTOR(_from, _to, _factor) CUDL_ADD_CONVERSION_FRACTION_FACTOR(_from, _to, _factor, 1)

#ifdef __cplusplus
}
#endif

#endif //CUDL_H
