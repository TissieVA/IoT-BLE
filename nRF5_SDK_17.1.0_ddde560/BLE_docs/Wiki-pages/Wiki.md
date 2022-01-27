# Bluetooth Low Power

## Initialization

We started from the example called [ble_app_uart](https://github.com/TissieVA/IoT-BLE/tree/master/nRF5_SDK_17.1.0_ddde560/nRF5_SDK_17.1.0_ddde560/examples/ble_peripheral/ble_app_uart).

To start off our own BLE project we set the device_name, UART Buffer size and other variables important for BLE.

"foto includes en defines"

## Inits

### Initialization of timers
timers_init initiliazes the timer we will be using for the app. 

"foto timers_init"

[[BLE_Docs/images/star.jpg]]

### Services
In the services_init function we initilialize the services we are going to use for the Bluetooth connection between the OCTA and a smartphone. For example the nus will be initiated in this function. 

"foto services_init"

### Connection parameters
In conn_params_init we initialize the parameters for the Connection module. We set the update delays for our parameters and the maximum update count of our parameters. 

"foto conn_params_init"

### GAP
In gap_params_init we initialize the General Access Profile which is used by BLE for advertising and connecting purposes. Here we set the slave_latency, connection intervals and timeouts

"foto gap_params_init"

## Handlers 

### UART data handler 
iIn nus_data_handler we handle the data which was received via BLE and send it to the UART module. We use a for loop to place the received data in a buffer which we then put on the UART using app_uart_put. 

"foto nus_data_handler"

### Error handler 
In nrf_qwr_error_handler we handle our nrf_errors using APP_ERROR_HANDLER

## Energy efficiency

### Entering sleep mode
We use sleep_mode_enter as our function to go in to sleep mode when our BLE device has stopped advertising and is in idle mode. 


