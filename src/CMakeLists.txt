cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(ModbusRequest VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    Gastech/UartModbusInterface.cpp    
    main.cpp    
)

# add the executable
add_executable(ModbusRequest ${SOURCES})