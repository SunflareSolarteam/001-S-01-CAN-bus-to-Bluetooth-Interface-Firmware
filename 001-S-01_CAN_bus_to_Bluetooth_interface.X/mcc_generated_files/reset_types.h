/**
  RESET Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    reset_types.h

  @Summary
    This is the generated driver implementation file for the RESET driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for RESET.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  dsPIC33EP128GS804
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB             :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef RESET_TYPES_H
#define	RESET_TYPES_H

/**
  Section: Type defines
 */ 
    
/** 
 * RCON error type enumerator. Supported types:
 * ERR_RCON_TRAPR
 * ERR_RCON_IOPUWR
 * ERR_RCON_CM 
 * ERR_RCON_WDTO_ISR
 */
typedef enum tagERROR_TYPE
{
    ERR_RCON_TRAPR      = 1, /** A Trap Conflict Reset has occurred **/
    ERR_RCON_IOPUWR     = 2, /** An illegal opcode detection, an illegal address mode or Uninitialized W register used as an
                             *   Address Pointer caused a Reset **/
    ERR_RCON_CM         = 3, /** A Configuration Mismatch Reset has occurred **/
    ERR_RCON_WDTO_ISR   = 4  /** WDT time-out has occurred **/
}RESET_TYPES;

/** 
 * RESET CAUSE Masks. Supported masks:
 * RESET_MASK_WDTO
 * RESET_MASK_SWR
 * REST_MASK_EXTR
 * RESET_MASK_CM
 * RESET_MASK_IOPUWR
 * RESET_MASK_TRAPR
 */
typedef enum tagRESET_MASKS
{ 
  RESET_MASK_WDTO = 0x0010,
  RESET_MASK_SWR = 0x0040,
  RESET_MASK_EXTR = 0x0080, 
  RESET_MASK_CM = 0x0200, 
  RESET_MASK_IOPUWR = 0x4000, 
  RESET_MASK_TRAPR = 0x8000, 
} RESET_MASKS;

#endif	/* RESET_TYPES_H */
/**
 End of File
*/