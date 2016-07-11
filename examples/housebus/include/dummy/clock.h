#ifndef PERIPH_CLOCK_H
#define PERIPH_CLOCK_H


namespace periph { namespace clock {



#if 0
class clock
{
	public:
		/* FIXME: Clean-up names. This is a workaround because defines polute these names... */

		static const std::uint8_t CR			= 0x00;		/*!< RCC clock control register */
		static const std::uint8_t PLLCFGR		= 0x04;		/*!< RCC PLL configuration register */
		static const std::uint8_t CFGR			= 0x08;		/*!< RCC clock configuration register */
		static const std::uint8_t CIR			= 0x0C;		/*!< RCC clock interrupt register */
		static const std::uint8_t AHB1RSTR		= 0x10;		/*!< RCC AHB1 peripheral reset register */
		static const std::uint8_t AHB2RSTR		= 0x14;		/*!< RCC AHB2 peripheral reset register */
		static const std::uint8_t APB1RSTR		= 0x20;		/*!< RCC APB1 peripheral reset register */
		static const std::uint8_t APB2RSTR		= 0x24;		/*!< RCC APB2 peripheral reset register */
		static const std::uint8_t AHB1ENR		= 0x30;		/*!< RCC AHB1 peripheral clock enable register */
		static const std::uint8_t AHB2ENR		= 0x34;		/*!< RCC AHB2 peripheral clock enable register */
		static const std::uint8_t APB1ENR		= 0x40;		/*!< RCC APB1 peripheral clock enable register */
		static const std::uint8_t APB2ENR		= 0x44;		/*!< RCC APB2 peripheral clock enable register */
		static const std::uint8_t AHB1LPENR		= 0x50;		/*!< RCC AHB1 peripheral clock enable in low power mode register */
		static const std::uint8_t AHB2LPENR		= 0x54;		/*!< RCC AHB2 peripheral clock enable in low power mode register */
		static const std::uint8_t APB1LPENR		= 0x60;		/*!< RCC APB1 peripheral clock enable in low power mode register */
		static const std::uint8_t APB2LPENR		= 0x64;		/*!< RCC APB2 peripheral clock enable in low power mode register */
		static const std::uint8_t BDCR			= 0x70;		/*!< RCC Backup domain control register */
		static const std::uint8_t CSR			= 0x74;		/*!< RCC clock control & status register */
		static const std::uint8_t SSCGR			= 0x80;		/*!< RCC spread spectrum clock generation register */
		static const std::uint8_t PLLI2SCFGR	= 0x84;		/*!< RCC PLLI2S configuration register */
		static const std::uint8_t DCKCFGR		= 0x8C;		/*!< RCC Dedicated Clocks Configuration Register */

		/* AHB 1 */
		static const std::uint32_t DMA2_		= 1 << 22;
		static const std::uint32_t DMA1_		= 1 << 21;
		static const std::uint32_t CRC_			= 1 << 12;
		static const std::uint32_t GPIOH_		= 1 << 7;
		static const std::uint32_t GPIOE_		= 1 << 4;
		static const std::uint32_t GPIOD_		= 1 << 3;
		static const std::uint32_t GPIOC_		= 1 << 2;
		static const std::uint32_t GPIOB_		= 1 << 1;
		static const std::uint32_t GPIOA_		= 1 << 0;

		/* AHB 2 */
		static const std::uint32_t OTGFS_		= 1 << 7;

		/* APB 1 */
		static const std::uint32_t PWR_			= 1 << 28;
		static const std::uint32_t I2C3_		= 1 << 23;
		static const std::uint32_t I2C2_		= 1 << 22;
		static const std::uint32_t I2C1_		= 1 << 21;
		static const std::uint32_t UART2_		= 1 << 17;
		static const std::uint32_t SPI3_		= 1 << 15;
		static const std::uint32_t SPI2_		= 1 << 14;
		static const std::uint32_t WWDG_		= 1 << 11;
		static const std::uint32_t TIM5_		= 1 << 3;
		static const std::uint32_t TIM4_		= 1 << 2;
		static const std::uint32_t TIM3_		= 1 << 1;
		static const std::uint32_t TIM2_		= 1 << 0;

		/* APB 2 */
		static const std::uint32_t SPI5_		= 1 << 20;
		static const std::uint32_t TIM11_		= 1 << 18;
		static const std::uint32_t TIM10_		= 1 << 17;
		static const std::uint32_t TIM9_		= 1 << 16;
		static const std::uint32_t SYSCFG_		= 1 << 14;
		static const std::uint32_t SPI4_		= 1 << 13;
		static const std::uint32_t SPI1_		= 1 << 12;
		static const std::uint32_t SDIO_		= 1 << 11;
		static const std::uint32_t ADC1_		= 1 << 8;
		static const std::uint32_t UART6_		= 1 << 5;
		static const std::uint32_t UART1_		= 1 << 4;
		static const std::uint32_t TIM1_		= 1 << 0;

	private:
		static const std::uint32_t OFFSET		= 0x40023800;

		static clock &m_instance;

		clock();

	protected:

	public:
		static clock &get() { return m_instance; }

		/* FIXME: Use variadic template struct with all offset and all bits */
		void reset(const std::uint8_t offset, const std::uint32_t bit)
		{
			*((volatile std::uint32_t *)(OFFSET + offset)) = bit;
		}

		/* FIXME: Use template struct with offset */
		void enable(const std::uint8_t offset, const std::uint32_t bit)
		{
			*((volatile std::uint32_t *)(OFFSET + offset)) |= bit;
		}

		/* FIXME: Use template struct with offset */
		void disable(const std::uint8_t offset, const std::uint32_t bit)
		{
			*((volatile std::uint32_t *)(OFFSET + offset)) &= ~bit;
		}
};
#endif

} }

#endif
