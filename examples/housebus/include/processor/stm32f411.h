#ifndef PROCESSOR_STM32F411_H
#define PROCESSOR_STM32F411_H

#include <common/oscillator.h>


namespace processor {

namespace oscillator {

typedef common::oscillator::tag<common::oscillator::source_t::internal, 16000000> internal_16mhz;
typedef common::oscillator::tag<common::oscillator::source_t::internal, 32000> internal_32khz;

}

}

#endif
