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

		enum class type_t
		{
			exception,
			interrupt
		};

		template<const std::uint8_t index_, const std::int8_t irq_, const type_t type_ = type_t::interrupt>
		struct irq_tag
		{
			static_assert(index <= 80, "Interrupt index out of range");

			static constexpr std::uint8_t index = index_;
			static constexpr std::int8_t irq = irq_;
			static constexpr type_t type = type_;

			static constexpr std::uint32_t offset = index * 4;
		//	static constexpr priority_t priority = priority_;
		};

		/* Cortex-M exceptions */
		typedef irq_tag<0, -100, type_t::exception> stack_tag;	/*!< Stack pointer, only for completion */
		typedef irq_tag<1, -100, type_t::exception> reset_tag;	/*!< Reset, priority = -3 (below normal 0-255) */
		typedef irq_tag<2, -14, type_t::exception> nmi_tag;	/*!< Non maskable interrupt, clock security system, priority = -2 (below normal 0-255) */
		typedef irq_tag<3, -13, type_t::exception> hard_fault_tag;	/*!< All class of fault, priority = -1 (below normal 0-255) */
		typedef irq_tag<4, -12, type_t::exception> memory_management_fault_tag;	/*!< Memory management */
		typedef irq_tag<5, -11, type_t::exception> bus_fault_tag;	/*!< Pre-fetch fault, memory access fault */
		typedef irq_tag<6, -10, type_t::exception> usage_fault_tag;	/*!< Undefinied instruction or illegal state */
		typedef irq_tag<11, -5, type_t::exception> sv_call_tag;	/*!< System serviced call wie SWI instruction */
		typedef irq_tag<12, -4, type_t::exception> debug_monitor_tag;	/*!< Debug Monitor */
		typedef irq_tag<14, -2, type_t::exception> pend_sv_tag;	/*!< Pendable request for system service */
		typedef irq_tag<15, -1, type_t::exception> systick_tag;	/*!< System tick timer */

		/* STM32F4xx interrupts */
		typedef irq_tag<16, 0, type_t::interrupt> interrupt_tag;	/*!<  */

		typedef irq_tag<16, 0, type_t::interrupt> wwdg_tag;	/*!< Window watchdog interrupt */
		typedef irq_tag<17, 1, type_t::interrupt> exti16_tag;	/*!< External interrupt 16 */
		typedef irq_tag<18, 2, type_t::interrupt> exti21_tag;	/*!< External interrupt 21 */
		typedef irq_tag<19, 3, type_t::interrupt> exti22_tag;	/*!< External interrupt 22 */
		typedef irq_tag<19, 3, type_t::interrupt> rtc_wkup_tag;	/*!< RTC wakeup interrupt */
		typedef irq_tag<20, 4, type_t::interrupt> flash_tag;	/*!< Flash global interrupt */
		typedef irq_tag<21, 5, type_t::interrupt> rcc_tag;	/*!< RCC global interrupt */
		typedef irq_tag<22, 6, type_t::interrupt> exti0_tag;	/*!< External interrupt 0 */
		typedef irq_tag<23, 7, type_t::interrupt> exti1_tag;	/*!< External interrupt 1 */
		typedef irq_tag<24, 8, type_t::interrupt> exti2_tag;	/*!< External interrupt 2 */
		typedef irq_tag<25, 9, type_t::interrupt> exti3_tag;	/*!< External interrupt 3 */
		typedef irq_tag<26, 10, type_t::interrupt> exti4_tag;	/*!< External interrupt 4 */
		typedef irq_tag<27, 11, type_t::interrupt> dma1_stream0_tag;	/*!< DMA 1 stream 0 global interrupt */
		typedef irq_tag<28, 12, type_t::interrupt> dma1_stream1_tag;	/*!< DMA 1 stream 1 global interrupt */
		typedef irq_tag<29, 13, type_t::interrupt> dma1_stream2_tag;	/*!< DMA 1 stream 2 global interrupt */
		typedef irq_tag<30, 14, type_t::interrupt> dma1_stream3_tag;	/*!< DMA 1 stream 3 global interrupt */
		typedef irq_tag<31, 15, type_t::interrupt> dma1_stream4_tag;	/*!< DMA 1 stream 4 global interrupt */
		typedef irq_tag<32, 16, type_t::interrupt> dma1_stream5_tag;	/*!< DMA 1 stream 5 global interrupt */
		typedef irq_tag<33, 17, type_t::interrupt> dma1_stream6_tag;	/*!< DMA 1 stream 6 global interrupt */
		typedef irq_tag<34, 18, type_t::interrupt> adc1_tag;	/*!< ADC1 global interrupt */
		typedef irq_tag<39, 23, type_t::interrupt> exti5_tag;	/*!< External interrupt 5 interrupt */
		typedef irq_tag<39, 23, type_t::interrupt> exti6_tag;	/*!< External interrupt 6 interrupt */
		typedef irq_tag<39, 23, type_t::interrupt> exti7_tag;	/*!< External interrupt 7 interrupt */
		typedef irq_tag<39, 23, type_t::interrupt> exti8_tag;	/*!< External interrupt 8 interrupt */
		typedef irq_tag<39, 23, type_t::interrupt> exti9_tag;	/*!< External interrupt 9 interrupt */
		typedef irq_tag<40, 24, type_t::interrupt> tim1_brk_tag;	/*!< Timer 1 break interrupt */
		typedef irq_tag<40, 24, type_t::interrupt> tim9_tag;	/*!< Timer 9 interrupt */
		typedef irq_tag<41, 25, type_t::interrupt> tim1_up_tag;	/*!< Timer 1 update interrupt */
		typedef irq_tag<41, 25, type_t::interrupt> tim10_tag;	/*!< Timer 10 interrupt */
		typedef irq_tag<42, 26, type_t::interrupt> tim1_trg_tag;	/*!< Timer 1 trigger interrupt */
		typedef irq_tag<42, 26, type_t::interrupt> tim11_tag;	/*!< Timer 11 interrupt */
		typedef irq_tag<43, 27, type_t::interrupt> tim1_cc_tag;	/*!< Timer 1 capture/compare interrupt */
		typedef irq_tag<44, 28, type_t::interrupt> tim2_tag;	/*!< Timer 2 interrupt */
		typedef irq_tag<45, 29, type_t::interrupt> tim3_tag;	/*!< Timer 3 interrupt */
		typedef irq_tag<46, 30, type_t::interrupt> tim4_tag;	/*!< Timer 4 interrupt */
		typedef irq_tag<47, 31, type_t::interrupt> i2c1_event_tag;	/*!< I2C 1 event interrupt */
		typedef irq_tag<48, 32, type_t::interrupt> i2c1_error_tag;	/*!< I2C 1 error interrupt */
		typedef irq_tag<49, 33, type_t::interrupt> i2c2_event_tag;	/*!< I2C 2 event interrupt */
		typedef irq_tag<50, 34, type_t::interrupt> i2c2_error_tag;	/*!< I2C 2 error interrupt */
		typedef irq_tag<51, 35, type_t::interrupt> spi1_tag;	/*!< SPI 1 interrupt */
		typedef irq_tag<52, 36, type_t::interrupt> spi2_tag;	/*!< SPI 2 interrupt */
		typedef irq_tag<53, 37, type_t::interrupt> usart1_tag;	/*!< USART 1 interrupt */
		typedef irq_tag<54, 38, type_t::interrupt> usart2_tag;	/*!< USART 2 interrupt */
		typedef irq_tag<56, 40, type_t::interrupt> exti10_tag;	/*!< External interrupt 10 interrupt */
		typedef irq_tag<56, 40, type_t::interrupt> exti11_tag;	/*!< External interrupt 11 interrupt */
		typedef irq_tag<56, 40, type_t::interrupt> exti12_tag;	/*!< External interrupt 12 interrupt */
		typedef irq_tag<56, 40, type_t::interrupt> exti13_tag;	/*!< External interrupt 13 interrupt */
		typedef irq_tag<56, 40, type_t::interrupt> exti14_tag;	/*!< External interrupt 14 interrupt */
		typedef irq_tag<56, 40, type_t::interrupt> exti15_tag;	/*!< External interrupt 15 interrupt */
		typedef irq_tag<57, 41, type_t::interrupt> exti17_tag;	/*!< External interrupt 17 interrupt */
		typedef irq_tag<57, 41, type_t::interrupt> rtc_alarm_tag;	/*!< RTC alarm interrupt */
		typedef irq_tag<58, 42, type_t::interrupt> exti18_tag;	/*!< External interrupt 18 interrupt */
		typedef irq_tag<58, 42, type_t::interrupt> usb_otg_wakeup_tag;	/*!< USB OTG Wakeup interrupt */
		typedef irq_tag<63, 47, type_t::interrupt> dma1_stream7_tag;	/*!< DMA 1 stream 7 global interrupt */
		typedef irq_tag<65, 49, type_t::interrupt> sdio_tag;	/*!< SDIO global interrupt */
		typedef irq_tag<66, 50, type_t::interrupt> tim5_tag;	/*!< Timer 5 interrupt */
		typedef irq_tag<67, 51, type_t::interrupt> spi3_tag;	/*!< SPI 3 interrupt */
		typedef irq_tag<72, 56, type_t::interrupt> dma2_stream0_tag;	/*!< DMA 2 stream 0 global interrupt */
		typedef irq_tag<73, 57, type_t::interrupt> dma2_stream1_tag;	/*!< DMA 2 stream 1 global interrupt */
		typedef irq_tag<74, 58, type_t::interrupt> dma2_stream2_tag;	/*!< DMA 2 stream 2 global interrupt */
		typedef irq_tag<75, 59, type_t::interrupt> dma2_stream3_tag;	/*!< DMA 2 stream 3 global interrupt */
		typedef irq_tag<76, 60, type_t::interrupt> dma2_stream4_tag;	/*!< DMA 2 stream 4 global interrupt */
		typedef irq_tag<83, 67, type_t::interrupt> usb_otg_tag;	/*!< USB ORG global interrupt */
		typedef irq_tag<84, 68, type_t::interrupt> dma2_stream5_tag;	/*!< DMA 2 stream 5 global interrupt */
		typedef irq_tag<85, 69, type_t::interrupt> dma2_stream6_tag;	/*!< DMA 2 stream 6 global interrupt */
		typedef irq_tag<86, 70, type_t::interrupt> dma2_stream7_tag;	/*!< DMA 2 stream 7 global interrupt */
		typedef irq_tag<87, 71, type_t::interrupt> usart6_tag;	/*!< USART 6 interrupt */
		typedef irq_tag<88, 72, type_t::interrupt> i2c3_event_tag;	/*!< I2C 3 event interrupt */
		typedef irq_tag<89, 73, type_t::interrupt> i2c3_error_tag;	/*!< I2C 3 error interrupt */
		typedef irq_tag<97, 81, type_t::interrupt> fpu_tag;	/*!< FPU global interrupt */
		typedef irq_tag<100, 84, type_t::interrupt> spi4_tag;	/*!< SPI 4 global interrupt */
		typedef irq_tag<101, 85, type_t::interrupt> spi5_tag;	/*!< SPI 5 global interrupt */

		template<typename T>
		static void enable(const std::uint32_t value_low = 0, const std::uint32_t value_mid = 0, const std::uint32_t value_high = 0)
		{
			typedef T config;

			static_assert(config::type == type_t::interrupt, "Exceptions must be enabled separately");

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

			static_assert(config::type == type_t::interrupt, "Exceptions must be enabled separately");

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
