/******************************************************************************
 * File:		gpio_setup.c
 * Language: 	C
 * Author:		Nathaniel Lao (lao.nathan@yahoo.com)
 *
 * Setup script for Raspberry Pi 3 for GPIO access through memory registers
 * Based on reference  code from https://elinux.org/RPi_GPIO_Code_Samples
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "gpio.h"

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

/* Memory address for GPIO */
#define BCM2708_PERI_BASE   0x3F000000
#define GPIO_BASE           (BCM2708_PERI_BASE + 0x200000)

/* GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y) */
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

/* Sets the GPIO on or off*/
#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

/* Get the input digital voltage of GPIO */
#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH

/* Sets the GPIO to pull up voltage or ground */
#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

int  mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;

/* Set up memory regions to access GPIO */
void setup_io() {
   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }

   /* mmap GPIO */
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );

   close(mem_fd); //No need to keep mem_fd open after mmap

   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }

   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;

}

/******************************************************************************
* WRAPPER FUNCTIONS
******************************************************************************/

/* Set GPIO to INPUT */
int gpio_input(unsigned int g) {
	if (!check_gpio())
		goto error;

	INP_GPIO(g);

	return 0;
error:
	return -1;
}

/* Set GPIO to OUTPUT */
int gpio_output(unsigned int g) {
	if (!check_gpio())
		goto error;

	INP_GPIO(g);	// INP_GPIO must be called BEFORE OUT_GPIO
	OUT_GPIO(g);

	return 0;
error:
	return -1;
}


/* Turn GPIO On or Off */
int gpio_set(unsigned int g, bool on) {
	if (!check_gpio())
		goto error;

	if (on)
		GPIO_SET = 1<<g;
	else
		GPIO_CLR = 1<<g;

	return 0;
error:
	return -1;
}

/* Get GPIO (returns -1 on err) */
int gpio_get(unsigned int g) {
	if (!check_gpio())
		goto error;

	return GET_GPIO(g) == 0 ? 0 : 1;
error:
	return -1;
}

// TODO need wrappers for GPIO_PULL, GPIO_PULLCLK0

