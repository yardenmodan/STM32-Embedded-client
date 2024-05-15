
#include "program.h"
#include <string.h>
#define ADC 16
#define TIMER 1
#define I2C 8
#define SPI 4
#define UART 2
void translateStringsToPacket(packet_from_client* msg_packet, user_input_packet* input, uint32_t TestID) {
    msg_packet->TestID = TestID; // add error handling!
    if (strcmp(input->Peripheral_name,"ADC")==0){
        msg_packet->Peripheral = ADC;
    }
    if (strcmp(input->Peripheral_name,"Timer")==0){
        msg_packet->Peripheral = TIMER;
    }
    if (strcmp(input->Peripheral_name,"I2C")==0){
        msg_packet->Peripheral = I2C;
    }
    if (strcmp(input->Peripheral_name,"SPI")==0){
        msg_packet->Peripheral = SPI;
    }
    if (strcmp(input->Peripheral_name,"UART")==0){
        msg_packet->Peripheral = UART;
    }

    msg_packet->iter_num = (uint8_t)strtol(input->iter_nums_str, (char **)NULL, 10); // add error handling!
    msg_packet->pattern_len = input->message_len_str;
    strncpy(msg_packet->str, input->str, 256);
}
