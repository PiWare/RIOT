#ifndef INTERFACE_PWM_H
#define INTERFACE_PWM_H

namespace interface {

class pwm
{
	public:
		virtual void set(const std::uint8_t value) = 0;
};

}

#endif
