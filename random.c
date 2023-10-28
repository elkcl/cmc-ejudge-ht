#include "random_source.h"
#include "my_utility.h"
#include <limits.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

RandomSource *
random_destroy(RandomSource *src)
{
    if (src == NULL) {
        return NULL;
    }
    if (src->ops != NULL) {
        free(src->ops);
    }
    if (close(src->random_fd) == -1) {
        free(src);
        panic("couldn't close /dev/urandom");
        return NULL;
    }
    free(src);
    return NULL;
}

double
random_next(const RandomSource *src)
{
    num_t curr;
    if (read_all(src->random_fd, &curr, sizeof(curr)) != sizeof(curr)) {
        panic("couldn't retrieve random number from the system");
    }
    double curr_d = curr;
    double denom_d = ULLONG_MAX;
    ++denom_d;
    return curr_d / denom_d;
}

RandomSource *
random_random_factory(const char *params)
{
    RandomSource *ans = calloc(1, sizeof(*ans));
    ans->ops = calloc(1, sizeof(*ans->ops));
    ans->ops->destroy = random_destroy;
    ans->ops->next = (double (*)(RandomSource *)) random_next;
    ans->random_fd = open("/dev/urandom", O_RDONLY);
    if (ans->random_fd == -1) {
        panic("couldn't open /dev/urandom");
    }
    return ans;
}
