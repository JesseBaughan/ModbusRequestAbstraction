/**
 * @file ModbusRequest.h
 *
 * @brief Base class for Modbus requests. Specific requests
 * publicly inherit from this class.
 * 
 * @author Jesse B 
 */

#ifndef MODBUS_REQUEST_H_
#define MODBUS_REQUEST_H_

#include <stdint.h>
#include "ModbusInterface.h"

template<int REQUEST_LENGTH, typename ResponseType>
class ModbusRequest
{
public:
    static constexpr uint8_t FUNCTION_CODE_READ_INPUT_REG = 0x04;
    static constexpr uint8_t FUNCTION_CODE_WRITE_SINGLE_COIL = 0x04;
    static constexpr uint8_t FUNCTION_CODE_WRITE_SINGLE_REG = 0x06;

    virtual bool make(ModbusInterface& interface)
    {
        interface.send(_request_buffer, _request_length);
        interface.receive((uint8_t*)&_response_data, _response_length);
        return true;
    }

    ResponseType get_response()
    {
        return _response_data;
    }

protected:
    explicit ModbusRequest(uint8_t slave_address)
        : _slave_address(slave_address)
        , _request_length(REQUEST_LENGTH)
        , _response_length(sizeof(ResponseType)) 
    {
        // First element of request buffer is always the slave address.
        _request_buffer[0] = _slave_address;
    }

    virtual ~ModbusRequest() {};

    uint8_t _request_buffer[REQUEST_LENGTH] = {};
    ResponseType _response_data{};

private:
    uint8_t _slave_address;
    uint8_t _request_length;
    uint8_t _response_length;
};

#endif /* MODBUS_REQUEST_H_ */

/*** end of file ***/