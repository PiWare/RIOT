#ifndef PERIPH_NVIC_H
#define PERIPH_NVIC_H

namespace periph {

class nvic
{
	private:
		static const std::uint32_t BASE = 0xE000E100;	/*!< NVIC base address */

		static const std::uint32_t ISER = 0x000;	/*!< Interrupt set-enable register */
		static const std::uint32_t ICER = 0x080;	/*!< Interrupt clear-enable registers */
		static const std::uint32_t ISPR = 0x100;	/*!<  */
		static const std::uint32_t ICPR = 0x180;	/*!<  */

	public:
		enum class priority_t
		{
			low		= 0xF0,
			medium	= 0x70,
			high	= 0x00,
		};

		template<const std::uint8_t index_, const priority_t priority_>
		struct irq_tag
		{
			static_assert(index <= 80, "Interrupt index out of range");

			static constexpr std::uint8_t index = index_;
			static constexpr priority_t priority = priority_;
		};

		typedef irq_tag<0, > reset_tag;

		template<typename T>
		static void enable(const std::uint32_t value_low = 0, const std::uint32_t value_mid = 0, const std::uint32_t value_high = 0)
		{
			typedef T config;

			if (config::index < 32)
				enable<Tn, Args...>(value_low | (1 << config::index), value_mid, value_high);
			else
			if (config::index < 64)
				enable<Tn, Args...>(value_low, value_mid | (1 << (config::index - 32)), value_high);
			else
				enable<Tn, Args...>(value_low, value_mid, value_high | (1 << (config::index - 64)));
		}

		template<typename T, typename Tn, typename... Args>
		static void enable(const std::uint32_t value_low = 0, const std::uint32_t value_mid = 0, const std::uint32_t value_high = 0)
		{
			typedef T config;

			if (config::index < 32)
				enable<Tn, Args...>(value_low | (1 << config::index), value_mid, value_high);
			else
			if (config::index < 64)
				enable<Tn, Args...>(value_low, value_mid | (1 << (config::index - 32)), value_high);
			else
				enable<Tn, Args...>(value_low, value_mid, value_high | (1 << (config::index - 64)));
		}

};

}

#endif
