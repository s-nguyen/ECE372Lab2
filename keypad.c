#include "p24FJ64GA002.h"
#include "keypad.h"
#include "timer.h"

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
   
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;

    AD1PCFG = 0xFFFF;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB2 = 0;

    ODCBbits.ODB1 = 1;
    ODCBbits.ODB10 = 1;
    ODCBbits.ODB11 = 1;
    ODCBbits.ODB2 = 1;

    ROW1 = 0; 
    ROW2 = 0;
    ROW3 = 0;
    ROW4 = 0;

    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISBbits.TRISB0 = 1;

    CNPU1bits.CN2PUE = 1;
    CNPU1bits.CN3PUE = 1;
    CNPU1bits.CN4PUE = 1;

    CNEN1bits.CN2IE = 1;
    CNEN1bits.CN3IE = 1;
    CNEN1bits.CN4IE = 1;

    
    
    
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(void){
    char key = -1;
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 1;
    ROW4 = 1;
    
    ROW1 = 0;
    delay5ms();
    if(COL1 == KEY_PRESSED){
        return '1';
    }
    else if(COL2 == KEY_PRESSED){
        return '2';
    }
    else if(COL3 == KEY_PRESSED){
        return '3';
    }
    ROW1 = 1;

    ROW2 = 0;
    delay5ms();
    if(COL1 == KEY_PRESSED){
        return '4';
    }
    else if(COL2 == KEY_PRESSED){
        return '5';
    }
    else if(COL3 == KEY_PRESSED){
        return '6';
    }
    ROW2 = 1;

    ROW3 = 0;
    delay5ms();
    if(COL1 == KEY_PRESSED){
        return '7';
    }
    else if(COL2 == KEY_PRESSED){
        return '8';
    }
    else if(COL3 == KEY_PRESSED){
        return '9';
    }
    ROW3 = 1;

    ROW4 = 0;
    delay5ms();
    if(COL1 == KEY_PRESSED){
        return '*';
    }
    else if(COL2 == KEY_PRESSED){
        return '0';
    }
    else if(COL3 == KEY_PRESSED){
        return '#';
    }
    ROW4 = 1;
    return key;
}
