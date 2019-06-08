/*
 *  hello-5.c - Demonstrate command line argument passing to a module.
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shaswata Das");

static short int myshort = 1;
static int myint = 1;
static long int mylong = 1;
static char *mystring = "stringy";
static int myIntArray[2] = { -1, -1 };
static int arr_argc = 0;

/*
 * module_param(foo, int, 00)
 * foo - parameter name
 * int - it's data type
 * 00  - permission bits,
 * for exposing param in sysfs (if non-zero) at a later stage.
 */

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mysting, "A character string");

/*
 * module_param_array(foo, int, &arg_num, 0000);
 * foo - array's name
 * int - data type of the array
 * &argc_num - pointer to the variable that will store the number
 * of elements of the array
 * 0000 - permission bits
 */

module_param_array(myIntArray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myIntArray, "An array of integers");

static int __init hello_5_init(void)
{
	int i;
	printk(KERN_INFO "Hello World 5!\n==============\n");
	printk(KERN_INFO "myshort is a short integer: %hd\n", myshort);
	printk(KERN_INFO "myint is an integer: %d\n", myint);
	printk(KERN_INFO "mylong is a long integer: %ld\n", mylong);
	printk(KERN_INFO "mystring is a string: %s\n", mystring);
	for(i = 0; i < (sizeof myIntArray / sizeof(int)); i++)
	{
		printk(KERN_INFO "myIntArray[%d] = %d\n", i, myIntArray[i]);
	}
	printk(KERN_INFO "got %d arguments of myIntArray.\n", arr_argc);
	return 0;
}

static void __exit hello_5_exit(void)
{
	printk(KERN_INFO "Exiting Kernel module 5\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);
