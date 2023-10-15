/**
 * @file main.cpp
 * 
 * @brief Example of how to make a Modbus request using the interface.
 * 
 * @author Jesse B
 */

#include <iostream>

#include "Gastech/UartModbusInterface.h"
#include "Gastech/GastechModbusRequests.h"

int main(void)
{
    // Create the interface that will send/receive the Modbus data.
    UartModbusInterface interface;

    // Make the Modbus request using the interface.
    static constexpr uint8_t slave_address = 0x08;
    SetGasUnitsRequest request = SetGasUnitsRequest(slave_address);
    bool success = request.make(interface);
    if(success)
    {
        WriteSingleRegResponse response = request.get_response();
        std::cout << "I got a response: " << unsigned(response.data_0) << std::endl;
    }

    return 0;
}

/*** end of file ***/