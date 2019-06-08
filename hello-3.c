/*
 * 	hello-3.c - Illustrating the __init, __initdata and __exit macros.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int hello3_data __initdata = 3;

static int __init hello_3_init(void)
{
	printk(KERN_INFO "Hello World %d!!!\n", hello3_data);
	return 0;
}

static void __exit hello_3_exit(void)
{
	printk(KERN_INFO "Goodbye World 3!!!\n");
}

module_init(hello_3_init);
module_exit(hello_3_exit);
