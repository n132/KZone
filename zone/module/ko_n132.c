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

MODULE_LICENSE("Dual BSD/GPL");
void * ptr_table[0x4000] = {};
void * drainer[0x1000] = {};
void hexdump(void * addr, size_t len);
int sprayProbe_p2s(void );
int sprayProbe_s2s(void );


void hexdump(void * addr, size_t len){
    int i;
    size_t more = (len%0x10) ? 1:0;
    printk("HexDump:\n");
    
    for(i = 0 ; i < (len/0x10)+ more; i++){
        printk("0x%016lx:\t0x%016lx\t0x%016lx\n",(unsigned long)(addr+i*0x10), *(unsigned long *)(addr+i*0x10), *(unsigned long *)(addr+i*0x10+8));
    }
}
static int _sprayProbe_p2s_probe(size_t order,size_t refill_size){
    int i;
    size_t *original = (size_t * )__get_free_pages(GFP_KERNEL,order);
    size_t refill_num = 0x20*0x1000*(1<<order)/refill_size; // 8 Times More than freed size
    free_pages((unsigned long )original,order);
    for(i  = 0 ;  i < refill_num ; i++){
        void * tmp =kmalloc(refill_size,GFP_KERNEL);
        memset(tmp,0x69,refill_size);
    }
    if(*original==0x6969696969696969){
        return 1;
    }
    else{
        return 0;
    }
}

int sprayProbe_p2s(void ){
    int i,k,j,x;
    size_t ct = 0;
    size_t slab_size[] = {0x8,0x10,0x20,0x40,0x60,0x80,0xc0,0x100,0x200,0x400,0x800,0x1000,0x2000};
    for(i = 0 ; i < 0x1000; i++){
        __get_free_pages(GFP_KERNEL,1);//Drain fragments
    }

    
    printk("[ UAF Size/Pages ] [\tRefill Objects Size / Bytes\t] [\t\tSuccess Rate\t]\n");
    for(k = 4 ; k < 0x5; k++)
    {
        for(j = 0; j < sizeof(slab_size) / sizeof(size_t)  ; j++ )
        {
            for(x = 0 ; x < 0x20000/slab_size[j]; x++)
                kmalloc(slab_size[j],GFP_KERNEL);//Drain fragments
    
            ct = 0 ; 
            for( i = 0 ; i < 0x10 ; i++){
                ct += _sprayProbe_p2s_probe(k,slab_size[j]);
            }
            printk("[\t%d\t] [\t\tkmalloc-%ld\t\t] [\t\t%ld/16\t\t]\n",k,slab_size[j],ct);
        }
    }
    return 0;
}

int yLay(void);
int yLay(void){
    /*
    0x600 page spraying has 80%+ succeress rate
    0x800 page spraying has 100% succeress rate
    */
   int i;
    char * targets;
    char * p1,*p2;
    char *victim;
    size_t flag2,flag1;
    flag1 = flag2 = 0;
    for(i = 0 ; i < 0x200 ;i++)
        __get_free_pages(GFP_KERNEL,0);

    victim = (char *)__get_free_pages(GFP_KERNEL,5); // Allocate a victim
    free_pages((unsigned long)victim,5);
    p1 = (char *)__get_free_pages(GFP_KERNEL,4);
    p2 = (char *)__get_free_pages(GFP_KERNEL,4);
    printk("%px %px %px\n",p1,p2,victim);
    if(abs(p1-p2)!=0x10000 || (p1!=victim && p2!=victim))
    {
        printk("[!] Die at first step\n");
        return 2;
    }
    free_pages((unsigned long)p1,4);
    for(i  = 0 ;  i < 0x4000 ; i++){
        targets = kmalloc(0x200,GFP_KERNEL);
        memset(targets,'\x11',0x200);
    }
    free_pages((unsigned long)p2,4);
    for(i = 0 ; i < 0x4000; i++){
        targets = kmalloc(0x100,GFP_KERNEL);
        memset(targets,'\xff',0x100);
        targets = kmalloc(0x100,GFP_KERNEL);
        memset(targets,'\xff',0x100);
    }
    for(i = 0 ; i < 0x20 ; i++){
        if(*(size_t *)(victim+0x1000*i)==0xffffffffffffffff)
            flag1 = 1;
        if(*(size_t *)(victim+0x1000*i)==0x1111111111111111)
            flag2 = 1;
    }
    if(flag1 == 1 && flag2 ==1)
    {
        printk("HIT\n");
        return 1;
    }
    return 0;
}
int xLay(size_t nr_page);
int xLay(size_t nr_page){
    int i;
    size_t * targets;
    size_t *a,*b,*c,*d;
    size_t probe1 = 0xffffffffffffffff;
    size_t probe2 = 0x1111111111111111;
    size_t flag1 =0;
    size_t flag2 =0;
    //Drain fragments
    for(i  = 0 ;  i < 0x800 ; i++)
        kmalloc(0x100,GFP_KERNEL);
    for(i  = 0 ;  i < 0x800 ; i++)
        kmalloc(0x200,GFP_KERNEL);
    a = (size_t *)__get_free_pages(GFP_KERNEL,3);
    b = (size_t *)__get_free_pages(GFP_KERNEL,3);
    c = (size_t *)__get_free_pages(GFP_KERNEL,3);
    d = (size_t *)__get_free_pages(GFP_KERNEL,3);
    for(i = 0 ; i < 0x200; i++)
        __get_free_pages(GFP_KERNEL,0);
    
    for(i = 0 ; i < nr_page*2; i++)
        ptr_table[i]=(size_t *)__get_free_pages(GFP_KERNEL,0);
    
    for(i = 0 ; i < nr_page ;i +=1)
        free_pages((unsigned long )ptr_table[i],0);
    
    free_pages((unsigned long )a,3);
    free_pages((unsigned long )b,3);

    for(i  = 0 ;  i < nr_page*0x1000/0x200*2 ; i++){
        targets = kmalloc(0x200,GFP_KERNEL);
        memset(targets,'\x11',0x200);
    }
    for(i = nr_page ; i < nr_page+nr_page ;i +=1)
        free_pages((unsigned long )ptr_table[i],0);
    free_pages((unsigned long )c,3);
    free_pages((unsigned long )d,3);


    for(i = 0 ;i < nr_page*0x1000/0x100*2 ; i++){
        targets = kmalloc(0x100,GFP_KERNEL);
        memset(targets,'\xff',0x100);
    }
    
    for(i = 0 ; i < nr_page*2 ; i++){
        if(*(size_t *)ptr_table[i]==probe1)
            flag1 = 1;
        if(*(size_t *)(ptr_table[i])==probe2)
            flag2 = 1;
        hexdump(ptr_table[i],0x10);
    }

    if(flag1 == 1 && flag2 ==1)
        return 1;
    return 0;
}
int holes(void);
int holes(void ){

    // Assuming we are targeting order-1
    int i;
    size_t nr_page = 0x40*4;
    size_t * targets;
    size_t *a,*b;
    // size_t probe1 = 0xffffffffffffffff;
    // size_t probe2 = 0x1111111111111111;
    // size_t flag1 =0;
    // size_t flag2 =0;
    // Drain fragments
    for(i  = 0 ;  i < 0x800 ; i++)
        kmalloc(0x100,GFP_KERNEL);
    for(i  = 0 ;  i < 0x800 ; i++)
        kmalloc(0x200,GFP_KERNEL);
    a = (size_t *)__get_free_pages(GFP_KERNEL,3);
    b = (size_t *)__get_free_pages(GFP_KERNEL,3);
    for(i = 0 ; i < 0x200; i++)
        __get_free_pages(GFP_KERNEL,0);
    // Do the work
    for(i = 0 ; i < nr_page; i++)
        ptr_table[i]=(size_t *)__get_free_pages(GFP_KERNEL,0);
    

    /*
        NYYY
    */
    for(i = 0 ; i < nr_page ; i++)
        if(i%4!=0)
            free_pages((unsigned long )ptr_table[i],0);
    
    free_pages((unsigned long )a,3);
    free_pages((unsigned long )b,3);

    for(i  = 0 ;  i < nr_page*0x1000/0x200*2; i++){
        targets = kmalloc(0x200,GFP_KERNEL);
        memset(targets,'\x22',0x200);
    }
    for(i = 0 ; i < nr_page ; i++)
        if(i%4==0)
            free_pages((unsigned long )ptr_table[i],0);
    for(i  = 0 ;  i < nr_page*0x1000/0x100*2 ; i++){
        targets = kmalloc(0x100,GFP_KERNEL);
        memset(targets,'\x11',0x100);
    }
    for(i = 0 ; i < nr_page ; i++)
        // if(i%4!=0)
            hexdump(ptr_table[i],0x10);


    return 0;
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
    switch(cmd) {
        case 0x13370000: // sanity check
            printk(KERN_INFO "CHECK CHECK\n");
            break;

        case 0x13370001: // oob read
            printk(KERN_INFO "OOB READ\n");

            if (copy_to_user(user_req.buf,user_req.addr, user_req.size)) 
                return -1;
        
            break;
        case 0x13370002: //oob write
            printk(KERN_INFO "OOB WRITE\n");

            if (copy_from_user(user_req.addr,user_req.buf, user_req.size)) 
                return -1;
            
            break;
        case 0x13370003: // UAF GFP_KERNEL
            printk(KERN_INFO "UAF GFP_KERNEL\n");
            res = (long int)kmalloc(user_req.size,GFP_KERNEL);
            kfree((void *)res);
            if(copy_to_user(*(void**)(arg+0x10),&res, 8))
                return -1;
            printk(KERN_INFO "UAF Pointer %px\n",(void *)res);
            break;
        case 0x13370004:
            // UAF GFP_KERNEL_ACCOUNT
            printk(KERN_INFO "UAF GFP_KERNEL_ACCOUNT\n");
            res = (long int)kmalloc(user_req.size,GFP_KERNEL_ACCOUNT);
            kfree((void *)res);
            if(copy_to_user(user_req.buf,&res, 8))
                return -1;
            printk(KERN_INFO "UAF Pointer %px\n",(void *)res);
            break;
        case 0x13370005:
            // KERNEL SPRAY
            printk(KERN_INFO "GFP_KERNEL SPRAY\n");
            res = (long int)kmalloc(user_req.size,GFP_KERNEL);
            printk("%px %px\n",(void *)res,user_req.addr);
            if(copy_from_user((void *)res,user_req.addr,user_req.size))
                return -1;
            break;
        case 0x13370006:
            // KERNEL_ACCOUNT SPRAY
            printk(KERN_INFO "GFP_KERNEL SPRAY\n");
            res = (long int)kmalloc(user_req.size,GFP_KERNEL_ACCOUNT);
            if(copy_from_user((void *)res,user_req.addr,user_req.size))
                return -1;
            break;
        case 0x13370007:
            rcu_barrier();
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
    holes();
	return misc_register(&librarymodule);
}
static void ko_n132_exit(void)
{
    misc_deregister(&librarymodule);
    printk("Bye Bye~\n");
}
module_init(ko_n132_init);
module_exit(ko_n132_exit);
