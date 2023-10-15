CC=g++
CFLAGS= -g -Wall

modbus_test: px4_interface.o main.o
	g++ -o modbus_test UartModbusInterface.o main.o

px4_interface.o: UartModbusInterface.cpp UartModbusInterface.hpp ModbusInterface.hpp
	g++ -c UartModbusInterface.cpp

main.o: main.cpp GastechModbusRequests.hpp ModbusRequest.hpp UartModbusInterface.hpp
	g++ -c main.cpp