/* 
 * File:   serial_to_can.c
 * Author: Gerke Kooistra
 *
 * Created on 20 april 2019, 20:59
 */

#include "can_to_serial.h"
#include "mcc_generated_files/can_types.h"


static void NibbleToChar (unsigned char hexValue, char *c){
    // Convert integer to hexadecimal character
    *c = 0x30 + ((hexValue) & 0x0F);
    if (*c > 0x39) 
    {
        // Add 7 for chars A till F
        *c += 0x07;
    }
}

void CTS_CanMsgToString  (uCAN_MSG *recCanMsg, char *string) {      
    uint8_t data_index = 0;
    
    // Convert the CAN message identifier to three hexadecimal characters
    NibbleToChar((recCanMsg->frame.id >> 8) & 0xF, string);
    string++;
    
    NibbleToChar((recCanMsg->frame.id >> 4) & 0xF, string);
    string++;
    
    NibbleToChar((recCanMsg->frame.id >> 0) & 0xF, string);
    string++;
    
    // Convert the CAN message data
    while (data_index != recCanMsg->frame.dlc) {
        
        NibbleToChar((recCanMsg->array[7 + data_index] >> 4) & 0xF, string);
        string++;
        
        NibbleToChar((recCanMsg->array[7 + data_index] >> 0) & 0xF, string);
        string++;
        
        data_index++;
    }
    
    // Add newline character indicating end of CAN message and 0 string terminator
    *string = '\n';
    string++;
    *string = '\0';
}
