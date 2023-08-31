CC=g++
CFLAGS= -g -Wall

modbus_test: px4_interface.o main.o
	g++ -o modbus_test PX4UartModbusInterface.o main.o

px4_interface.o: PX4UartModbusInterface.cpp PX4UartModbusInterface.hpp ModbusInterface.hpp
	g++ -c PX4UartModbusInterface.cpp

main.o: main.cpp GastechModbusRequests.hpp ModbusRequest.hpp PX4UartModbusInterface.hpp
	g++ -c main.cpp