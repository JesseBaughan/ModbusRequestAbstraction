
#include <stdint.h>
#include <cstring>

namespace Engine
{

class ModbusInterface
{
public:
    ModbusInterface() = default;
    virtual ~ModbusInterface() {}

    virtual void send(void* data, uint32_t num_bytes_to_send) = 0;
    virtual void get_response(void* data, uint32_t num_bytes_to_receive) = 0;
};

class PX4ModbusInterface : public ModbusInterface
{
public:
    PX4ModbusInterface() {}
    ~PX4ModbusInterface() {}

    void send(void* data, uint32_t num_bytes_to_send) override;
    void get_response(void* data, uint32_t num_bytes_to_receive) override;
};

template<typename T>
class ModbusRequest
{
public:
    static constexpr uint8_t FUNCTION_CODE_READ_INPUT_REG = 0x04;
    static constexpr uint8_t FUNCTION_CODE_WRITE_SINGLE_COIL = 0x04;
    static constexpr uint8_t FUNCTION_CODE_WRITE_SINGLE_REG = 0x06;

    ModbusRequest(uint8_t slave_address, uint8_t request_length, uint8_t response_length)
        : _slave_address(slave_address)
        , _request_length(request_length)
        , _response_length(response_length)
    { 
    }

    virtual ~ModbusRequest() {};

    void make(ModbusInterface& interface) 
    {
        _interface = &interface;
        _interface->send(_request_buffer, _request_length);
    }

    T get_response()
    {
        _interface->get_response(_response_buffer, _response_length);
        T output_struct;
        memcpy(&output_struct, (void *)_response_buffer, _response_length);
        return output_struct;
    }

protected:
    static constexpr uint8_t MAX_MODBUS_REQUEST = 16;
    static constexpr uint8_t MAX_MODBUS_RESPONSE = 16;
    uint8_t _response_buffer[MAX_MODBUS_RESPONSE];
    uint8_t _request_buffer[MAX_MODBUS_REQUEST];

private:
    uint8_t _slave_address;
    const uint8_t _request_length;
    const uint8_t _response_length;

    ModbusInterface* _interface;
};

struct __attribute__((__packed__)) ResponseWriteSingleReg {
	uint8_t slaveAddress;
	uint8_t functionCode;
	uint8_t regAddressLow;
	uint8_t regAddressHigh;
	uint8_t data_0;
	uint8_t data_1;
	uint16_t crc_16;
};

class WriteSystemTimeRequest : public ModbusRequest<ResponseWriteSingleReg>
{
public:
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_LOW = 0x00;			// 40013 - 40001
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_HIGH = 0x0C;
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SET_SYSTEM_TIME_LOW = 0x00;		// 00004 - 1
    static constexpr uint8_t request_length = 10;
    static constexpr uint8_t response_length = 10;

    WriteSystemTimeRequest(uint8_t slave_address, uint8_t* request_data)
        : ModbusRequest(slave_address, request_length, response_length)
    {
        _request_buffer[1] = FUNCTION_CODE_WRITE_SINGLE_COIL;
		_request_buffer[2] = REGISTER_ADDRESS_WRITE_SYSTEM_TIME_LOW;
		_request_buffer[3] = REGISTER_ADDRESS_WRITE_SET_SYSTEM_TIME_LOW;
		_request_buffer[3] = request_data[0];
		_request_buffer[4] = request_data[1];
		_request_buffer[5] = request_data[2];
		_request_buffer[6] = request_data[3];
    }
};

class SetGasUnitsRequest : public ModbusRequest<ResponseWriteSingleReg>
{
public:
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_LOW = 0x00;			// 40013 - 40001
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_HIGH = 0x0C;
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SET_SYSTEM_TIME_LOW = 0x00;		// 00004 - 1
    static constexpr uint8_t request_length = 8;
    static constexpr uint8_t response_length = 10;

    SetGasUnitsRequest(uint8_t slave_address)
        : ModbusRequest(slave_address, request_length, response_length)
    {
        _request_buffer[1] = FUNCTION_CODE_WRITE_SINGLE_COIL;
		_request_buffer[2] = REGISTER_ADDRESS_WRITE_SYSTEM_TIME_LOW;
		_request_buffer[3] = REGISTER_ADDRESS_WRITE_SET_SYSTEM_TIME_LOW;
		_request_buffer[4] = 0x01;
		_request_buffer[5] = 0x00;
    }
};
} // namespace Engine
