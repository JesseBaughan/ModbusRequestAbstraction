/**
 * @file UartModbusInterface.h
 *
 * @brief Concrete modbus interface class that defines the specific
 * send/recieve functions for the interface/hardware used to 
 * communicate with the Modbus device.
 * 
 * @author Jesse B 
 */

#ifndef UART_MODBUS_INTERFACE_H_
#define UART_MODBUS_INTERFACE_H_

#include "../ModbusInterface.h"

class UartModbusInterface : public ModbusInterface
{
public:
    UartModbusInterface() {}
    ~UartModbusInterface() {}

    int32_t send(uint8_t* data, uint32_t num_bytes_to_send) override;
    int32_t receive(uint8_t* data, uint32_t num_bytes_to_receive) override;
};

#endif /* UART_MODBUS_INTERFACE_H_ */

/*** end of file ***/