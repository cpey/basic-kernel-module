#ifndef _DEFS_H
#define _DEFS_H

//#define DEBUGFS

#define SIMPLE_MODULE_FN1   _IOW('S', 0, uint32_t *)
#define SIMPLE_MODULE_FN2   _IOWR('S', 1, uint32_t *)

#define REQUEST_LENGTH      9

#ifdef DEBUGFS
#define CHIPSEC_DRIVER_PATH "/sys/kernel/debug/simple_module"
#else
#define CHIPSEC_DRIVER_PATH "/dev/simple_module"
#endif

#endif
