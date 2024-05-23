#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS   1000
#define LED0_NODE DT_NODELABEL(led4)
// led4 is added manually using the DT overlay which is attached to @pin27 

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

// Expire call back function from the timer 
static void mytimer_cb (struct k_timer *dummy){
	gpio_pin_toggle_dt(&led); 
}

struct k_timer mytimer; 

int main(void)
{
	k_timer_init(&mytimer, mytimer_cb, NULL);	// .expiry_fn = mytimer_cb and .stop_fn = NULL
	k_timer_start(&mytimer, K_SECONDS(20), K_SECONDS(3));  // The timer starts after 20 secs and call the CBack fn every 3 seconds 
	
	gpio_pin_configure_dt(&led, GPIO_OUTPUT);
	
	while (true){
	}

	return 0;
}
