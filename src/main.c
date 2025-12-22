/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include "button.h"

#define SLEEP_TIME_MS	1

#if !DT_NODE_HAS_STATUS_OKAY(DT_ALIAS(led0))
#error "Overlay for led node not properly defined."
#endif

#if !DT_NODE_EXISTS(DT_NODELABEL(load_switch1))
#error "Overlay for power output node not properly defined."
#endif

#if !DT_NODE_EXISTS(DT_NODELABEL(load_switch2))
#error "Overlay for power output node not properly defined."
#endif

#if !DT_NODE_EXISTS(DT_NODELABEL(load_switch3))
#error "Overlay for power output node not properly defined."
#endif

#if !DT_NODE_EXISTS(DT_NODELABEL(load_switch4))
#error "Overlay for power output node not properly defined."
#endif

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
