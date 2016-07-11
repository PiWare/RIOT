#ifndef INTERFACE_GPIO_H
#define INTERFACE_GPIO_H

#include <type/direction.h>


namespace interface {

class gpio
{
	public:
		virtual void direction(const type::direction value) = 0;
		virtual type::direction direction() const = 0;

		virtual void set(const bool value) = 0;
		virtual bool get(void) const = 0;
};

}

#endif
