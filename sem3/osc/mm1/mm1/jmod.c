#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

static int major_num;
static int busy;


static int cool_open(struct inode *inode, struct file *file)
{
	/* Check if we are already serving someone */
	if (busy) {
		return -EBUSY;
	}

	busy = 1;
	return 0;
}

static int cool_release (struct inode *inode, struct file *file)
{
	busy = 0;

	return 0;
}

static ssize_t cool_read (struct file *filp, char *buffer, size_t len, loff_t *offset)
{

	char str[12] = "hej med dig";
	int i;

	for (i = 0; i < len; i++) {
		put_user(str[i % 12], buffer++);
	}

	return i;
}

static struct file_operations file_ops = {
	.owner = THIS_MODULE,
	.read = cool_read,
	.open = cool_open,
	.release = cool_release
};

static int __init jmod_init(void) 
{
	printk(KERN_INFO "COOL_MODULE: Registering cooldev\n");
	
	major_num = register_chrdev(0, "cooldev", &file_ops);
	if (major_num < 0) {
		printk(KERN_ERR "COOL_MODULE: Could not register major\n");
		return 1;
	}

	printk(KERN_INFO "COOL_MODULE: Got major %d\n", major_num);

	return 0;
}


static void __exit jmod_exit(void) 
{
	printk(KERN_INFO "COOL_MODULE: Nou moe\n");
	unregister_chrdev(major_num, "cooldev");
}

module_init( jmod_init );
module_exit( jmod_exit );

