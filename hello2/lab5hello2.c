#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>

#include <lab5hello1.h>

MODULE_AUTHOR("Vanya Braslavets");
MODULE_DESCRIPTION("Lab 4 module");
MODULE_LICENSE("Dual BSD/GPL");


// https://tldp.org/LDP/lkmpg/2.6/html/x323.html
static uint amount = 1;
module_param(amount, uint, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(amount, "Amount of times to print a string. Recommended value: 1..=5. Allowed value: 0..=10");


static int __init lab5hello2_init(void)
{
    uint i;

    if(false) {}
    else if(amount == 0 || (6 <= amount && amount <= 10)) {
        printk(KERN_EMERG "WARNING: Recommended value for `amount` is 1..=5. Received value: %d\n", amount);
    }
    else if(amount > 10) {
        printk(KERN_EMERG "ERROR: Recommended value for `amount` is 1..=5. Received value: %d\n", amount);
        return -EINVAL;
    }

    for(i = 0; i < amount; i++) {
        print_hello();
    }

    return 0;
}

static void __exit lab5hello2_exit(void)
{
}

module_init(lab5hello2_init);
module_exit(lab5hello2_exit);
