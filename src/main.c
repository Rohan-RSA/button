/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * NOTE: If you are looking into an implementation of button events with
 * debouncing, check out `input` subsystem and `samples/subsys/input/input_dump`
 * example instead.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include "button.h"

#define SLEEP_TIME_MS	1

#define SW0_NODE	DT_ALIAS(sw0)
#if !DT_NODE_HAS_STATUS_OKAY(SW0_NODE)
#error "Unsupported board: sw0 devicetree alias is not defined"
#endif

#if !DT_NODE_EXISTS(DT_NODELABEL(load_switch1))
#error "Overlay for power output node not properly defined."
#endif

// static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET_OR(SW0_NODE, gpios, {0});
// static struct gpio_dt_spec led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led0), gpios, {0});

/**
 * @brief	These switches are the gpio connected to the isolated MOSFET driver
 * 			IC. Each IC has two input and two outputs to drive the GATE	of the
 * 			connected MOSFET.
 */
// static const struct gpio_dt_spec switch_1 = GPIO_DT_SPEC_GET(DT_ALIAS(switch1), gpios);
// static const struct gpio_dt_spec switch_2 = GPIO_DT_SPEC_GET(DT_ALIAS(switch2), gpios);
// static const struct gpio_dt_spec switch_3 = GPIO_DT_SPEC_GET(DT_ALIAS(switch3), gpios);
// static const struct gpio_dt_spec switch_4 = GPIO_DT_SPEC_GET(DT_ALIAS(switch4), gpios);

/**
 * @brief	These are the gpio connected to the mechanical SPST/push button
 * 			switches. They are used by the user to toggle the attached load,
 * 			in this case it will be a 12V LED.
 */
// static const struct gpio_dt_spec input_1 = GPIO_DT_SPEC_GET(DT_ALIAS(input1), gpios);
// static const struct gpio_dt_spec input_2 = GPIO_DT_SPEC_GET(DT_ALIAS(input2), gpios);
// static const struct gpio_dt_spec input_3 = GPIO_DT_SPEC_GET(DT_ALIAS(input3), gpios);
// static const struct gpio_dt_spec input_4 = GPIO_DT_SPEC_GET(DT_ALIAS(input4), gpios);

/**
 * @brief	Define callbacks for the input buttons
 */
// static struct gpio_callback button_cb_data;
// static struct gpio_callback user_input_cb_data;



// void switch_load(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
// {
// 	// gpio_pin_set_dt(&led, 1);
// 	// k_msleep(50);
// 	// gpio_pin_set_dt(&led, 0);
// 	gpio_pin_toggle_dt(&led);
// 	gpio_pin_toggle_dt(&switch_1);
	
// }

// int config_gpio(const struct device *dev)
// {

// }


static char *helper_button_evt_str(enum button_evt evt)
{
	switch (evt) {
	case BUTTON_EVT_PRESSED:
		return "Pressed";
	case BUTTON_EVT_RELEASED:
		return "Released";
	default:
		return "Unknown";
	}
}

static void button_event_handler(enum button_evt evt)
{
	// printk("Button event: %s\n", helper_button_evt_str(evt));
}

void main(void)
{
	int err = -1;

	// printk("Button Debouncing Sample!\n");

	err = button_init(button_event_handler);
	if (err) {
		// printk("Button Init failed: %d\n", err);
		return;
	}

	// printk("Init succeeded. Waiting for event...\n");
}

// int main(void)
// {
// 	int ret;

// 	if (!gpio_is_ready_dt(&switch_1))
// 	{
// 		printk("Error: switch_1 device %s is not ready\n", switch_1.port->name);
// 		return 0;
// 	}
// 	if (!gpio_is_ready_dt(&input_1))
// 	{
// 		printk("Error: input_1 device %s is not ready\n", input_1.port->name);
// 		return 0;
// 	}

// 	ret = gpio_pin_configure_dt(&input_1, (GPIO_INPUT | GPIO_PULL_DOWN));
// 	if (ret != 0) {
// 		printk("Error %d: failed to configure %s pin %d\n",
// 		       ret, input_1.port->name, input_1.pin);
// 		return 0;
// 	}
// 	ret = gpio_pin_interrupt_configure_dt(&input_1, GPIO_INT_EDGE_TO_ACTIVE);
// 	if (ret != 0) {
// 		printk("Error %d: failed to configure interrupt on %s pin %d\n",
// 			ret, input_1.port->name, input_1.pin);
// 		return 0;
// 	}
// 	gpio_init_callback(&user_input_cb_data, switch_load, BIT(input_1.pin));
// 	gpio_add_callback(input_1.port, &user_input_cb_data);
// 	printk("Set up button at %s pin %d\n", input_1.port->name, input_1.pin);

// 	ret = gpio_pin_configure_dt(&switch_1, (GPIO_OUTPUT_LOW | GPIO_PULL_DOWN));
// 	if (ret != 0) {
// 		printk("Error %d: failed to configure %s pin %d\n",
// 		       ret, switch_1.port->name, switch_1.pin);
// 		return 0;
// 	}

// 	if (led.port && !gpio_is_ready_dt(&led)) {
// 		printk("Error %d: LED device %s is not ready; ignoring it\n",
// 		       ret, led.port->name);
// 		led.port = NULL;
// 	}
// 	if (led.port) {
// 		ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT);
// 		if (ret != 0) {
// 			printk("Error %d: failed to configure LED device %s pin %d\n",
// 			       ret, led.port->name, led.pin);
// 			led.port = NULL;
// 		} else {
// 			printk("Set up LED at %s pin %d\n", led.port->name, led.pin);
// 		}
// 	}

// 	while (1)
// 	{
// 		k_msleep(500);
// 	}
	
// 	return 0;
// }
