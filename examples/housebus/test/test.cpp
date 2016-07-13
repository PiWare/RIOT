#include <dummy/gpio.h>
#include <dummy/i2c.h>
#include <dummy/spi.h>

#include <periph/periph.h>
#include <periph/clock.h>

#include <driver/rgb.h>
#include <driver/i2c/pcal6408.h>
#include <driver/spi/pcd8544.h>

int main(int, char**)
{
//	periph::enable<periph::gpioA, periph::gpioB>();

	periph::clock::pll<periph::HSI16, 16, 200, 2, 4>();

	dummy::spi spi1(1);
	dummy::i2c i2c1(1);

	driver::i2c::pcal6408 io_expander(i2c1);
	interface::gpio &led_red = io_expander.get(0);
	interface::gpio &led_green = io_expander.get(1);
	interface::gpio &led_blue = io_expander.get(2);

	driver::led::rgp_gpio rgb1(led_red, led_green, led_blue);
	rgb1.set(type::color::mangenta);

	interface::gpio &lcd_reset = io_expander.get(3);
	interface::gpio &lcd_data_command = io_expander.get(4);
	driver::spi::pcd8544 lcd1(spi1, lcd_reset, lcd_data_command);
	lcd1.set(true);
	lcd1.draw(true);

	return 0;
}
