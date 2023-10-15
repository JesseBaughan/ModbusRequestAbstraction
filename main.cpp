#include <iostream>

#include "UartModbusInterface.hpp"
#include "GastechModbusRequests.hpp"

int main(void)
{
    PX4ModbusInterface interface;
    static constexpr uint8_t slave_address = 0x08;

    SetGasUnitsRequest request = SetGasUnitsRequest(slave_address);
    request.make(interface);
    WriteSingleRegResponse response = request.get_response(interface);

    std::cout << "I got a response: " << unsigned(response.data_0) << std::endl;

    return 0;
}