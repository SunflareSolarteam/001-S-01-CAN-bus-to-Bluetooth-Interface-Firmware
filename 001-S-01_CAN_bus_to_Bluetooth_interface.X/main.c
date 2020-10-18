/**
 * File:   main.c
 * Author: Gerke Kooistra
 *
 * Created on 20 april 2019, 20:59
*/

/**
  Section: Included Files
*/
#include <xc.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/uart2.h"
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/can_types.h"
#include "can_to_serial.h"
#include <stdint.h>
#include <string.h>

// HC-05 Configuration.
// For this parameters to have effect the HC-05 module must be initialized by using the the jumper P5.
#define HC05_NAME       "SOLARBOAT"
#define HC05_PIN        "1234"

// Delay function
static void Delayms (uint16_t ms) {
    uint16_t i = 0;
    
    // Start 1ms timer
    TMR1_Start();
    // Loop ms times
    while(i < ms){
        // Proccess timer
        TMR1_Tasks_16BitOperation();
        // Check if timer has elapsed, increase counter
        if(TMR1_GetElapsedThenClear() == true){
            i++;
        }
    }
    // Stop the hardware timer
    TMR1_Stop();

    return;
}

void HC05_Initialize(void) {  
    char command_str[32];
    char debug_str[35];
    char response_str[32];
    int8_t response_length;
    
    // Turn led on indicating initialization in progress
    IO_LED_SetLow();  //LED on

    // Let the HC-05 complete the startup
    Delayms(2000);
    
    U1BRG = 0x186; // Reduce baudrate to 38400
    
    // Clear receive buffer
    response_length = UART1_ReadBuffer((uint8_t*)response_str, 32);
    
    // Check connection
    strcpy(command_str, "");
    strcat(command_str, "AT\r\n");
    UART1_WriteBuffer((uint8_t*)command_str, strlen(command_str));
    strcpy(debug_str, "> ");
    strcat(debug_str, command_str);
    UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    Delayms(500);
    response_length = UART1_ReadBuffer((uint8_t*)response_str, 32);
    if (response_length != -1) {
        response_str[response_length] = '\0';
        strcpy(debug_str, "< ");
        strcat(debug_str, response_str);
        strcat(debug_str, "\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    } else {
        strcpy(debug_str, "< ERROR\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    }
    
    // Check connection
    strcpy(command_str, "");
    strcat(command_str, "AT\r\n");
    UART1_WriteBuffer((uint8_t*)command_str, strlen(command_str));
    strcpy(debug_str, "> ");
    strcat(debug_str, command_str);
    UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    Delayms(500);
    response_length = UART1_ReadBuffer((uint8_t*)response_str, 32);
    if (response_length != -1) {
        response_str[response_length] = '\0';
        strcpy(debug_str, "< ");
        strcat(debug_str, response_str);
        strcat(debug_str, "\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    } else {
        strcpy(debug_str, "< ERROR\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    }
    
    // Reset the HC-05 to default
    strcpy(command_str, "");
    strcat(command_str, "AT+ORGL\r\n");
    UART1_WriteBuffer((uint8_t*)command_str, strlen(command_str));
    strcpy(debug_str, "> ");
    strcat(debug_str, command_str);
    UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    Delayms(500);
    response_length = UART1_ReadBuffer((uint8_t*)response_str, 32);
    if (response_length != -1) {
        response_str[response_length] = '\0';
        strcpy(debug_str, "< ");
        strcat(debug_str, response_str);
        strcat(debug_str, "\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    } else {
        strcpy(debug_str, "< ERROR\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    }
    
    U1BRG = 0x61A;

    // Change the name
    strcpy(command_str, "");
    strcat(command_str, "AT+NAME=");
    strcat(command_str, HC05_NAME);
    strcat(command_str, "\r\n");
    UART1_WriteBuffer((uint8_t*)command_str, strlen(command_str));
    strcpy(debug_str, "> ");
    strcat(debug_str, command_str);
    UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    Delayms(500);
    response_length = UART1_ReadBuffer((uint8_t*)response_str, 32);
    if (response_length != -1) {
        response_str[response_length] = '\0';
        strcpy(debug_str, "< ");
        strcat(debug_str, response_str);
        strcat(debug_str, "\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    } else {
        strcpy(debug_str, "< ERROR\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    }
    
    // Change the pin
    strcpy(command_str, "");
    strcat(command_str, "AT+PWSD=");
    strcat(command_str, HC05_PIN);
    strcat(command_str, "\r\n");
    UART1_WriteBuffer((uint8_t*)command_str, strlen(command_str));
    strcpy(debug_str, "> ");
    strcat(debug_str, command_str);
    UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    Delayms(500);
    response_length = UART1_ReadBuffer((uint8_t*)response_str, 32);
    if (response_length != -1) {
        response_str[response_length] = '\0';
        strcpy(debug_str, "< ");
        strcat(debug_str, response_str);
        strcat(debug_str, "\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    } else {
        strcpy(debug_str, "< ERROR\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    }
    
    // Change the bautrate
    strcpy(command_str, "");
    strcat(command_str, "AT+UART=234000,0,0");
    strcat(command_str, "\r\n");
    UART1_WriteBuffer((uint8_t*)command_str, strlen(command_str));
    strcpy(debug_str, "> ");
    strcat(debug_str, command_str);
    UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    Delayms(500);
    response_length = UART1_ReadBuffer((uint8_t*)response_str, 32);
    if (response_length != -1) {
        response_str[response_length] = '\0';
        strcpy(debug_str, "< ");
        strcat(debug_str, response_str);
        strcat(debug_str, "\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    } else {
        strcpy(debug_str, "< ERROR\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    }
    
    U1BRG = 0x40; // Change baudrate to 230400
    Delayms(500);
    
    // Check connection
    strcpy(command_str, "");
    strcat(command_str, "AT\r\n");
    UART1_WriteBuffer((uint8_t*)command_str, strlen(command_str));
    strcpy(debug_str, "> ");
    strcat(debug_str, command_str);
    UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    Delayms(500);
    response_length = UART1_ReadBuffer((uint8_t*)response_str, 32);
    if (response_length != -1) {
        response_str[response_length] = '\0';
        strcpy(debug_str, "< ");
        strcat(debug_str, response_str);
        strcat(debug_str, "\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    } else {
        strcpy(debug_str, "< ERROR\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    }
    
    // Check connection
    strcpy(command_str, "");
    strcat(command_str, "AT\r\n");
    UART1_WriteBuffer((uint8_t*)command_str, strlen(command_str));
    strcpy(debug_str, "> ");
    strcat(debug_str, command_str);
    UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    Delayms(500);
    response_length = UART1_ReadBuffer((uint8_t*)response_str, 32);
    if (response_length != -1) {
        response_str[response_length] = '\0';
        strcpy(debug_str, "< ");
        strcat(debug_str, response_str);
        strcat(debug_str, "\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    } else {
        strcpy(debug_str, "< ERROR\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    }
    
    // Reset the HC-05
    strcpy(command_str, "");
    strcat(command_str, "AT+RESET\r\n");
    UART1_WriteBuffer((uint8_t*)command_str, strlen(command_str));
    strcpy(debug_str, "> ");
    strcat(debug_str, command_str);
    UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    Delayms(500);
    response_length = UART1_ReadBuffer((uint8_t*)response_str, 32);
    if (response_length != -1) {
        response_str[response_length] = '\0';
        strcpy(debug_str, "< ");
        strcat(debug_str, response_str);
        strcat(debug_str, "\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    } else {
        strcpy(debug_str, "< ERROR\r\n");
        UART2_WriteBuffer((uint8_t*)debug_str, strlen(debug_str));
    }

    // Turn led off indicating finished initialization
    IO_LED_SetHigh();
}

/*
   Main application
 */
int main(void) {
    static uCAN_MSG canMessage;    // CAN message container
    static char canAsciiStr[21];     // UART string container
    
    // Initialize the device
    SYSTEM_Initialize();
    CAN1_TransmitEnable();
    CAN1_ReceiveEnable();
    
    // On first time use the HC-05 needs to be initialized.
    // The HC-05 can be put into command mode by placing the jumper P5.
    // The firmware check if the jumper is placed and initialized the HC-05.
    // If no jumper is placed the firmware will start normal.
    
    // Check if KEY pin is pulled high
    if (IO_KEY_GetValue()) {
        // Initialize the HC-05
        HC05_Initialize();
        // Wait for power reset
        while (1) {
            UART2_WriteBuffer((uint8_t*)"Waiting for power reset\r\n", strlen("Waiting for power reset\r\n"));
            Delayms(5000);
        }
    };
    
    while (1)
    {
        // Check if a can message was received
        if (CAN1_receive(&canMessage))
        {
            // Set led on indicating message processing
            IO_LED_SetLow();
            
            // Convert CAN message to ascii string
            CTS_CanMsgToString(&canMessage, canAsciiStr);
            // Write the ascii string to the HC-05
            UART1_WriteBuffer((uint8_t*)canAsciiStr, strlen(canAsciiStr));
            
            // Write same message to debug port
            UART2_WriteBuffer((uint8_t*)canAsciiStr, strlen(canAsciiStr));
            
            // Set led off indicating finished message processing
            IO_LED_SetHigh();
        }
    }
    
    return 1; 
}
