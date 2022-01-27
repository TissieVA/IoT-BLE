# Bluetooth Low Power

## Initialization

We started from the example called [ble_app_uart](https://github.com/TissieVA/IoT-BLE/tree/master/nRF5_SDK_17.1.0_ddde560/nRF5_SDK_17.1.0_ddde560/examples/ble_peripheral/ble_app_uart).

To start off our own BLE project we set the device_name, UART Buffer size and other variables important for BLE.

![Defines](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/beginningDefines.jpg)

### Main

The main function start by calling all the init functions, after this the advertising phase starts.

![main](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/main.jpg)

## Inits

### Initialization of timers
timers_init initiliazes the timer we will be using for the app. 

"foto timers_init"

![timers](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/Timers_init.png)

### Services
In the services_init function we initilialize the services we are going to use for the Bluetooth connection between the OCTA and a smartphone. For example the nus will be initiated in this function. 

![services_init](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/services_init.png)

### Connection parameters
In conn_params_init we initialize the parameters for the Connection module. We set the update delays for our parameters and the maximum update count of our parameters. 

![conn_params_init](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/conn_params_init.png)

### GAP
In gap_params_init we initialize the General Access Profile which is used by BLE for advertising and connecting purposes. Here we set the slave_latency, connection intervals and timeouts.

![gap_params_init](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/gap_params_init.png)

### GATT
In gatt_init we initialize the Generic Attribute Profile library.

![gatt_init](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/gatt_init.png)

### Bluetooth stack
In ble_stack_init we intialize the SoftDevice and the BLE event interrupt.

![ble_stack_init](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/ble_stack_init.png)

### UART
The uart_init function sets the parameters used to send data over the UART, for example the pins the BLE chip need to send the data over. In [pca10040.h](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/nRF5_SDK_17.1.0_ddde560/components/boards/pca10040.h) we defined the pins for the OCTA, RX pin 26 and TX pin 27. Another parameter initiated here is the baudrate, this is important because UART won't work if the receiving and sending side aren't using the same baudrate.

![uart_init](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/uart_init.png)

### Advertising
In advertising_init we initialize the advertising functionality of our BLE module. We set the advertising name, start fast advertising and initialize an event handler for advertising.  

![advertising_init](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/advertising_init.png)

### NRF logging
In log_init we initialize our NRF log module which we use to debug our NRF events. 

![log_init](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/log_init.png)

### Power management
In power_management_init we initialize the power management function. 

## Handlers 

### UART data handler 
In nus_data_handler we handle the data which was received via BLE and send it to the UART module. We use a for loop to place the received data in a buffer which we then put on the UART using app_uart_put. 

![nus_data_handler](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/nus_data_handler.png)

### Error handler 
In nrf_qwr_error_handler we handle our nrf_errors using APP_ERROR_HANDLER

![nrf_qwr_error](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/nrf_qwr_error.png)

### Advertising event handler
In on_adv_evt we handle the advertising events. When our device receives an event that it should fast advertise then it will indicate that it is advertising. When our BLE module goes into idle state it will call the sleep_mode_enter function and go to sleep.

![on_adv_evt](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/on_adv_evt.png)

### Bluetooth event handler
In ble_evt_handler we handle the BLE events. When a device connects to the BLE chip it will send a message over the UART saying that a device has been connected, same for disconnecting.

![ble_evt_handler](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/ble_evt_handler.png)

### GATT event handler
In gatt_evt_handler we handle the events from the GATT library 

![gatt_evt_handler](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/gatt_evt_handler.png)


## Energy efficiency

### Entering sleep mode
We use sleep_mode_enter as our function to go in to sleep mode when our BLE device has stopped advertising and is in idle mode. 

![sleep_mode_enter](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/sleep_mode_enter.png)

### Idle state
In idle_state_handle we look if there is a pending log operation, if this is not the case we will go to sleep until the next event occurs. 

![idle_state_handle](https://github.com/TissieVA/IoT-BLE/blob/master/nRF5_SDK_17.1.0_ddde560/BLE_docs/images/ble_evt_handler.png)

