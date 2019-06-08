/*
 *  hello-4.c - Demonstates module documentation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#define DRIVER_AUTHOR "Shaswata Das <shaswata56@gmail.com>"
#define DRIVER_DESC   "A sample driver for learning"

static int __init init_hello_4(void)
{
	printk(KERN_INFO "Hello World 4\n");
	return 0;
}

static void __exit cleanup_hello_4(void)
{
	printk(KERN_INFO "Goodbye World 4\n");
}

module_init(init_hello_4);
module_exit(cleanup_hello_4);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("test_dev");
