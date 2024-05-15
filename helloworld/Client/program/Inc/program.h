#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdint.h>

#define TESTID_LEN 4

#define MAX_MSG_SIZE 255
#define SERVER_PORT 8080
#define CLIENT_PORT 8080
#define CLOCKS_PER_SEC 1000
#define TESTID_LEN 4


typedef struct __attribute__((__packed__)){
    uint8_t Test_ID_str[11] ;
    uint16_t message_len_str ;
    uint8_t iter_nums_str[4] ;
    uint8_t Peripheral_name[7] ;
    uint8_t str[MAX_MSG_SIZE + 1] ;
}user_input_packet;

typedef struct __attribute__((__packed__)) {
    uint32_t TestID;
    uint8_t Peripheral;
    uint8_t iter_num;
    uint8_t pattern_len;
    uint8_t str[MAX_MSG_SIZE];
} packet_from_client;

typedef struct __attribute__((__packed__)) {
    uint32_t TestID;
    uint8_t TestResult;
} packet_to_client;

typedef enum {
    TEST_ID,
    PERIPHERAL,
    ITER_NUM,
    PATTERN_LEN,
    STR,
	PACKET_FIELDS_NUM
} packet_field;



void getUserInput(user_input_packet* input) ;
void translateStringsToPacket(packet_from_client* msg_packet, user_input_packet* input, uint32_t TestID);
void sendTestUDP(char* serializedPacket);

#endif  // MAIN_H
