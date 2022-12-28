#include <device.h>

void init()
{
    printk("Initializing Hello World\n");
}

void greet()
{
    printk("Hell0 World\n");
}

DEVICE_DEFINE(helloworld, "HELLO_WORLD_DRIVER",
              init, NULL,
              NULL, NULL, POST_KERNEL,
              CONFIG_SENSOR_INIT_PRIORITY, &((struct hello_world_driver_api){.greet = greet}));