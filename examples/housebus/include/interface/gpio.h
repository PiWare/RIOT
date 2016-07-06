#ifndef INTERFACE_GPIO_H
#define INTERFACE_GPIO_H

namespace interface {

class gpio
{
	public:
		virtual void set(const bool value) = 0;

		virtual void set(void) = 0;
		virtual void clear(void) = 0;
		virtual bool get(void) const = 0;
};

}

#endif
