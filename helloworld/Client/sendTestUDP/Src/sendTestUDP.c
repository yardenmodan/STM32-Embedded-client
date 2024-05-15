#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "assert.h"
#include <errno.h>
#include "program.h"

/* things to fix:
test id prngitning
inputs correctness
*/
#define MSG_LEN 264
#define CLIENT_PORT 6000
#define SERVER_PORT 5000 
#define TRUE_TEST  0
#define FALSE_TEST 0
//sending exactly 264 bytes
void sendTestUDP(char serializedPacket[]) {
    
   

    int sockfd;
    
    struct sockaddr_in server_addr;
    socklen_t clientlen=sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // Create a socket for UDP communication
    if (sockfd <0 ) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
//192.168.007.002
    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("192.168.007.002");//192.168.7.2//); //
    
    

    clock_t start_time = clock();
    time_t current_time = time(NULL);
    struct tm* local_time = localtime(&current_time);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
    int send_error=0;
    while (1){


        send_error=sendto(sockfd, serializedPacket, MSG_LEN, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        if (send_error<0) {
            printf("error: %d", errno);
            perror("Sendto failed!\r\n");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        if (send_error>0){
            printf("data was sent!\n");
            break;
        }
    }

    printf("UDP packet send successfully!\r\n");

    

    size_t bytes_received = 0;
    uint8_t receivedPacket[5] = {0};
    bytes_received = recvfrom(sockfd, receivedPacket, sizeof(receivedPacket),0, (struct sockaddr*)&server_addr, &clientlen);
    if (bytes_received < 0) {
        printf("error is : %d, errno: %d \r\n",bytes_received, errno);
        perror("Receiving failed!\r\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Send the message to the server
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC);
    printf("UDP packet received successfully!\r\n");
    packet_to_client received_packet = {0};
    memcpy(&received_packet.TestID, receivedPacket, sizeof(uint32_t));
    memcpy(&received_packet.TestResult, &receivedPacket[4], sizeof(uint8_t));
    char test_result[10] = {0};
    (received_packet.TestResult == 0x01U) ? strncpy(test_result, "Success", 8) : strncpy(test_result, "Failure", 8);
    #if FALSE_TEST
        assert(received_packet.TestResult==0x00U); 
    #endif
    #if TRUE_TEST
        assert(received_packet.TestResult==0x01U); 

    #endif
    // Take input and put it in a file
    FILE* file;
    if ((file = fopen("Test_Results.txt", "a")) == NULL) {
        perror("Error opening the file!");
        exit(EXIT_FAILURE);
    }
    //uint8_t str[100]={0};
    //sprintf(str,"%u",received_packet.TestID );
    fprintf(file, "Date: [%s], Time Taken: %.6f seconds, Test ID: %d, Result: %s \r\n", time_str, elapsed_time, received_packet.TestID, test_result);

    fclose(file);
    // Close the socket
    close(sockfd);
    
}
