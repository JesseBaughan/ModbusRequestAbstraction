#include "UartModbusInterface.hpp"

void add_crc_to_request(uint8_t* buffer, uint8_t insertion_index);

int32_t UartModbusInterface::send(uint8_t* data, uint32_t num_bytes_to_send)
{
    add_crc_to_request(data, num_bytes_to_send - 2);

    // Here we would send the data via interface

    return num_bytes_to_send;
}

void add_crc_to_request(uint8_t* buffer, uint8_t insertion_index)
{
    // Crc value is a dummy value for now.
    uint16_t crc_16 = 183;
    *(uint16_t*)&buffer[insertion_index] = crc_16 | crc_16 >> 8;
}

int32_t UartModbusInterface::receive(uint8_t* data, uint32_t num_bytes_to_receive)
{
    // Here we would grab the data from the interface.
    // Instead we are fill output with dummy data for testing purposes.
    for(int i = 0; i < num_bytes_to_receive; i++)
    {
        data[i] = 5;
    }

    return num_bytes_to_receive;
}