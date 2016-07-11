#ifndef INTERFACE_PWM_H
#define INTERFACE_PWM_H

namespace interface {

class pwm
{
	public:
		virtual void set(const std::uint16_t value) = 0;
};

}

#endif
