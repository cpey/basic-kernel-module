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
#include "defs.h"

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
    uint32_t request[REQUEST_LENGTH];
    uint64_t time_delta;
    uint64_t start_time;

    memset(request, 0, REQUEST_LENGTH * sizeof(int));

    CHECK_ERR(fd = open(SIMPLE_MODULE_DEVICE, O_RDWR));
    CHECK_ERR(ioctl(fd, SIMPLE_MODULE_FN2, request));
    printf("Received: 0x%X\n",  request[REQUEST_LENGTH - 1]);
    close(fd);
}
