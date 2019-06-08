/*
 * stop.c - last file of the multi filed module.
 * from start.c.
 */

#include <linux/kernel.h>
#include <linux/module.h>

void cleanup_module(void)
{
	printk(KERN_INFO "Life of a kernel module is so short...\n");
}
