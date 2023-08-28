#include "test_two.hpp"

namespace Engine
{

void PX4ModbusInterface::make_request(const ModbusRequest& request)
{
    add_crc_to_request(request.GetRequestBuffer(), request.GetRequestLength() - 2);
    
    //PX4 send functio
}

void PX4ModbusInterface::get_response(void* data, uint32_t num_bytes_to_receive)
{
    //PX4 recieve function
}

}