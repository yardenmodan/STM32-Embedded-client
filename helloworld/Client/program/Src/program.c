#include <stdio.h>
#include "program.h"
#include "string.h"
#include <stdlib.h>
#include <unistd.h>
#include "time.h"




int main() {
        /* ############# take inputs from user and generate fields of packet ############## */

        uint32_t TestID=0;
        packet_from_client msg_packet = {0};
        user_input_packet input ={0};

    while (1) {

        // this while loop receives input from user for each packet field
       
   
        getUserInput(&input);

        /* ############# translation of strings to packet fields ############## */

        translateStringsToPacket(&msg_packet, &input, TestID);

        /* ############# pack all fields into struct ############## */

        char serializedPacket[264] = {0};
        char receivedPacket[5] = {0};
        memcpy(serializedPacket, &msg_packet, sizeof(msg_packet));

        /* ############# send test across ethernet using udp ############## */
        sendTestUDP(serializedPacket);
        //        uint8_t* field_list[PACKET_FIELDS_NUM] = {Test_ID_str, Peripheral_name, iter_nums_str,message_len_str, str};

        /* ############# resetting field_list and msg_packet ############## */
        memset(&input,0,sizeof(input));
      
        memset(&msg_packet,0,sizeof(msg_packet));
        TestID++;
        
    }
    return 0;
}

