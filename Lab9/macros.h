#ifndef MACROS_H
#define MACROS_H

#define MAX (x, y) int result = 0; \
if (x >= y){            \
    result = x;         \
} else {                \
    result = y;         \
}                       \
return result;          \

#define MIN(x, y) int result = 0;  \
if(x <= y) {            \
    result = x;         \
} else {                \
    result = y;         \
}                       \
return result;          \

#define ABS(x) \
if (x < 0){             \
    x = x * -1;         \
    return x;           \
}                       \
return x;               \

#define RANGE(curr, min, max)

#define RANGE_DESC(curr, max, min)

#define SET(ary, start, count, value)

#endif /* MACROS_H */