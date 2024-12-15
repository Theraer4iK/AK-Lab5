#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello2 Module - Uses print_hello()");
MODULE_AUTHOR("sorbat");

static int count = 1;
module_param(count, int, 0444);
MODULE_PARM_DESC(count, "Number of times to print hello");

static int __init hello2_init(void) {
    int i;

    pr_info("Hello2 Module: Initialization\n");

    if (count < 1) {
        pr_warn("Hello2: Warning! Parameter 'count' is less than 1\n");
        count = 1;
    } else if (count > 10) {
        pr_err("Hello2: Error! Parameter 'count' is too large\n");
        return -EINVAL;
    }

    for (i = 0; i < count; i++) {
        print_hello();
    }

    return 0;
}

static void __exit hello2_exit(void) {
    pr_info("Hello2 Module: Cleanup\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
