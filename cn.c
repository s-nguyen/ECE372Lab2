#include "p24fj64ga002.h"
#include "cn.h"

//Initilize the reset button
void initCNForSW1(){
    //Use the switch on the board connected to RB5
    TRISBbits.TRISB5 = 1;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
    CNEN2bits.CN27IE = 1;
}

//Initilizes the External Switch Used for Stopping / Starting the stop watch
void initSW2(){
    AD1PCFGbits.PCFG4 = 1; //Turn this analogue pin to digital
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;  //Enable Interrupt


    TRISBbits.TRISB2 = 1; //IO5 //Set as input

    CNPU1bits.CN6PUE = 1; //Set as a pullup resistor
    CNEN1bits.CN6IE = 1; //Enable Interrupt for this pin

}