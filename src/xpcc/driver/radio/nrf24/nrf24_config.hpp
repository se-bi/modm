// coding: utf-8
/* Copyright (c) 2014, Roboterclub Aachen e. V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC__NRF24_CONFIG_HPP
#define XPCC__NRF24_CONFIG_HPP

#include <stdint.h>
#include <xpcc/debug/logger.hpp>

#include "nrf24_phy.hpp"
#include "nrf24_definitions.hpp"

#undef  XPCC_LOG_LEVEL
#define XPCC_LOG_LEVEL xpcc::log::DISABLED

namespace xpcc
{

/**
 * Configuration interface for nRF24L01+
 *
 * This class allows for configuration of some aspects of the nRF24L01+
 * wireless modules. It doesn't implement every aspect, but hopefully
 * all the often used ones.
 *
 * @ingroup	nrf24
 * @author		Daniel Krebs
 */
template<typename Nrf24Phy>
class Nrf24Config : public Nrf24Register
{

public:

	enum class
	Mode
	{
		Rx,
		Tx
	};

	enum class
	Speed
	{
		kBps250,
		MBps1,
		MBps2
	};

	enum class
	Crc
	{
		NoCrc,
		Crc1Byte,
		Crc2Byte
	};

	enum class
	AddressWidth : uint8_t
	{
		/* 2 byte works in hardware but is illegal according to datasheet */
		/* Byte2 = 0x00, */
		Byte3 = 0x01,
		Byte4 = 0x02,
		Byte5 = 0x03
	};

	enum class
	RfPower : uint8_t
	{
		Minus18dBm  = 0x00,
		Minus12dBm  = 0x01,
		Minus6dBm   = 0x02,
		dBm0        = 0x03
	};

	enum class
	AutoRetransmitDelay : uint8_t
	{
		us250   = 0x00,
		us500   = 0x01,
		us750   = 0x02,
		us1000  = 0x03,
		us1250  = 0x04,
		us1500  = 0x05,
		us1750  = 0x06,
		us2000  = 0x07,
		us2250  = 0x08,
		us2500  = 0x09,
		us2750  = 0x0A,
		us3000  = 0x0B,
		us3250  = 0x0C,
		us3500  = 0x0D,
		us3750  = 0x0E,
		us4000  = 0x0F,
	};

	enum class
	AutoRetransmitCount : uint8_t
	{
		Disable         = 0x00,
		Retransmit1     = 0x01,
		Retransmit2     = 0x02,
		Retransmit3     = 0x03,
		Retransmit4     = 0x04,
		Retransmit5     = 0x05,
		Retransmit6     = 0x06,
		Retransmit7     = 0x07,
		Retransmit8     = 0x08,
		Retransmit9     = 0x09,
		Retransmit10    = 0x0A,
		Retransmit11    = 0x0B,
		Retransmit12    = 0x0C,
		Retransmit13    = 0x0D,
		Retransmit14    = 0x0E,
		Retransmit15    = 0x0F
	};


public:
	static void
	powerUp()
	{ Nrf24Phy::setBits(NrfRegister::CONFIG, Config::PWR_UP); }

	static void
	powerDown()
	{ Nrf24Phy::clearBits(NrfRegister::CONFIG, Config::PWR_UP); }

	static void
	setChannel(uint8_t channel)
	{ Nrf24Phy::writeRegister(NrfRegister::RF_CH, channel); }

	static void
	setMode(Mode mode);

	static void
	setSpeed(Speed speed);

	static void
	setCrc(Crc crc);

	static void
	setAddressWidth(AddressWidth width)
	{ Nrf24Phy::writeRegister(NrfRegister::SETUP_AW, static_cast<uint8_t>(width)); }

	static void
	setRfPower(RfPower power)
	{ Nrf24Phy::writeRegister(NrfRegister::RF_SETUP, static_cast<uint8_t>(power) << 1); }

	static void
	setAutoRetransmitDelay(AutoRetransmitDelay delay)
	{ Nrf24Phy::writeRegister(NrfRegister::SETUP_RETR, static_cast<uint8_t>(delay) << 4); }

	static void
	setAutoRetransmitCount(AutoRetransmitCount count)
	{ Nrf24Phy::writeRegister(NrfRegister::SETUP_RETR, static_cast<uint8_t>(count)); }

	static void
	enableFeatureNoAck()
	{ Nrf24Phy::setBits(NrfRegister::FEATURE, Feature::EN_DYN_ACK); }

	static void
	disableFeatureNoAck()
	{ Nrf24Phy::clearBits(NrfRegister::FEATURE, Feature::EN_DYN_ACK); }

	/** @brief Enable Rx Pipe and set payload width
	 *
	 *  @param pipe     Pipe Number
	 */
	static void
	enablePipe(Pipe_t pipe, bool enableAutoAck);

	/** @brief Disable Rx Pipe and set payload width
	 *
	 *  @param pipe     Pipe Number
	 */
	static void
	disablePipe(Pipe_t pipe)
	{ Nrf24Phy::clearBits(NrfRegister::EN_RX_ADDR, (1 << pipe.value)); }

	/** @brief Return number of pipe number that has payload available
	 */
	static Pipe_t
	getPayloadPipe();

};

}   // namespace xpcc

#include "nrf24_config_impl.hpp"

#endif /* XPCC__NRF24_CONFIG_HPP */
