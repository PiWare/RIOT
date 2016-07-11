#ifndef DUMMY_I2C_H
#define DUMMY_I2C_H

#include <iostream>
#include <iomanip>

#include <interface/i2c.h>


namespace dummy {

class i2c:
	public interface::i2c
{
	protected:
		const int m_index;

	public:
		i2c(const int index):
			m_index(index)
		{

		}

		virtual bool write(const std::uint8_t address, const std::uint8_t *buffer, const size_t size)
		{
			std::cout << "i2c" << m_index << ".write@0x" << std::hex << std::setfill('0') << std::setw(2) << (int)address << ":";
			for (size_t index = 0; index < size; index++)
			{
				std::cout << " 0x" << std::setw(2) << (int)*buffer++;
			}
			std::cout << std::endl;
			return true;
		}

		virtual bool read(const std::uint8_t address, std::uint8_t *buffer, const size_t size)
		{
			std::cout << "i2c" << m_index << ".read@0x" << std::hex << std::setfill('0') << std::setw(2) << (int)address << ":";

			std::cout << std::endl;
			return true;
		}
};

}

#endif
