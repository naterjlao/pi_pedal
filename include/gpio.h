#ifndef GPIO_H
#define GPIO_H

/* 
	Setup the environment for GPIO manipulation.
	This should be called once only in main driver.
*/
void setup_io();

/* 
	Setup the GPIO to input/output.
   	Must be called before gpio_set() or gpio_get().
	Returns -1 on error.
*/
int gpio_input(unsigned int g);
int gpio_output(unsigned int g);

/*
	Set GPIO to on/off.
	Returns -1 on error.
*/
int gpio_set(unsigned int g, bool on);

/*
	Get GPIO voltage: 0->low, 1->high.
	Returns -1 on error.
*/
int gpio_get(unsigned int g);

// TODO need wrappers for GPIO_PULL, GPIO_PULLCLK0

#endif

