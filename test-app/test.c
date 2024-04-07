// SPDX-License-Identifier: MIT
/*
 * (C) 2024 Carles Pey <cpey@pm.me>
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define SIMPLE_MODULE_FN1   _IOW(0x33, 0, int32_t *)

//#define DEBUGFS

#ifdef DEBUGFS
#define CHIPSEC_DRIVER_PATH "/sys/kernel/debug/simple_module"
#else
#define CHIPSEC_DRIVER_PATH "/dev/simple_module"
#endif

#define REQUEST_LENGTH      9

#define CHECK_ERR(expr) {  \
    int check_val = expr; \
    if (check_val == -1) { \
        char err[256]; \
        sprintf(err, "Error in line %d", __LINE__); \
        perror(err); \
        clear_and_exit(); \
    } \
}

#define clear_and_exit() { \
    if (fd) { \
        close(fd); \
    }\
    return -1; }

int main() {
    int fd;
    int request[REQUEST_LENGTH];
    uint64_t time_delta;
    uint64_t start_time;

    memset(request, 0, REQUEST_LENGTH * sizeof(int));

    CHECK_ERR(fd = open(CHIPSEC_DRIVER_PATH, O_RDWR));
    CHECK_ERR(ioctl(fd, SIMPLE_MODULE_FN1, request));
    close(fd);
}
