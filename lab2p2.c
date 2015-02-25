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
#include <stdlib.h>
#include <string.h>

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

typedef enum stateTypeEnum{


    scan, waitforpress, waitforrelease, debouncepress, debouncerelease,
            setmode, checkinputset, enter, checkinputenter, checkpassword,
            good, bad


} stateType;

volatile stateType curState = setmode;
volatile stateType nextState;


int main(void)
{
    char key;
    char tempPassword[] = "0000";
    char password[4][5]; //Never forget the stupid null character
    int starCount = 0;
    int passCount = 0;
    int storageCount = 0;
    int i = 0;

    initKeypad();
    initLCD();

    curState = setmode;

    while(1)
    {
        switch(curState){
            case enter:
                starCount = 0;
                passCount = 0;
                clearLCD();
                moveCursorLCD(0,0);
                printStringLCD("Enter");
                moveCursorLCD(1,0);
                nextState = checkinputenter;
                curState = waitforpress;
                break;
            case setmode:
                starCount = 0;
                passCount = 0;
                clearLCD();
                moveCursorLCD(0,0);
                printStringLCD("Set Mode");
                moveCursorLCD(1,0);
                nextState = checkinputset;
                curState = waitforpress;
                break;
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
                curState = nextState;
                break;
            case checkinputset:
                if(key == '*' || key == '#'){
                    clearLCD();
                    moveCursorLCD(0,0);
                    printStringLCD("Invalid");
                    delayS(2);
                    curState = enter;
                }
                else if(passCount == 3){
                    clearLCD();
                    moveCursorLCD(0,0);
                    printStringLCD("Valid");
                    delayS(2);
                    //Storepassword
                    tempPassword[passCount] = key;
                    strcpy(password[storageCount], tempPassword);
                    storageCount++;
                    curState = enter;
                }
                else{
                    printCharLCD(key);
                    //Storepassword temp
                    tempPassword[passCount] = key;
                    passCount++;
                    curState = waitforpress;
                }
                break;
            case checkinputenter:
                //TODO: fix entering a number after *
                if(key == '*' && passCount == 0){
                    printCharLCD(key);
                    starCount++;
                    passCount++;
                    curState = waitforpress;
                }
                else if(key == '*' && passCount == 1 && starCount == 1){
                    curState = setmode;
                }
                else if(key == '*' || key == '#' || (key != '*' && starCount == 1)){
                    curState = bad;
                }
                else if(passCount == 3){
                    tempPassword[passCount] = key;
                    passCount++;
                    curState = checkpassword;
                }
                else{
                    printCharLCD(key);
                    //Storepassword
                    tempPassword[passCount] = key;
                    passCount++;
                    curState = waitforpress;
                }
                break;
            case checkpassword:
                for(i = 0; i < storageCount; i++){
                    if(strcmp(password[i], tempPassword) == 0){
                        curState = good;
                        break;
                    }
                    else{
                        curState = bad;
                    }
                }
                break;
            case good:
                clearLCD();
                moveCursorLCD(0,0);
                printStringLCD("Good");
                delayS(2);
                curState = enter;
                break;
            case bad:
                clearLCD();
                moveCursorLCD(0,0);
                printStringLCD("Bad");
                delayS(2);
                curState = enter;
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

