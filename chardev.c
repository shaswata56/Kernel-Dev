/*
 *  chardev.c: creates a read-only char device that says how many times
 *  we've read from the dev file.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	//for put_user
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shaswata Das");

/*
 * Prototypes - this would normally go in a .h file
 */

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 80

static int major, dev_open = 0;
static char msg[BUF_LEN], *msg_ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

int init_module(void)
{
	major = register_chrdev(0, DEVICE_NAME, &fops);

	if(major < 0) {
		printk(KERN_ALERT 
		       "Registering char device failed with %d\n", major);
		return major;
	}

	printk(KERN_INFO "I was assigned major number %d. To talk to\n", major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");

	return SUCCESS;
}

void cleanup_module(void)
{
	unregister_chrdev(major, DEVICE_NAME);
	printk(KERN_INFO "Removed /dev/chardev \n");
}

/*
 *  Called when a process tries to open the device file, like
 *  "cat /dev/chardev"
 */

static int device_open(struct inode *inode, struct file *file)
{
	static int counter = 0;

	if(dev_open) {
		return -EBUSY;
	}

	dev_open++;

	sprintf(msg, "You've opened the device %d times!!!\n", counter++);
	msg_ptr = msg;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

/*
 *  Called when a process closes the device file.
 */

static int device_release(struct inode *inode, struct file *file)
{
	dev_open--;

	module_put(THIS_MODULE);

	return SUCCESS;
}

static ssize_t device_read(struct file *filp, char *buff,
			   size_t length, loff_t *offset)
{
	int bytes_read = 0;	// number of bytes written to the buffer

	if(*msg_ptr == 0)	// if we're at the end of the message,
		return 0;	// by returning 0, we signify EOF

	while(length && *msg_ptr) {
		// putting the data into the buffer
		
		put_user(*(msg_ptr++), buff++);

		length--;
		bytes_read++;
	}

	return bytes_read;
}

static ssize_t device_write(struct file *filp, const char *buff,
			    size_t len, loff_t *off)
{
	printk(KERN_ALERT "Sorry, this operation is not supported!\n");
	return -EINVAL;
}
