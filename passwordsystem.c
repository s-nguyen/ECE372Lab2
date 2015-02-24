// ******************************************************************************************* //
// File:         lab2p1.c
// Date:
// Authors:
//
// Description:
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#include "keypad.h"

#include <stdio.h>

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

typedef enum stateTypeEnum{


    scan, waitforpress, waitforrelease, debouncepress, debouncerelease, printlcd,
            checkcursor


} stateType;

volatile stateType curState = waitforpress;
volatile int correct = 0;


int main(void)
{
    char key;
    int cursor = 0;
    initKeypad();
    initLCD();
    //initTimer1();


    curState = waitforpress;


    while(1)
    {
        switch(curState){
            case waitforpress:
                break;
            case debouncepress:
                delay5ms();
                curState = scan;
                break;
            case scan:
                ROW1 = 1;
                ROW2 = 1;
                ROW3 = 1;
                ROW4 = 1;
                key = scanKeypad();
                ROW1 = 0;
                ROW2 = 0;
                ROW3 = 0;
                ROW4 = 0;
                curState = waitforrelease;
                break;
            case waitforrelease:
                break;
            case debouncerelease:
                delay5ms();
                curState = printlcd;
                break;
            case printlcd:
                printCharLCD(key);
                curState = checkcursor;
                break;
            

        }

    }

    return 0;
}

void _ISR _CNInterrupt(void){
    IFS1bits.CNIF = 0;
    if(COL1 == KEY_PRESSED || COL2 == KEY_PRESSED || COL3 == KEY_PRESSED){
        curState = debouncepress;
    }
    else{
        curState = debouncerelease;
    }
}

