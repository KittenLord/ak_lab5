#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/export.h>
#include <linux/ktime.h>
#include <linux/slab.h>

#define LAB5_MESSAGE "Hello, World!\n"

MODULE_AUTHOR("Vanya Braslavets");
MODULE_DESCRIPTION("Lab 5 main module");
MODULE_LICENSE("Dual BSD/GPL");


// https://docs.kernel.org/core-api/list.html
typedef struct {
    ktime_t timeStart;
    ktime_t timeEnd;

    struct list_head node;
} TimestampNode;

typedef struct {
    struct list_head stamps;
} Timestamps;

static Timestamps timestamps;


void print_hello(void) {
    ktime_t timeStart, timeEnd;
    TimestampNode *node;

    timeStart = ktime_get();
    pr_info(LAB5_MESSAGE);
    timeEnd = ktime_get();

    node = kmalloc(sizeof(TimestampNode), GFP_KERNEL);
    if(!node) return;

    *node = (TimestampNode){
        .timeStart = timeStart,
        .timeEnd = timeEnd,
    };

    list_add_tail(&node->node, &timestamps.stamps);
}
EXPORT_SYMBOL(print_hello);

static int __init lab5hello1_init(void)
{
    timestamps = (Timestamps){
        .stamps = LIST_HEAD_INIT(timestamps.stamps),
    };

    return 0;
}

static void __exit lab5hello1_exit(void)
{
    int i = 0;
    TimestampNode *e, *n;

    list_for_each_entry_safe(e, n, &timestamps.stamps, node) {
        pr_info("Stamp %lld took %lldns (%lld -> %lld)\n", e->timeEnd - e->timeStart, e->timeStart, e->timeEnd);

        list_del(&e->node);
        kfree(e);
    }
}

module_init(lab5hello1_init);
module_exit(lab5hello1_exit);
