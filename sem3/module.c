#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

module_init(void)
{
	printk(KERN_INFO "COOL_MODULE: Hej med dig\n");
	return 0;
}

module_exit(void)
{
	printk(KERN_INFO "COOL_MODULE: Nou moe\n");
}
