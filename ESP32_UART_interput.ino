#include "src/uart_esp32.h"
#include "driver/uart.h"
/// Created by gopalreddy form sytiqhub
// UART2 RECVIED DATA
  void   recdata(String ff)
  {

     Serial.print("UART2 REC:");
    Serial.println(ff);
  }
void setup() {
 
    Serial.begin(115200);

// Serial2.begin(115200);
    //Configuro la porta Serial2 (tutti i parametri hanno anche un get per effettuare controlli)
    uart_config_t Configurazione_UART2 = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(NUMERO_PORTA_SERIALE, &Configurazione_UART2);
    esp_log_level_set(TAG, ESP_LOG_INFO);
    //Firma: esp_err_tuart_set_pin(uart_port_tuart_num, int tx_io_num, int rx_io_num, int rts_io_num, int cts_io_num)
    uart_set_pin(NUMERO_PORTA_SERIALE, U2TXD, U2RXD, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    //Firma: uart_driver_install(UART_NUM_2, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
    //       uart_driver_install(Numero_porta, RXD_BUFFER, TXD_Buffer, event queue handle and size, flags to allocate an interrupt)
    uart_driver_install(NUMERO_PORTA_SERIALE, BUF_SIZE, BUF_SIZE, 20, &uart2_queue, 0);
    //Create a task to handler UART event from ISR
    xTaskCreate(UART_ISR_ROUTINE, "UART_ISR_ROUTINE", 2048, NULL, 12, NULL);
 
}
 
 
 
void loop() {

send_data("AT\n");
delay(5000);

  }
 
 
 
 