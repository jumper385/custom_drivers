#include "hello_world.h"
#include <zephyr/device.h>
#include <zephyr/types.h>
#include <zephyr/sys/printk.h>

static int init()
{
    printk("Initializing Hello World\n");
    return 0;
}

static void greet(const struct device *dev)
{
    printk("Hello World from %s\n", dev->name);
}

DEVICE_DEFINE(hello_world, "HELLO_WORLD_DRIVER",
              init, NULL,
              NULL, NULL, POST_KERNEL,
              CONFIG_SENSOR_INIT_PRIORITY, &((struct hello_world_driver_api){.greet = greet}));