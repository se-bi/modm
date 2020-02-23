/*
 * Copyright (c) 2011, Georgi Grinshpun
 * Copyright (c) 2011-2012, Fabian Greif
 * Copyright (c) 2012, 2014, Sascha Schade
 * Copyright (c) 2013, Kevin Läufer
 * Copyright (c) 2013, 2015-2017, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <modm/board.hpp>
using namespace modm::literals;

#include <modm/debug/logger.hpp>

modm::IODeviceWrapper< modm::platform::Usart2, modm::IOBuffer::DiscardIfFull > extLogDevice;
modm::log::Logger extLogger(extLogDevice);

// Set the log level
#undef  MODM_LOG_LEVEL
#define MODM_LOG_LEVEL modm::log::DEBUG

// ----------------------------------------------------------------------------
/**
 * Very basic example of USART usage.
 * The ASCII sequence 'A', 'B', 'C, ... , 'Z', 'A', 'B', 'C', ...
 * is printed with 9600 baud, 8N1 at pin PA3.
 */
int
main()
{
	Board::initialize();

	Board::LedRed::set();

	// Enable USART 2
	Usart2::connect<GpioA2::Tx>();
	Usart2::initialize<Board::SystemClock, 9600_Bd>();

	extLogger << "Hello" << modm::endl;
	extLogger << "Core Freq.: "   << Board::SystemClock::Frequency / 1e6 << " MHz" << modm::endl;
//	extLogger << "Ahb Freq.:  "   << Board::SystemClock::Ahb       / 1e6 << " MHz" << modm::endl;
	extLogger << "Apb1 Freq.: "   << Board::SystemClock::Apb1      / 1e6 << " MHz" << modm::endl;
	extLogger << "Apb2 Freq.: "   << Board::SystemClock::Apb2      / 1e6 << " MHz" << modm::endl;
	extLogger << "Timer1 Freq.: " << Board::SystemClock::Timer1    / 1e6 << " MHz" << modm::endl;
	extLogger << "Timer2 Freq.: " << Board::SystemClock::Timer2    / 1e6 << " MHz" << modm::endl;

	while (true)
	{
		static uint8_t c = 'A';
		Board::LedRed::toggle();
		Board::LedGreen::toggle();
		extLogDevice.write(c);
		++c;
		if (c > 'Z') {
			c = 'A';
		}
		modm::delayMilliseconds(500);
	}

	return 0;
}
