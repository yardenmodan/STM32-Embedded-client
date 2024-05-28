#include <stdio.h>
#include "program.h"
#include "getUserInput.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


void getUserInput(user_input_packet* input) {
	
	packet_field field_iter=TEST_ID;
	uint32_t temp_num_iter=0;
	int result=0;
	while( field_iter++<PACKET_FIELDS_NUM ){

	
		switch (field_iter) {
			

			case PERIPHERAL:
				do {
					memset(input->Peripheral_name, 0, 7);

					printf("Please enter valid Peripheral name (Timer, ADC, SPI, I2C, UART) or type 'quit' to exit:\n");

					fgets(input->Peripheral_name, 7,stdin);
					

				}
				while(strcmp(input->Peripheral_name, "Timer\n")!=0 && \
					  strcmp(input->Peripheral_name, "ADC\n"  )!=0 && \
					  strcmp(input->Peripheral_name, "SPI\n"  )!=0 && \
					  strcmp(input->Peripheral_name, "I2C\n"  )!=0 && \
					  strcmp(input->Peripheral_name, "UART\n" )!=0 && \
					  strcmp(input->Peripheral_name, "quit\n" ));

				if (strcmp(input->Peripheral_name, "quit\n")==0){
					exit(EXIT_SUCCESS);
				}
				int len=strlen(input->Peripheral_name);//success//strlen takes also \n
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

					printf("Please enter a valid positive number of iterations to run (256 iterations tops):\n");
					result= scanf("%u",&temp_num_iter );
					clearInputBuffer();
				}
				while( result < 1 || temp_num_iter<0 || temp_num_iter>256 || temp_num_iter<0);
				uint8_t temp_array[20]={0};
				int chars_written= snprintf(input->iter_nums_str, sizeof(input->iter_nums_str), "%u" ,temp_num_iter);
				
				break;

			case PATTERN_LEN:
				continue;
			

			case STR:

				do{

					if (strcmp(input->Peripheral_name, "Timer")==0){
						printf("Please enter time for timer:\n");
						
						}
					
					else if (strcmp(input->Peripheral_name, "ADC")==0){
						printf("Please enter a digital value for ADC:\n");
					}
					else{

						printf( "Please enter a message (256 characters tops):\n");
					}
					while (getchar()!='\n') {}
					if (fgets(input->str, 256,stdin)!=NULL){
						input->message_len_str= strlen((const uint8_t *)input->str);
						
					}
				}
				while(!isValidInput(input->Peripheral_name, input->str));
				break;

			default:
				break;
		}
	}



}
int isValidInput(uint8_t * Peripheral_name, uint8_t * str){
	if (strcmp(Peripheral_name, "Timer")==0 || strcmp(Peripheral_name,"ADC")==0){
		for (int i=0; i<strlen(str)-1;i++){
			if (!isdigit(str[i])){
				printf("Please enter valid number!\n");
				return 0;
			}
		
		}
		return 1;
	}
	else{
		return 1;
	}

}


		
		
		

void clearInputBuffer() {
	scanf("%*[^\n]");
}
