#ifndef RANDOM_SOURCE_H
#define RANDOM_SOURCE_H

typedef unsigned long long num_t;

typedef struct RandomSourceOperations
{
    struct RandomSource *(*destroy)(struct RandomSource *);
    double (*next)(struct RandomSource *);
} RandomSourceOperations;

typedef struct RandomSource
{
    struct RandomSourceOperations *ops;
    num_t linear_state;
    int random_fd;
} RandomSource;

#endif
