#ifndef INTERFACE_SPI_H
#define INTERFACE_SPI_H

namespace interface {

class spi
{
	public:
		virtual bool write(const char *buffer, const size_t size) = 0;
		virtual bool read(char *buffer, const size_t size) = 0;
};

}

#endif
