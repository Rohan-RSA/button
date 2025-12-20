#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "button.h"

// #define SW0_NODE	DT_ALIAS(sw0)

// static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static struct gpio_dt_spec led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led0), gpios, {0});

static const struct gpio_dt_spec input_1 = GPIO_DT_SPEC_GET(DT_ALIAS(input1), gpios);

static const struct gpio_dt_spec switch_1 = GPIO_DT_SPEC_GET(DT_ALIAS(switch1), gpios);

static struct gpio_callback button_cb_data;

static button_event_handler_t user_cb;

static void cooldown_expired(struct k_work *work)
{
    ARG_UNUSED(work);

    int val = gpio_pin_get_dt(&input_1);
    enum button_evt evt = val ? BUTTON_EVT_PRESSED : BUTTON_EVT_RELEASED;
    if (user_cb) {
        user_cb(evt);
    }
}

static K_WORK_DELAYABLE_DEFINE(cooldown_work, cooldown_expired);

void button_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
    gpio_pin_toggle_dt(&led);
    gpio_pin_toggle_dt(&switch_1);
    k_work_reschedule(&cooldown_work, K_MSEC(15));
}

int button_init(button_event_handler_t handler)
{
    int err = -1;

    if (!handler) {
        return -EINVAL;
    }

    user_cb = handler;

	if (!device_is_ready(input_1.port)) {
		return -EIO;
	}

	err = gpio_pin_configure_dt(&input_1, GPIO_INPUT);
	if (err) {
        return err;
	}

	err = gpio_pin_interrupt_configure_dt(&input_1, GPIO_INT_EDGE_TO_ACTIVE);
	if (err) {
		return err;
	}

	gpio_init_callback(&button_cb_data, button_pressed, BIT(input_1.pin));
	err = gpio_add_callback(input_1.port, &button_cb_data);
    if (err) {
        return err;
    }

    err = gpio_pin_configure_dt(&led, GPIO_OUTPUT);

    if (!gpio_is_ready_dt(&switch_1))
	{
		// printk("Error: switch_1 device %s is not ready\n", switch_1.port->name);
		return 0;
	}
    err = gpio_pin_configure_dt(&switch_1, (GPIO_OUTPUT_LOW | GPIO_PULL_DOWN));
	if (err != 0) {
		// printk("Error %d: failed to configure %s pin %d\n",
		//        err, switch_1.port->name, switch_1.pin);
		return 0;
	}

    return 0;
}