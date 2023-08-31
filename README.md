## Problem
This was a learning exercise prompted by a challenge at work. We were working on 
integrating a new sensor that utilised MODBUS over RS-485. MODBUS operates by sending 
a request to a slave address and reading the returned response.
<br>
The tricky part of this problem was thatthe requests themselves were varying
lengths and had varying data which was in some cases static and other cases
required runtime data. Additionally, the responses were also varying length.
Due to this code running on a embedded device, there was no STL containers
such as vector or array and dynamic allocation was not allowed.
<br>
## Constraints
The following constratins where imposed:
- The interface used to send/receive the request/response data to the device needed to be flexible.
because MODBUS can be used over different communication buses such as CANBUS, Etherenet or RS-484.

- Defining new requests had to be easy and done via extension not modification. 

- Messages has to be flexible to allow passing in of run-time data if required.

- The response had to be pack into and returned as a struct for that particualr response type.

- Send/receive buffers could not exceed the actual request/response size for the particular
message being sent.

- Cannot use stl vector or array as it wasn't available on the particular embedded device

- No dynamic allocation allowed - typically avoided on embedded devices.

## Solution
Knowing the message that needed sending at runtime, the length of the request array,
the length of the response array and the response struct type was known. This made
a perfect case for templates to provide compile-time polymorphism. 
<br>
A virtual base class ModbusRequest was defined to take in two template arguments,
the REQUEST_SIZE and the response struct type which was used to determine the response size.
<br>
Concrete child classe were then defined for all requests that were to be made to 
the sensor. Each child class simply passed in the required template arguments as a
part of it's definition. Any static request data was assigned in the constuctor
and runtime data could be passed in on consctruction.
<br>
The request and response was performed through the message class itself,
by passing in a reference to the interface. 
<br>
The interface itself was a very simple virtual base class with send and receive 
functions. A concrete child class for a PX4 UART inteface was defined and used
to send and receive. Seeing as this wasn't running on target, stdout was used
to test the correct return data which was filled with mock data within the PX4 
receive function.


