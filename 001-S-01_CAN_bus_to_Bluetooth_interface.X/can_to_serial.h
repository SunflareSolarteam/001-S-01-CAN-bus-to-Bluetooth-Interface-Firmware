/* 
 * File:   serial_to_can.h
 * Author: Gerke Kooistra
 *
 * Created on 20 april 2019, 20:59
 */

#ifndef SERIAL_TO_CAN_H
#define	SERIAL_TO_CAN_H

#include "mcc_generated_files/can_types.h"
/**
  @Summary
    Converts CAN message to ascii hexadecimal string

  @Description
    Converts CAN message to ascii hexadecimal string

  @Preconditions
    None

  @Returns
    None.

  @Param
    uCAN_MSG *recCanMsg     Pointer to the CAN message to be converted
    char *string            Pointer to store the Ascii hexadecimal string into
 
  @Example
    <code>
    // Convert CAN message to ascii string
    CTS_CanMsgToString(&canMessage, &canAsciiStr);
    </code>

*/
void CTS_CanMsgToString(uCAN_MSG *recCanMsg, char *string);

#endif	/* SERIAL_TO_CAN_H */

