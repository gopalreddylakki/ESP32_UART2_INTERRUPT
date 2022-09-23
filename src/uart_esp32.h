#include <Arduino.h>
#include "driver/uart.h"
  void   recdata(String daaa);
//extern TinyGsm        modem(SerialAT);
 //extern TinyGsmClient  client(modem); 
 //void   recdata(uint8_t UART2_data[128]);
#define NUMERO_PORTA_SERIALE UART_NUM_2
#define BUF_SIZE (1024 * 2)
#define RD_BUF_SIZE (1024)
static QueueHandle_t uart2_queue;
/// Created by gopalreddy form sytiqhub
static const char * TAG = "";                  
 
#define U2RXD 16
#define U2TXD 17
 
uint8_t rxbuf[256];     //Buffer di ricezione
uint16_t rx_fifo_len;        //Lunghezza dati
 static void UART_ISR_ROUTINE(void *pvParameters)
{
    uart_event_t event;
    size_t buffered_size;
    bool exit_condition = false;
   
    //Infinite loop to run main bulk of task
    while (1) {
     
        //Loop will continually block (i.e. wait) on event messages from the event queue
        if(xQueueReceive(uart2_queue, (void * )&event, (portTickType)portMAX_DELAY)) {
         
            //Handle received event
            if (event.type == UART_DATA) {
 
                uint8_t UART2_data[128];
                int UART2_data_length = 0;
                ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_2, (size_t*)&UART2_data_length));
                UART2_data_length = uart_read_bytes(UART_NUM_2, UART2_data, UART2_data_length, 100);
             
                //Serial.println("LEN= ");Serial.println(UART2_data_length);
                String daaa="";
               // Serial.print("DATA= ");
               
                for(byte i=0; i<UART2_data_length;i++) 
                    {daaa+=char(UART2_data[i]);
                        //Serial.print((char)UART2_data[i]);
                    }
                recdata(daaa);
               // Serial.println("");
             
            }
           
            //Handle frame error event
            else if (event.type == UART_FRAME_ERR) {
                //TODO...
            }
           
            //Keep adding else if statements for each UART event you want to support
            //else if (event.type == OTHER EVENT) {
                //TODO...
            //}
           
           
            //Final else statement to act as a default case
            else {
                //TODO...
            }      
        }
       
        //If you want to break out of the loop due to certain conditions, set exit condition to true
        if (exit_condition) {
            break;
        }
    }
   
    //Out side of loop now. Task needs to clean up and self terminate before returning
    vTaskDelete(NULL);
}

/// Created by gopalreddy form sytiqhub
void send_data(char* test_str)
{

uart_write_bytes(UART_NUM_2, (const char*)test_str, strlen(test_str));
   // const uart_port_t uart_num = UART_NUM_2;
ESP_ERROR_CHECK(uart_wait_tx_done(UART_NUM_2, 100)); 
}