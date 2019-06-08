/*
 * start.c - writing a multi file kernel module.
 * It's the first file.
 */

#include <linux/kernel.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");

int init_module(void)
{
	printk(KERN_INFO "Whispering from a multi-file kernel module.\n");
	return 0;
}
