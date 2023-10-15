/**
 * @file ModbusInterface.h
 *
 * @brief Base class for the interface used to send/receive 
 * the Modbus requests. This class is used by Modbus requests
 * class to send/receive the data to/from the Modbus device.
 * 
 * @author Jesse B
 */

#ifndef MODBUS_INTERFACE_H_
#define MODBUS_INTERFACE_H_

#include <stdint.h>

class ModbusInterface
{
public:
    ModbusInterface() = default;
    virtual ~ModbusInterface() {}

    virtual int32_t send(uint8_t* data, uint32_t num_bytes_to_send) = 0;
    virtual int32_t receive(uint8_t* data, uint32_t num_bytes_to_receive) = 0;
};

#endif /* MODBUS_INTERFACE_H_ */

/*** end of file ***/