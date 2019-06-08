/*
 *  Demonstrating I/O with kernel using /proc/myproc .
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h> /* for sequential read, write purpose */
#include <linux/stat.h>
#include <linux/utsname.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shaswata Das");

static const char *filename = "myproc";

static int show_msg(struct seq_file *m, void *v)
{
	seq_printf(m, 
		   "The kernel version is: %s\n", utsname()->release);
	printk(KERN_INFO "Entered into show_msg().\n");
	return 0;
}

static int open_file(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Entered into open_file().\n");
	return single_open(file, show_msg, NULL);
}

static const struct file_operations fops = {
	.llseek = seq_lseek,
	.open = open_file,
	.owner = THIS_MODULE,
	.read = seq_read,
	.release = single_release
};

static int initmod(void)
{
	proc_create(filename, 0, NULL, &fops);
	printk(KERN_INFO "Module initialized...\nTry to 'cat /proc/myproc'\n");
	return 0;
}

static void exitmod(void)
{
	remove_proc_entry(filename, NULL);
	printk(KERN_INFO "Removing Kernel module: myproc\n");
}

module_init(initmod);
module_exit(exitmod);
