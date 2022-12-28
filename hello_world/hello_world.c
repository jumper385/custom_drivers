#include <device.h>

void init()
{
    printk("Initializing Hello World\n");
}

void greet()
{
    printk("Hell0 World");
}

DEVICE_DEFINE(hpma115s0, DT_INST_LABEL(0),
              init, NULL,
              NULL, NULL, POST_KERNEL,
              CONFIG_SENSOR_INIT_PRIORITY, NULL);