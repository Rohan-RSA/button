#ifndef _BUTTON_H_
#define _BUTTON_H_

enum button_evt {
    BUTTON_EVT_PRESSED,
    BUTTON_EVT_RELEASED
};

typedef void (*button_event_handler_t)(enum button_evt evt);

int button_init(button_event_handler_t handler);

static struct gpio_dt_spec led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led0), gpios, {0});

static const struct gpio_dt_spec input_1 = GPIO_DT_SPEC_GET(DT_ALIAS(input1), gpios);
static const struct gpio_dt_spec input_2 = GPIO_DT_SPEC_GET(DT_ALIAS(input2), gpios);
static const struct gpio_dt_spec input_3 = GPIO_DT_SPEC_GET(DT_ALIAS(input3), gpios);
static const struct gpio_dt_spec input_4 = GPIO_DT_SPEC_GET(DT_ALIAS(input4), gpios);

/**
 * @brief	These switches are the gpio connected to the isolated MOSFET driver
 * 			IC's gate pin. Each IC has two input and two outputs to drive the GATE	of the
 * 			connected MOSFET.
 */
static const struct gpio_dt_spec switch_1 = GPIO_DT_SPEC_GET(DT_ALIAS(switch1), gpios);
static const struct gpio_dt_spec switch_2 = GPIO_DT_SPEC_GET(DT_ALIAS(switch2), gpios);
static const struct gpio_dt_spec switch_3 = GPIO_DT_SPEC_GET(DT_ALIAS(switch3), gpios);
static const struct gpio_dt_spec switch_4 = GPIO_DT_SPEC_GET(DT_ALIAS(switch4), gpios);

static struct gpio_callback input1_cb_data;
static struct gpio_callback input2_cb_data;
static struct gpio_callback input3_cb_data;
static struct gpio_callback input4_cb_data;

#endif /* _BUTTON_H_ */