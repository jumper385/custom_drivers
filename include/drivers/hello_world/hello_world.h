#ifndef DRIVERS_HELLO_WORLD_H_
#define DRIVERS_HELLO_WORLD_H_

struct hello_world_driver_api
{
    void (*greet)();
};

int init();
void greet();

#endif