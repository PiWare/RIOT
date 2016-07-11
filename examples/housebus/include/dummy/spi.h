#ifndef DUMMY_SPI_H
#define DUMMY_SPI_H

#include <iostream>
#include <iomanip>

#include <interface/spi.h>


namespace dummy {

class spi:
	public interface::spi
{
	protected:
		const int m_index;

	public:
		spi(const int index):
			m_index(index)
		{

		}

		virtual bool write(const std::uint8_t *buffer, const size_t size)
		{
			std::cout << "spi" << m_index << ".write: " << std::hex << std::setw(2) << std::setfill('0');
			for (size_t index = 0; index < size; index++)
			{
				std::cout << *buffer++;
			}
			std::cout << std::endl;
			return true;
		}

		virtual bool read(std::uint8_t *buffer, const size_t size)
		{
			std::cout << "spi" << m_index << ".read " << std::hex << std::setw(2) << std::setfill('0') << std::endl;
			return true;
		}
};

}

#endif
