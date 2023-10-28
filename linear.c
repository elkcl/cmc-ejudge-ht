#include "random_source.h"
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>

enum
{
    SEED_DEFAULT = (num_t) 1234,
    MULTIPLIER = (num_t) 1103515245,
    INCREMENT = (num_t) 12345,
    MOD_MASK = (num_t) 0x7FFFFFFF,
    UPPER_BOUND = (num_t) 1ull << 31
};

RandomSource *
linear_destroy(RandomSource *src)
{
    if (src == NULL) {
        return NULL;
    }
    if (src->ops != NULL) {
        free(src->ops);
    }
    free(src);
    return NULL;
}

double
linear_next(RandomSource *src)
{
    src->linear_state *= MULTIPLIER;
    src->linear_state += INCREMENT;
    src->linear_state &= MOD_MASK;
    return (double) src->linear_state / UPPER_BOUND;
}

RandomSource *
random_linear_factory(const char *params)
{
    num_t seed = SEED_DEFAULT;
    if (params != NULL) {
        char *eptr = NULL;
        errno = 0;
        seed = strtoull(params, &eptr, 0);
        if (errno || *eptr || eptr == params) {
            seed = SEED_DEFAULT;
        }
    }
    RandomSource *ans = calloc(1, sizeof(*ans));
    ans->linear_state = seed & MOD_MASK;
    ans->ops = calloc(1, sizeof(*ans->ops));
    ans->ops->destroy = linear_destroy;
    ans->ops->next = linear_next;
    return ans;
}
