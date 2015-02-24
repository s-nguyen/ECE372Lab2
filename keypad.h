/* 
 * File:   keypad.h
 * Author: user
 *
 * Created on February 5, 2015, 11:42 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#define COL1 PORTAbits.RA1
#define COL2 PORTAbits.RA0
#define COL3 PORTBbits.RB0



#define ROW1 LATBbits.LATB1
#define ROW2 LATBbits.LATB10
#define ROW3 LATBbits.LATB11
#define ROW4 LATBbits.LATB2

#define KEY_PRESSED 0
#define KEY_RELEASE 1

void initKeypad(void);
char scanKeypad(void);

#endif	/* KEYPAD_H */

