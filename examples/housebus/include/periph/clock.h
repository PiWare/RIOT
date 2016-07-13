#ifndef PERIPH_CLOCK_H
#define PERIPH_CLOCK_H

#include <iostream>
#include <iomanip>


namespace periph {

enum class source_t
{
	internal	= 0,
	external	= 1,
};

template<unsigned int frequency_, source_t source_ = source_t::external>
struct clock_tag
{
	static constexpr unsigned int frequency = frequency_;
	static constexpr source_t source = source_;
	static constexpr unsigned int M = 0;
	static constexpr unsigned int N = 0;
};

typedef clock_tag<16000000, source_t::internal> HSI16;
typedef clock_tag< 4000000, source_t::external> HSE4;
typedef clock_tag< 8000000, source_t::external> HSE8;
typedef clock_tag<16000000, source_t::external> HSE16;

class clock
{
	private:
		static const std::uint32_t BASE	= 0x40023800;

		static const std::uint32_t CR			= 0x00;	/*!< Clock control register */
		static const std::uint32_t PLLCFGR		= 0x04;	/*!< PLL configuration register */
		static const std::uint32_t CFGR			= 0x08;	/*!< Clock configuration register */
		static const std::uint32_t CIR			= 0x0C;	/*!< Clock interrupt register */

		static const std::uint32_t BDCR			= 0x70;	/*!< Backup domain control register */
		static const std::uint32_t CSR			= 0x74;	/*!< Clock control & status register */
		static const std::uint32_t SSCGR		= 0x80;	/*!< Spread spectrum clock generation register */
		static const std::uint32_t PLLI2SCFGR	= 0x84;	/*!< PLL I2S configuration register */

	public:
		template<typename C, unsigned int M, unsigned int N, unsigned int P, unsigned int Q>
		static void pll()
		{
			typedef C config;

			static_assert((M >= 2) && (M <= 63), "Valid values for M: 2 <= M <= 63");
			static_assert((N >= 50) && (N <= 432), "Valid values for N: 50 <= N <= 432");
			static_assert((P == 2) || (P == 4) || (P == 6) || (P == 8), "Valid values for P: 2, 4, 6, 8");
			static_assert((Q >= 2) && (Q <= 15), "Valid values for Q: 2 <= Q <= 15");

			constexpr unsigned int VCO_IN = config::frequency / M;
			constexpr unsigned int VCO_OUT = VCO_IN * N;
			static_assert((VCO_IN >= 1000000) && (VCO_IN <= 2000000), "VCO_IN must be between 1MHz and 2MHz");
			static_assert((VCO_OUT >= 100000000) && (VCO_OUT <= 432000000), "VCO_OUT must be between 100MHz and 432MHz");

			constexpr unsigned int PLL_P = VCO_OUT / P;
			constexpr unsigned int PLL_Q = VCO_OUT / Q;
			static_assert(PLL_P <= 100000000, "PLL_P must not exeed 100MHz");
			static_assert(PLL_Q <= 50000000, "PLL_Q must not exeed 50MHz");

			std::uint32_t value = M | N << 6 | ((P >> 1) - 1) << 16 | Q << 24 | (unsigned int)config::source << 22;
			std::cout << std::hex << std::setfill('0') << "0x" << std::setw(8) << value << std::endl;

		//	*((volatile std::uint32_t *)BASE + PLLCFGR) = value;
		}

		template<typename C, unsigned int M, unsigned int N, unsigned int R>
		static void pll_i2s()
		{
			typedef C config;

			static_assert((M >= 2) && (M <= 63), "Valid values for M: 2 <= M <= 63");
			static_assert((N >= 50) && (N <= 432), "Valid values for N: 50 <= N <= 432");
			static_assert((R >= 2) && (R <= 7), "Valid values for R: 2 <= R <= 7");

			constexpr unsigned int VCO_IN = config::frequency / M;
			constexpr unsigned int VCO_OUT = VCO_IN * N;
			static_assert((VCO_IN >= 1000000) && (VCO_IN <= 2000000), "VCO_IN must be between 1MHz and 2MHz");
			static_assert((VCO_OUT >= 100000000) && (VCO_OUT <= 432000000), "VCO_OUT must be between 100MHz and 432MHz");

			constexpr unsigned int PLL_R = VCO_OUT / R;
			static_assert(PLL_R <= 192000000, "PLL_R must not exeed 192MHz");

			std::uint32_t value = M | N << 6 | R << 28;
			std::cout << std::hex << std::setfill('0') << "0x" << std::setw(8) << value << std::endl;

		//	*((volatile std::uint32_t *)BASE + PLLI2SCFGR) = value;
		}
};

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

}

#endif
