/**
 * @file GastechModbusRequests.h
 *
 * @brief Modbus requests for a Gastech sensor.
 * 
 * @author Jesse B 
 */

#ifndef GASTECH_MODBUS_REQUESTS_H_
#define GASTECH_MODBUS_REQUESTS_H_

#include "../ModbusRequest.h"

// We use __packed__ so we don't have data packing issues.
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
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_LOW = 0x00;			
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_HIGH = 0x0C;
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SET_SYSTEM_TIME_LOW = 0x00;		

    explicit WriteSystemTimeRequest(uint8_t slave_address, uint8_t* request_data)
        : ModbusRequest(slave_address)
    {
        // Must start at index 1 as 0 is used for slave address.
        // TODO: Should we implement method so that we can use 0 indexing?
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
    static constexpr uint8_t REGISTER_ADDRESS_READ_GAS_DATA_LOW = 0x00;			
    static constexpr uint8_t REGISTER_ADDRESS_READ_GAS_DATA_HIGH = 0x0B;

    explicit SetGasUnitsRequest(uint8_t slave_address)
        : ModbusRequest(slave_address)
    {
        _request_buffer[1] = FUNCTION_CODE_WRITE_SINGLE_COIL;
		_request_buffer[2] = REGISTER_ADDRESS_READ_GAS_DATA_LOW;
		_request_buffer[3] = REGISTER_ADDRESS_READ_GAS_DATA_HIGH;
		_request_buffer[4] = 0x01;
		_request_buffer[5] = 0x00;
    }
};

#endif /* GASTECH_MODBUS_REQUESTS_H_ */

/*** end of file ***/