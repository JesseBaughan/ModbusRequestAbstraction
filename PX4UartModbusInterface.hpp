#pragma once

#include "ModbusInterface.hpp"

class PX4ModbusInterface : public ModbusInterface
{
public:
    PX4ModbusInterface() {}
    ~PX4ModbusInterface() {}

    int32_t send(void* data, uint32_t num_bytes_to_send) override;
    int32_t receive(void* data, uint32_t num_bytes_to_receive) override;
};