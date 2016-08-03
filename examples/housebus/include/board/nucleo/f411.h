#ifndef BOARD_NUCLEO_F411
#define BOARD_NUCLEO_F411

#include <common/oscillator.h>
#include <common/clock.h>

#include <processor/stm32f411.h>

namespace board {

namespace oscillator {

typedef common::oscillator::tag<common::oscillator::source_t::external, 16000000> external_16mhz;
typedef common::oscillator::tag<common::oscillator::source_t::external, 32768> external_32khz;

}

namespace pll {

typedef processor::pll::tag<processor::oscillator::internal_16mhz, > pll_84mhz;

}

namespace clock {

typedef common::clock::tag<pll::pll_84mhz, 1> clock_84mhz;
typedef common::clock::tag<pll::pll_84mhz, 21> clock_4mhz;

}

}

#endif
