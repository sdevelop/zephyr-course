#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <our_driver.h>

#if defined(CONFIG_LED_SUBSYSTEM)
#define SLEEP_TIME_MS CONFIG_APP_HEARTBEAT_PERIOD_MS
#else
#define SLEEP_TIME_MS 500
#endif

/* The devicetree node identifier for the "app_led" alias. */
#define LED_NODE DT_ALIAS(app_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

const struct device *dev = DEVICE_DT_GET_ANY(our_driver);

int main(void)
{
    bool led_state = true;

    if (!device_is_ready(dev)) {
        LOG_ERR("Our driver device is not ready");
        return -ENODEV;
    }

    LOG_INF("toggle sleep %d", SLEEP_TIME_MS);
    k_msleep(3000);
    while (1) {
        our_driver_update_led_toggle_counter(dev, 1);
        sensor_sample_fetch(dev);
        k_msleep(SLEEP_TIME_MS);
        sensor_channel_get(dev, SENSOR_CHAN_ALL, NULL);
        k_msleep(5*SLEEP_TIME_MS);
    }

#if 0
    if (!gpio_is_ready_dt(&led)) return -ENODEV;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    LOG_INF("BOARD: %s\n", CONFIG_BOARD);
    LOG_INF("LED_SUBSYSTEM: %s, SLEEP_TIME_MS: %d ms",
        IS_ENABLED(CONFIG_LED_SUBSYSTEM) ? "enabled" : "disabled", SLEEP_TIME_MS);

    while (1) {
        if (gpio_pin_toggle_dt(&led) < 0) return 0;

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(SLEEP_TIME_MS);
    }
#endif
    return 0;
}
