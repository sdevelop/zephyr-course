#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

//const char dev_name[] = "our_driver";

static int cmd_fetch_handler(const struct shell *shell, int argc, char **argv) {

    const char *dev_name = argv[1];
    const struct device *dev = shell_device_get_binding(dev_name);
    if (!dev) {
        shell_error(shell, "Could not find device %s", dev_name);
        return -ENOENT;
    }
    //shell_info(shell, "This command would call sensor_sample_fetch in %s driver", dev_name);
    sensor_sample_fetch(dev);

    return 0;
}

static int cmd_read_handler(const struct shell *shell, int argc, char **argv) {

    const char *dev_name = argv[1];
    const struct device *dev = shell_device_get_binding(dev_name);
    if (!dev) {
        shell_error(shell, "Could not find device %s", dev_name);
        return -ENOENT;
    }
    struct sensor_value val = {0};
    //shell_info(shell, "This command would call sensor_channel_get in %s driver", dev_name);
    sensor_channel_get(dev, SENSOR_CHAN_ALL, &val);
    shell_info(shell, "Value read from sensor: %d.%06d", val.val1, val.val2);

    return 0;
}

static int cmd_info_handler(const struct shell *shell, int argc, char **argv) {

    const char *dev_name = argv[1];
    const struct device *dev = shell_device_get_binding(dev_name);
    if (!dev) {
        shell_error(shell, "Could not find device %s", dev_name);
        return -ENOENT;
    }
    //shell_print(shell, "This command would print information about %s driver", dev_name);
    shell_info(shell, "Device name: %s, Ready state: %s", dev->name, device_is_ready(dev) ? "ready" : "not ready");

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmds,
    SHELL_CMD_ARG(fetch, NULL, "Calls sensor_sample_fetch in our driver", cmd_fetch_handler, 2, 0),
    SHELL_CMD_ARG(read, NULL, "Calls sensor_channel_get in our driver", cmd_read_handler, 2, 0),
    SHELL_CMD_ARG(info, NULL, "Print information about our driver", cmd_info_handler, 2, 0),
    SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(sensor, &our_driver_subcmds, "Commands for our driver", NULL);
