#ifndef INTERFACE_SPI_H
#define INTERFACE_SPI_H

#include <cstddef>
#include <cstdint>


namespace interface {

class spi
{
	public:
		virtual bool write(const std::uint8_t *buffer, const size_t size) = 0;
		virtual bool read(std::uint8_t *buffer, const size_t size) = 0;
};

}

#endif
