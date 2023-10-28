#include "my_utility.h"

void
panic(char *err)
{
    if (errno) {
        fprintf(stderr, "Error: %s\nLast errno: %s\n", err, strerror(errno));
    } else {
        fprintf(stderr, "Error: %s\n", err);
    }
    exit(1);
}

ssize_t
read_all(int fd, void *buf_v, size_t size)
{
    char *buf = buf_v;
    ssize_t remaining = size;
    while (remaining > 0) {
        ssize_t cnt_read = 0;
        do {
            errno = 0;
            cnt_read = read(fd, buf, remaining);
        } while (cnt_read == -1 && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR));
        if (cnt_read == -1) {
            panic("reading from file failed");
        }
        if (cnt_read == 0) {
            break;
        }
        remaining -= cnt_read;
        buf += cnt_read;
    }
    return size - remaining;
}
