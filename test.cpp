#include "test.hpp"

namespace Engine
{

void add_crc_to_request(uint8_t* buffer, uint8_t insertion_index)
{
    // Include crc calc in request
    //uint16_t crc_16 = crc16_calc(_request_buffer, _request_length);
    uint16_t crc_16 = 0;
    *(uint16_t*)&buffer[insertion_index] = crc_16 | crc_16 >> 8;
}

void PX4ModbusInterface::send(void* data, uint32_t num_bytes_to_send)
{
    add_crc_to_request((uint8_t*)data, num_bytes_to_send - 2);
}

void PX4ModbusInterface::get_response(void* data, uint32_t num_bytes_to_receive)
{
    //Add some kind of delay

    // Read the data from the UART buffer and return it in data pointer
}
}