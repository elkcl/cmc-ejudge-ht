#ifndef MY_UTILITY_H
#define MY_UTILITY_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

void panic(char *err);
ssize_t read_all(int fd, void *buf_v, size_t size);

#endif
