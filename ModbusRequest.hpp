#include <stdint.h>
#include "ModbusInterface.hpp"

template<int REQUEST_LENGTH, typename ResponseType>
class ModbusRequest
{
public:
    static constexpr uint8_t FUNCTION_CODE_READ_INPUT_REG = 0x04;
    static constexpr uint8_t FUNCTION_CODE_WRITE_SINGLE_COIL = 0x04;
    static constexpr uint8_t FUNCTION_CODE_WRITE_SINGLE_REG = 0x06;

    explicit ModbusRequest(uint8_t slave_address)
        : _slave_address(slave_address)
        , _request_length(REQUEST_LENGTH)
        , _response_length(sizeof(ResponseType)) {}

    virtual ~ModbusRequest() {};

    virtual bool make(ModbusInterface& interface)
    {
        interface.send(_request_buffer, _request_length);
        interface.receive((void*)&_return_data, _response_length);

        return true;
    }

    ResponseType get_response()
    {
        return _return_data;
    }

protected:
    uint8_t _request_buffer[REQUEST_LENGTH];
    ResponseType _return_data;

private:
    uint8_t _slave_address;
    uint8_t _request_length;
    uint8_t _response_length;
};

