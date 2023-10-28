#include "random_source.h"
#include "my_utility.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

enum
{
    ARGC = 4,
    TYPE_ARG = 1,
    COUNT_ARG = 2,
    PARAM_ARG = 3,
    MIN_COUNT = 0,
    MAX_COUNT = 100000
};

int
main(int argc, char **argv)
{
    if (argc != ARGC || argv == NULL || argv[TYPE_ARG] == NULL || argv[COUNT_ARG] == NULL) {
        panic("incorrect argument format");
    }
    void *handle = dlopen(NULL, RTLD_LAZY);
    if (handle == NULL) {
        panic(dlerror());
    }
    char *factory_name;
    if (asprintf(&factory_name, "random_%s_factory", argv[TYPE_ARG]) == -1) {
        panic("couldn't allocate memory");
    }
    RandomSource *(*random_factory)(const char *) = dlsym(handle, factory_name);
    if (random_factory == NULL) {
        panic(dlerror());
    }
    RandomSource *gen = random_factory(argv[PARAM_ARG]);
    char *eptr = NULL;
    errno = 0;
    long count = strtol(argv[COUNT_ARG], &eptr, 0);
    if (errno || *eptr || eptr == argv[COUNT_ARG] || count < MIN_COUNT || count > MAX_COUNT) {
        panic("incorrect count format");
    }
    while (count--) {
        printf("%.10g\n", gen->ops->next(gen));
    }
    gen->ops->destroy(gen);
    free(factory_name);
    if (dlclose(handle) != 0) {
        panic(dlerror());
    }
}
