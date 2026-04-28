#include <zephyr/sys/printk.h>

void board_early_init_hook(void)
{
    printk("[%s] %s Board initialized\n", __func__, CONFIG_BOARD);
}
