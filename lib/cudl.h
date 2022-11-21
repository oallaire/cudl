/**
 * @file cudl.h
 * @author Olivier Allaire
 * @brief This library is meant to make units more usable in a C code base. It takes inspiration from the C++ user
 * defined literals. See the documentation for usage.
 */

#ifndef CUDL_H
#define CUDL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CUDL_PREFIX
/**
 * @brief Prefix to prevent name clashes. If it is not a problem to the user, it can be redefined or set to an empty
 * value.
 */
#define CUDL_PREFIX cudl_
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/**
 * @brief Level 2 stringification macro. For internal use only.
 */
#define __CUDL_L2STR(_p, _s) _p##_s// NOLINT(bugprone-reserved-identifier)
/**
 * @brief Level 1 stringification macro. For internal use only.
 */
#define __CUDL_L1STR(_p, _s) __CUDL_L2STR(_p, _s)// NOLINT(bugprone-reserved-identifier)
/**
 * @brief Utility macro to append CUDL_PREFIX at the beginning of the given token. For internal use only.
 */
#define __CUDL_AP(_s) __CUDL_L1STR(CUDL_PREFIX, _s)// NOLINT(bugprone-reserved-identifier)
/**
 * @brief Utility macro meant to easily rebuild the type name associated to the unit name. For internal use only.
 */
#define __CUDL_UT(_name) __CUDL_L1STR(__CUDL_AP(_name), _t)// NOLINT(bugprone-reserved-identifier)

/**
 * @brief Utility macro meant to allow reuse of other macros that requires an op. For internal use only.
 */
#define __CUDL_NOP(_x) _x// NOLINT(bugprone-reserved-identifier)
#endif                   //DOXYGEN_SHOULD_SKIP_THIS

/**
 * @brief Function to add a unit.
 * @param _name The name of the unit. This will be used to define the unit type and the init function.
 * @code
ADD_2(_x) (_x + 2)
CUDL_ADD_UNIT_WITH_OP(my_unit, int, ADD_2)
// This type and function will now exist
cudl_my_unit_t foo = cudl_my_unit(5); // Foo will be equal to 7
 * @endcode
 * @param _type The underlying storage type to use.
 * @param _op Should be a macro or function that can take _type as an input and returns _type as a value.
 */
#define CUDL_ADD_UNIT_WITH_OP(_name, _type, _op)                                                                       \
    typedef struct {                                                                                                   \
        _type value;                                                                                                   \
    } __CUDL_UT(_name);                                                                                                \
    static inline __CUDL_UT(_name) __CUDL_AP(_name)(_type input_value) {                                               \
        __CUDL_UT(_name) ct;                                                                                           \
        ct.value = _op(input_value);                                                                                   \
        return ct;                                                                                                     \
    }

/**
 * @brief Function to add a unit.
 * @param _name The name of the unit. This will be used to define the unit type and the init function.
 * @code
CUDL_ADD_UNIT(my_unit, int)
// This type and function will now exist
cudl_my_unit_t foo = cudl_my_unit(5); // Foo will be equal to 5
 * @endcode
 * @param _type The underlying storage type to use.
 */
#define CUDL_ADD_UNIT(_name, _type) CUDL_ADD_UNIT_WITH_OP(_name, _type, __CUDL_NOP)

/**
 * @brief Utility macro to access the underlying value when usage requires to interact with non cudl variables.
 * @param _value This must be a unit type instance defined by CUDL_ADD_UNIT*.
 */
#define CUDL_GET(_value) (_value).value

/**
 * @brief This function allows to a conversion from one unit to another. It does this with a fraction. The from value
 * will be multiplied by _n and divided by _d.
 * @code
CUDL_ADD_UNIT(v, uint32_t)
CUDL_ADD_UNIT(mv, uint32_t)

CUDL_ADD_CONVERSION_FACTOR(v, mv, 1000)
CUDL_ADD_CONVERSION_FRACTION_FACTOR(mv, v, 1, 1000)

void foo(void) {
    cudl_v_t volts = v(10);
    cudl_mv_t mvolts = cudl_from_v_to_mv(volts);      // mvolts will be equal to 10000 internally.
    cudl_v_t other_volts = cudl_from_mv_to_v(mvolts); // other_volts will be equal to 10 internally.
}
 * @endcode
 * @param _from The unit to convert from. It is expected to be the same as the _name param used with CUDL_ADD_UNIT*.
 * @param _to The unit to convert to. It is expected to be the same as the _name param used with CUDL_ADD_UNIT*.
 * @param _explicative String to append to the beginning of the function name to make it unique.
 * @param _n Numerator of the fraction.
 * @param _d Denominator of the fraction.
 */
#define CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR(_from, _to, _explicative, _n, _d)                                 \
    static inline __CUDL_UT(_to) __CUDL_L1STR(__CUDL_AP(_explicative), _to)(__CUDL_UT(_from) from_value) {             \
        __CUDL_UT(_to) to_value;                                                                                       \
        to_value.value = (from_value.value * _n) / _d;                                                                 \
        return to_value;                                                                                               \
    }

/**
 * @brief Simplified version of the #CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR to have a default explicative.
 * @param _from See #CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR documentation.
 * @param __to See #CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR documentation.
 * @param _n See #CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR documentation.
 * @param _d See #CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR documentation.
 */
#define CUDL_ADD_CONVERSION_FRACTION_FACTOR(_from, __to, _n, _d)                                                       \
    CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR(_from, __to, from_##_from##_to_, _n, _d)

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

#endif//CUDL_H
