#pragma once

#include "ModbusInterface.hpp"

class PX4ModbusInterface : public ModbusInterface
{
public:
    PX4ModbusInterface() {}
    ~PX4ModbusInterface() {}

    int32_t send(uint8_t* data, uint32_t num_bytes_to_send) override;
    int32_t receive(uint8_t* data, uint32_t num_bytes_to_receive) override;
};