// SPDX-License-Identifier: MIT
/*
 * (C) 2024 Carles Pey <cpey@pm.me>
 */
#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/miscdevice.h>
#include "defs.h"

MODULE_LICENSE("GPL");

#ifdef DEBUGFS
struct dentry *file;
#endif

static int device_open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "[%s] device_open", KBUILD_MODNAME);
    return 0;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch (cmd) {
    case SIMPLE_MODULE_FN1:
        printk(KERN_INFO "[%s] CALL_FN1\n", KBUILD_MODNAME);
        break;
    case SIMPLE_MODULE_FN2:
        printk(KERN_INFO "[%s] CALL_FN2\n", KBUILD_MODNAME);
        uint32_t ptr[REQUEST_LENGTH];

        if (copy_from_user((void*)ptr, (void*)arg, (sizeof(*ptr) * REQUEST_LENGTH)) > 0)
            return -EFAULT; 

        ptr[REQUEST_LENGTH - 1] = 0x5A5A5A5A;
        if (copy_to_user((void*)arg, (void*)ptr, (sizeof(*ptr) * REQUEST_LENGTH)) > 0)
            return -EFAULT; 
        break;
    default:
        printk(KERN_INFO "[%s] Invalid ioctl command\n", KBUILD_MODNAME);
        return -EINVAL;
    }
    return 0;
}

static int device_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "[%s] Release", KBUILD_MODNAME);
    return 0;
}

static int device_flush(struct file *file, void *unknown) {
    printk(KERN_INFO "[%s] Flush", KBUILD_MODNAME);
    return 0;
}

static const struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl,
    .flush = device_flush,
};

#ifndef DEBUGFS
static struct miscdevice mod_misc_dev = {
    .name = KBUILD_MODNAME,
    .minor = MISC_DYNAMIC_MINOR,
    .fops = &my_fops,
};
#endif

static int __init simple_module_init(void)
{
    printk(KERN_INFO "[%s] Loaded module\n", KBUILD_MODNAME);
#ifdef DEBUGFS
    file = debugfs_create_file(KBUILD_MODNAME, 0644, NULL, NULL, &my_fops);
    return 0;
#else
    return misc_register(&mod_misc_dev);
#endif
}

static void __exit simple_module_exit(void)
{
#ifdef DEBUGFS
    debugfs_remove(file);
#else
    misc_deregister(&mod_misc_dev);
#endif
    printk(KERN_INFO "[%s] Unloaded module\n", KBUILD_MODNAME);
}

module_init(simple_module_init);
module_exit(simple_module_exit);
