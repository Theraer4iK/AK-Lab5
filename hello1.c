#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello1 Module - Exports print_hello()");
MODULE_AUTHOR("sorbat");

static LIST_HEAD(time_list);

void print_hello(void) {
    struct print_time *entry;

    entry = kmalloc(sizeof(*entry), GFP_KERNEL);
    if (!entry) {
        pr_err("Hello1: Memory allocation failed\n");
        return;
    }

    entry->start = ktime_get();
    pr_info("Hello1: Hello, world!\n");
    entry->end = ktime_get();

    list_add_tail(&entry->list, &time_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void) {
    pr_info("Hello1 Module: Initialization\n");
    return 0;
}

static void __exit hello1_exit(void) {
    struct print_time *entry, *tmp;

    pr_info("Hello1 Module: Cleanup\n");

    list_for_each_entry_safe(entry, tmp, &time_list, list) {
        pr_info("Hello1: Execution time: %lld ns\n",
                ktime_to_ns(entry->end) - ktime_to_ns(entry->start));
        list_del(&entry->list);
        kfree(entry);
    }
}

module_init(hello1_init);
module_exit(hello1_exit);
