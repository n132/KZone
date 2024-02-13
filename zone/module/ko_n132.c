#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/msg.h>
#include <linux/slab.h>
MODULE_LICENSE("Dual BSD/GPL");


static int ko_n132_init(void)
{
    int i = 0 ;
    for(i = 0 ; i< 0x100 ; i++){
        size_t *p = kmalloc(0x1000,GFP_KERNEL);
        printk("%p\n",p);
    }
    return 0;
}
static void ko_n132_exit(void)
{
    printk("Bye Bye~\n");
}
module_init(ko_n132_init);
module_exit(ko_n132_exit);
