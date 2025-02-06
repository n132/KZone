#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/msg.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/list.h>
#include <linux/vmalloc.h>

MODULE_LICENSE("Dual BSD/GPL");
void hexdump(void * addr, size_t len);

void hexdump(void * addr, size_t len){
    int i;
    size_t more = (len%0x10) ? 1:0;
    printk("HexDump:\n");
    
    for(i = 0 ; i < (len/0x10)+ more; i++){
        printk("0x%016lx:\t0x%016lx\t0x%016lx\n",(unsigned long)(addr+i*0x10), *(unsigned long *)(addr+i*0x10), *(unsigned long *)(addr+i*0x10+8));
    }
}
struct req{
    void * addr;
    size_t size;
    void * buf;
};

static long int n132_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
    struct req user_req;
    long int res = 0 ; 
    if(copy_from_user(&user_req,(void *)arg,sizeof(struct req))){
        return -1;
    }
    switch(cmd) { // RIP control
        case 0x13371337:
            // <CODE>
            break;
        default:
            return -1;
    }
    return 0;

}

#define DEVICE_NAME "ko_n132"

static const struct file_operations n132_fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = n132_ioctl, 
};

static struct miscdevice librarymodule = {
    .minor      = 53,
    .name       = DEVICE_NAME,
    .fops       = &n132_fops,
    .mode	    = 0666,
};
static int __init ko_n132_init(void)
{   
	printk("Module Loaded\n");
    return misc_register(&librarymodule);
}
static void ko_n132_exit(void)
{
    misc_deregister(&librarymodule);
	printk("Module Removed\n");
}
module_init(ko_n132_init);
module_exit(ko_n132_exit);
