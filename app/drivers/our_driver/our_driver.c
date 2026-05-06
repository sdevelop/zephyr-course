#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

#define LED_NODE DT_ALIAS(app_led)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static int handle_led_state(bool state) {

    LOG_INF("Turning %s LED", state ? "ON" : "OFF");
    if (gpio_pin_set_dt(&led, state) < 0) {
        LOG_ERR("Failed to set LED state");
        return -EIO;
    }
    return 0;
}

static int channel_get_my_impl(const struct device *dev,
                               enum sensor_channel chan,
                               struct sensor_value *val) {

    handle_led_state(false); /* Turning off LED */
    LOG_INF("%s - led OFF", __func__);
    return 0;
}

static int sample_fetch_my_impl(const struct device *dev,
                                enum sensor_channel chan) {

    handle_led_state(true); /* Turning on LED */
    LOG_INF("%s - led ON", __func__);
    return 0;
}

// Init fnction for our driver
static int our_driver_init(const struct device *dev) {
    if (!gpio_is_ready_dt(&led)) {
        LOG_ERR("GPIO is not ready");
        return -ENODEV;
    }
    /* Configure LED on at the beginning */
    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) {
        LOG_ERR("Failed to configure GPIO");
        return -EINVAL;
    }
    LOG_INF("Device %s initialized, LED ON", dev->name);
    return 0;
}

static DEVICE_API(sensor, our_driver_api) = {
    .channel_get = channel_get_my_impl,
    .sample_fetch = sample_fetch_my_impl,
};

#define DEV_INST(inst) DEVICE_DT_INST_DEFINE(inst, our_driver_init, NULL, NULL, NULL, POST_KERNEL, 80, &our_driver_api);
DT_INST_FOREACH_STATUS_OKAY(DEV_INST);
