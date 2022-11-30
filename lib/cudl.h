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

#include <stdbool.h>

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
 * @brief Function to add a unit with an initialisation operation.
 * @include add_unit_with_init_op_example.c
 * @param _name The name of the unit. This will be used to define the unit type and the init function.
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
 * @include add_unit_example.c
 * @param _name The name of the unit. This will be used to define the unit type and the init function.
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
 * @include add_conversion_example.c
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
 * @include add_conversion_example.c
 * @param _from See #CUDL_ADD_CONVERSION_FRACTION_FACTOR documentation.
 * @param _to See #CUDL_ADD_CONVERSION_FRACTION_FACTOR documentation.
 * @param _factor The multiplication facto to convert _from to _to.
 */
#define CUDL_ADD_CONVERSION_FACTOR(_from, _to, _factor) CUDL_ADD_CONVERSION_FRACTION_FACTOR(_from, _to, _factor, 1)

/**
 * @brief Macro to add an operation that has a left hand side and right side of the same type and does not change the
 * units. For example, adding 2 variables of volts together still results in volts, but multiplying would result in
 * square volts. To do the former, use #CUDL_ADD_NO_TRANSFORM_OP.
 * @include add_no_transform_op_example.c
 * @param _name The unit to add an op for. It is expected to be the same as the _name param used with CUDL_ADD_UNIT*.
 * @param _op_name The core name of function to add.
 * @param _op The op to use between the 2 values.
 */
#define CUDL_ADD_NO_TRANSFORM_OP(_name, _op_name, _op)                                                                 \
    static inline __CUDL_UT(_name)                                                                                     \
            __CUDL_L1STR(__CUDL_AP(_name), _op_name)(__CUDL_UT(_name) lhs, __CUDL_UT(_name) rhs) {                     \
        __CUDL_UT(_name) result;                                                                                       \
        result.value = CUDL_GET(lhs) _op CUDL_GET(rhs);                                                                \
        return result;                                                                                                 \
    }

/**
 * @brief Macro to add an operation that has a left hand side of the unit type and a unitless right side. This is a type
 * of operation that does not change the unit type. For example, doubling (or multiplying by 2) a voltage.
 * @include add_no_unit_op_example.c
 * @param _name The unit to add an op for. It is expected to be the same as the _name param used with CUDL_ADD_UNIT*.
 * @param _op_name The core name of function to add.
 * @param _op The op to use between the 2 values.
 * @param _type The underlying storage type to use.
 */
#define CUDL_ADD_NO_UNIT_OP(_name, _op_name, _op, _type)                                                               \
    static inline __CUDL_UT(_name) __CUDL_L1STR(__CUDL_AP(_name), _op_name)(__CUDL_UT(_name) lhs, _type rhs) {         \
        __CUDL_UT(_name) result;                                                                                       \
        result.value = CUDL_GET(lhs) _op rhs;                                                                          \
        return result;                                                                                                 \
    }

/**
 * @brief Macro to add a relational operation (==, !=, >, >=, <, <=). The result of these operations is always a
 * boolean value.
 * @include add_relational_op_example.c
 * @param _name The unit to add an op for. It is expected to be the same as the _name param used with CUDL_ADD_UNIT*.
 * @param _op_name The core name of function to add.
 * @param _op The op to use between the 2 values.
 */
#define CUDL_ADD_RELATIONAL_OP(_name, _op_name, _op)                                                                   \
    static inline bool __CUDL_L1STR(__CUDL_AP(_name), _op_name)(__CUDL_UT(_name) lhs, __CUDL_UT(_name) rhs) {          \
        return CUDL_GET(lhs) _op CUDL_GET(rhs);                                                                        \
    }

/**
 * @brief Add the bitwise not operator for a given unit.
 * @include add_bitwise_not_op_example.c
 * @param _name The unit to add an op for. It is expected to be the same as the _name param used with CUDL_ADD_UNIT*.
 * @param _op_name The core name of function to add.
 */
#define CUDL_ADD_BITWISE_NOT_OP(_name, _op_name)                                                                       \
    static inline __CUDL_UT(_name) __CUDL_L1STR(__CUDL_AP(_name), _op_name)(__CUDL_UT(_name) value) {                  \
        value.value = ~value.value;                                                                                    \
        return value;                                                                                                  \
    }

/**
 * @brief Helper macro to add operators that are supported by all types.
 * @param _name The unit to add an op for. It is expected to be the same as the _name param used with CUDL_ADD_UNIT*.
 * @param _type The underlying storage type to use.
 */
#define CUDL_ADD_COMMON_OPERATORS(_name, _type)                                                                        \
    CUDL_ADD_NO_TRANSFORM_OP(_name, _add, +)                                                                           \
    CUDL_ADD_NO_TRANSFORM_OP(_name, _sub, -)                                                                           \
    CUDL_ADD_NO_UNIT_OP(_name, _mul, *, _type)                                                                         \
    CUDL_ADD_NO_UNIT_OP(_name, _div, /, _type)                                                                         \
    CUDL_ADD_RELATIONAL_OP(_name, _eq, ==)                                                                             \
    CUDL_ADD_RELATIONAL_OP(_name, _ne, !=)                                                                             \
    CUDL_ADD_RELATIONAL_OP(_name, _gt, >)                                                                              \
    CUDL_ADD_RELATIONAL_OP(_name, _ge, >=)                                                                             \
    CUDL_ADD_RELATIONAL_OP(_name, _lt, <)                                                                              \
    CUDL_ADD_RELATIONAL_OP(_name, _le, <=)

/**
 * @brief Helper macro to add operators that are supported by integer types.
 * @param _name The unit to add an op for. It is expected to be the same as the _name param used with CUDL_ADD_UNIT*.
 * @param _type The underlying storage type to use.
 */
#define CUDL_ADD_INTEGER_OPERATORS(_name, _type)                                                                       \
    CUDL_ADD_COMMON_OPERATORS(_name, _type)                                                                            \
    CUDL_ADD_NO_UNIT_OP(_name, _mod, %, _type)                                                                         \
    CUDL_ADD_NO_UNIT_OP(_name, _and, &, _type)                                                                         \
    CUDL_ADD_NO_UNIT_OP(_name, _or, |, _type)                                                                          \
    CUDL_ADD_NO_UNIT_OP(_name, _xor, ^, _type)                                                                         \
    CUDL_ADD_NO_UNIT_OP(_name, _bsl, <<, _type)                                                                        \
    CUDL_ADD_NO_UNIT_OP(_name, _bsr, >>, _type)                                                                        \
    CUDL_ADD_BITWISE_NOT_OP(_name, _bnot)

#ifdef __cplusplus
}
#endif

#endif//CUDL_H
