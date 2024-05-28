#ifndef USER_INPUT_H
#define USER_INPUT_H
#include "program.h"
void clearInputBuffer();
int isValidInput(uint8_t * Peripheral_name, uint8_t * str);

void getUserInput(user_input_packet* input);

#endif  // USER_INPUT_H
