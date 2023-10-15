#pragma once

#include "../ModbusRequest.hpp"

struct __attribute__((__packed__)) WriteSingleRegResponse {
	uint8_t slaveAddress;
	uint8_t functionCode;
	uint8_t regAddressLow;
	uint8_t regAddressHigh;
	uint8_t data_0;
	uint8_t data_1;
	uint16_t crc_16;
};

class WriteSystemTimeRequest : public ModbusRequest<8, WriteSingleRegResponse>
{
public:
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_LOW = 0x00;			// 40013 - 40001
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_HIGH = 0x0C;
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SET_SYSTEM_TIME_LOW = 0x00;		// 00004 - 1

    explicit WriteSystemTimeRequest(uint8_t slave_address, uint8_t* request_data)
        : ModbusRequest(slave_address)
    {
        _request_buffer[1] = FUNCTION_CODE_WRITE_SINGLE_COIL;
		_request_buffer[2] = REGISTER_ADDRESS_WRITE_SYSTEM_TIME_LOW;
		_request_buffer[3] = REGISTER_ADDRESS_WRITE_SET_SYSTEM_TIME_LOW;
		_request_buffer[4] = request_data[0];
		_request_buffer[5] = request_data[1];
		_request_buffer[6] = request_data[2];
		_request_buffer[7] = request_data[3];
    }
};

class SetGasUnitsRequest : public ModbusRequest<6, WriteSingleRegResponse>
{
public:
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_LOW = 0x00;			// 40013 - 40001
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_HIGH = 0x0C;
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SET_SYSTEM_TIME_LOW = 0x00;		// 00004 - 1

    explicit SetGasUnitsRequest(uint8_t slave_address)
        : ModbusRequest(slave_address)
    {
        _request_buffer[1] = FUNCTION_CODE_WRITE_SINGLE_COIL;
		_request_buffer[2] = REGISTER_ADDRESS_WRITE_SYSTEM_TIME_LOW;
		_request_buffer[3] = REGISTER_ADDRESS_WRITE_SET_SYSTEM_TIME_LOW;
		_request_buffer[4] = 0x01;
		_request_buffer[5] = 0x00;
    }
};