#pragma once

#include <stdint.h>

class ModbusInterface
{
public:
    ModbusInterface() = default;
    virtual ~ModbusInterface() {}

    virtual int32_t send(uint8_t* data, uint32_t num_bytes_to_send) = 0;
    virtual int32_t receive(uint8_t* data, uint32_t num_bytes_to_receive) = 0;
};
