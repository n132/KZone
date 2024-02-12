#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/msg.h>
MODULE_LICENSE("Dual BSD/GPL");
static int ko_n132_init(void)
{
    struct msg_msg p;
    printk("n132>\n%d\n",sizeof(p));
    return 0;
}
static void ko_n132_exit(void)
{
    printk("Bye Bye~\n");
}
module_init(ko_n132_init);
module_exit(ko_n132_exit);