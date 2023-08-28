
#include <stdint.h>
#include <cstring>

namespace Engine
{

class ModbusRequest
{
public:
    static constexpr uint8_t FUNCTION_CODE_READ_INPUT_REG = 0x04;
    static constexpr uint8_t FUNCTION_CODE_WRITE_SINGLE_COIL = 0x04;
    static constexpr uint8_t FUNCTION_CODE_WRITE_SINGLE_REG = 0x06;

    ModbusRequest(uint8_t slave_address, uint8_t request_length)
        : _slave_address(slave_address)
        , _request_length(request_length)
    { 
        _request_buffer[0] = _slave_address;
    }

    virtual ~ModbusRequest() {};

    uint8_t GetRequestLength() const { return _request_length; }
    uint8_t* GetRequestBuffer() const { return (uint8_t*)&_request_buffer[0]; }
protected:
    static constexpr uint8_t MAX_MODBUS_REQUEST = 8;
    uint8_t _request_buffer[MAX_MODBUS_REQUEST];

private:
    uint8_t _slave_address{0};
    const uint8_t _request_length;
};

struct __attribute__((__packed__)) responseWriteSingleReg {
	uint8_t slaveAddress;
	uint8_t functionCode;
	uint8_t regAddressLow;
	uint8_t regAddressHigh;
	uint8_t data_0;
	uint8_t data_1;
	uint16_t crc_16;
};

class WriteSystemTimeRequest : public ModbusRequest
{
public:
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_LOW = 0x00;			// 40013 - 40001
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SYSTEM_TIME_HIGH = 0x0C;
    static constexpr uint8_t REGISTER_ADDRESS_WRITE_SET_SYSTEM_TIME_LOW = 0x00;		// 00004 - 1
    static constexpr uint8_t request_length = 10;

    WriteSystemTimeRequest(uint8_t slave_address, uint8_t* request_data)
        : ModbusRequest(slave_address, request_length)
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


class ModbusInterface
{
public:
    ModbusInterface() = default;
    virtual ~ModbusInterface() {}

    virtual void make_request(const ModbusRequest& request) = 0;
    virtual void get_response(void* data, uint32_t num_bytes_to_receive) = 0;
};

class PX4ModbusInterface : public ModbusInterface
{
public:
    PX4ModbusInterface() {}
    ~PX4ModbusInterface() {}

    void make_request(const ModbusRequest& request) override;
    void get_response(void* data, uint32_t num_bytes_to_receive) override;
private:
    void add_crc_to_request(uint8_t data[], uint8_t insertion_index)
    {
        // Include crc calc in request
        //uint16_t crc_16 = crc16_calc(_request_buffer, _request_length);
        uint16_t crc_16 = 0;
        *(uint16_t*)&data[insertion_index] = crc_16 | crc_16 >> 8;
    }
};
} // namespace Engine
