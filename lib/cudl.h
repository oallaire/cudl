#ifndef CUDL_H
#define CUDL_H

#ifdef __cplusplus
extern "C"
{
#endif

#define __CUDLE_UT(_name) _name##_t // NOLINT(bugprone-reserved-identifier)
#define __CUDLE_NOP(_x) _x // NOLINT(bugprone-reserved-identifier)
#define __CUDLE_FACTOR(_factor) (_x // NOLINT(bugprone-reserved-identifier)

#define CUDL_ADD_UNIT_WITH_OP(_name, _type, _op)              \
typedef struct _name##_s { _type value; } __CUDLE_UT(_name);  \
static inline __CUDLE_UT(_name) _name(_type input_value) {    \
    __CUDLE_UT(_name) ct;                                     \
    ct.value = _op(input_value);                              \
    return ct;                                                \
}

#define CUDL_ADD_UNIT(_name, _type) CUDL_ADD_UNIT_WITH_OP(_name, _type, __CUDLE_NOP)

#define CUDL_GET(_value) (_value).value

#define CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR(_from, _to, _explicative, _n, _d)       \
static inline __CUDLE_UT(_to) _explicative##_to(__CUDLE_UT(_from) from_value) {              \
    __CUDLE_UT(_to) to_value;                                                                \
    to_value.value = (from_value.value * _n) / _d;                                           \
    return to_value;                                                                         \
}

#define CUDL_ADD_CONVERSION_FRACTION_FACTOR(_from, __to, _n, _d) \
CUDL_ADD_EXPLICIT_CONVERSION_FRACTION_FACTOR(_from, __to, from##_from##_to, _n, _d)

#define CUDL_ADD_CONVERSION_FACTOR(_from, _to, _factor) CUDL_ADD_CONVERSION_FRACTION_FACTOR(_from, _to, _factor, 1)

#ifdef __cplusplus
}
#endif

#endif //CUDL_H
