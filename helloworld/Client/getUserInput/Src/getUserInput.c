#include <stdio.h>
#include "program.h"
#include "getUserInput.h"
#include <string.h>


void getUserInput(user_input_packet* input) {
	
	packet_field field_iter=TEST_ID;
	uint32_t temp_num_iter=0;
	int result=0;
	while( field_iter++<PACKET_FIELDS_NUM )

	
		switch (field_iter) {
			

			case PERIPHERAL:
				do {
					memset(input->Peripheral_name, 0, 7);

					printf("Please enter valid Peripheral name (Timer, ADC, SPI, I2C, UART):\n");
					fgets(input->Peripheral_name, 6,stdin);
					clearInputBuffer();

				}
				while(strcmp(input->Peripheral_name, "Timer\n")!=0 && \
					  strcmp(input->Peripheral_name, "ADC\n"  )!=0 && \
					  strcmp(input->Peripheral_name, "SPI\n"  )!=0 && \
					  strcmp(input->Peripheral_name, "I2C\n"  )!=0 && \
					  strcmp(input->Peripheral_name, "UART\n" )!=0 );

				
				int len=strlen(input->Peripheral_name);//success
				if (len>0 && input->Peripheral_name[len-1]=='\n'){
					input->Peripheral_name[len-1]='\0';
				}
				
				else{
					//error occoured
				}
				break;

			case ITER_NUM:
				do {
					memset(input->iter_nums_str, 0, 4);
					clearInputBuffer();

					printf("Please enter a valid positive number of iterations to run (256 iterations tops):\n");
					result= scanf("%u",&temp_num_iter );
				}
				while( result < 1 || temp_num_iter<0 || temp_num_iter>256 || temp_num_iter<0);
				uint8_t temp_array[20]={0};
				int chars_written= snprintf(input->iter_nums_str, sizeof(input->iter_nums_str), "%u" ,temp_num_iter);
				
				break;

			case PATTERN_LEN:
				continue;
			

			case STR:
				clearInputBuffer();
				printf( "Please enter a message (256 characters tops):\n");
				if (fgets(input->str, 256,stdin)!=NULL){
					input->message_len_str= strlen((const uint8_t *)input->str);
					//success
				}
				else{
					//error occoured
				}
				break;

			default:
				break;
		}
		field_iter++;


}
	

		
		
		

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}
