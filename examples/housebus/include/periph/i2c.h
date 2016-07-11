#ifndef INTERFACE_I2C_H
#define INTERFACE_I2C_H

namespace interface {

class i2c
{
	public:
		virtual bool write(const std::uint8_t address, const char *buffer, const size_t size) = 0;
		virtual bool read(const std::uint8_t address, char *buffer, const size_t size) = 0;
};

}

#endif
