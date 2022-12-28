#define DT_DRV_COMPAT microchip_mcp3201

#include <zephyr/drivers/spi.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

struct mcp3201_data
{
    uint16_t sample;
};

struct mcp3201_config
{
    struct spi_dt_spec spi;
};

int adc_read(const struct device *dev, uint16_t *val)
{
    const struct mcp3201_config *cfg = dev->config;

    uint8_t sample[2];
    struct spi_buf rx_buf = {
        .buf = &val,
        .len = 2,
    };

    struct spi_buf_set rx_bufs = {
        .buffers = &rx_buf,
        .count = 1,
    };

    int rc = spi_read_dt(&cfg->spi, &rx_bufs);
    return rc;
}

int mcp3201_init()
{
    printk("Hello World\n");
    return 0;
}

extern int mcp3201_sample_fetch(const struct device *dev, enum sensor_channel chan);
extern int mcp3201_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val);

int mcp3201_sample_fetch(const struct device *dev, enum sensor_channel chan)
{
    printk("ADC was Sampled\n");
    struct mcp3201_data *data = dev->data;
    return adc_read(dev, &data->sample);
}

int mcp3201_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val)
{
    const struct mcp3201_data *data = dev->data;
    uint16_t sample = data->sample;

    val->val1 = sample;
    return 0;
}

static const struct sensor_driver_api mcp3201_api_funcs = {
    .sample_fetch = mcp3201_sample_fetch,
    .channel_get = mcp3201_channel_get,
};

#define MCP3201_DEFINE(inst)                                                       \
    static struct mcp3201_data mcp3201_data_##inst;                                \
    static const struct mcp3201_config mcp3201_confit_##inst = {                   \
        .i2c = I2C_DT_SPEC_INST_GET(inst),                                         \
    };                                                                             \
    SENSOR_DEVICE_DT_INST_DEFINE(inst, mcp3201_init, NULL, &mcp3201_data_##inst,   \ 
                                &mcp3201_config_##inst,                            \
                                 POST_KERNEL,                                      \
                                 CONFIG_SENSOR_INIT_PRIORITY, &mcp3201_api_funcs); \
                                                                                   \
    DT_INST_FOREACH_STATUS_OKAY(MCP3201_DEFINE)
