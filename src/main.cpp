#include <iostream>

#include "Gastech/UartModbusInterface.hpp"
#include "Gastech/GastechModbusRequests.hpp"

int main(void)
{
    UartModbusInterface interface;
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