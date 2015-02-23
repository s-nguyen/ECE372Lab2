/* 
 * File:   initCN.h
 * Author: gvanhoy
 *
 * Created on December 30, 2014, 12:35 PM
 */

#ifndef INITCN_H
#define	INITCN_H

#define PRESSED 0
#define RELEASED 1
#define BUTTON PORTBbits.RB2
#define RESET PORTBbits.RB5
void initCNForSW1();
void initSW2();
#endif	/* INITCN_H */

