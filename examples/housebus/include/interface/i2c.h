#ifndef INTERFACE_I2C_H
#define INTERFACE_I2C_H

#include <cstddef>
#include <cstdint>


namespace interface {

class i2c
{
	public:
		virtual bool write(const std::uint8_t address, const std::uint8_t *buffer, const size_t size) = 0;
		virtual bool read(const std::uint8_t address, std::uint8_t *buffer, const size_t size) = 0;
};

}

#endif
