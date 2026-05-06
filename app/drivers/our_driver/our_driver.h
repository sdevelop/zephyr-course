#ifndef ZEPHYR_DRIVERS_OUR_DRIVER_H_
#define ZEPHYR_DRIVERS_OUR_DRIVER_H_
#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int our_driver_update_led_toggle_counter(const struct device *dev, unsigned int added_value);

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_DRIVERS_OUR_DRIVER_H_ */