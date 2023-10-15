/**
 * @file main.cpp
 * 
 * @brief Example of how to make a Modbus request using the interface.
 * 
 * @author Jesse B
 */

#include <iostream>
#include <chrono>
#include <thread>

#include "Gastech/UartModbusInterface.h"
#include "Gastech/GastechModbusRequests.h"

void get_time_data(uint8_t* data);

int main(void)
{
    // Create the interface that will send/receive the Modbus data.
    UartModbusInterface interface;

    // Make the Modbus request using the interface.
    static constexpr uint8_t slave_address = 0x08;
    SetGasUnitsRequest gas_unit_request = SetGasUnitsRequest(slave_address);
    bool success = gas_unit_request.make(interface);
    if(success)
    {
        WriteSingleRegResponse response = gas_unit_request.get_response();
        std::cout << "Response: " << unsigned(response.data_0) << std::endl;
    }

    // Secondary request passing runtime data
    uint8_t time_data[4];
    get_time_data(time_data);
    WriteSystemTimeRequest sys_time_request = WriteSystemTimeRequest(slave_address, time_data);
    sys_time_request.make(interface);

    return 0;
}

void get_time_data(uint8_t* data)
{
    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto end = std::chrono::system_clock::now();
 
    auto elapsed_seconds = end - start;
    auto secs = std::chrono::duration_cast<std::chrono::duration<float>>(elapsed_seconds);
    *(uint32_t*)&data[0] = static_cast<uint32_t>(secs.count());
}

/*** end of file ***/