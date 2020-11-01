/* 
 * File:   main.c
 * Author: Takuya
 *
 * Created on 2020/11/01, 0:06
 */
// CONFIG1
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB3      // CCP1 Pin Selection bit (CCP1 function on RB3)  ※CCP1はRB3から出力するように設定
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#include <stdio.h>
#include <stdlib.h>

#include "com_types.h"

#define _XTAL_FREQ 1000000 //__delay_ms()関数を使用するための提議

/*
 * 
 */
int main(int argc, char** argv) 
{
    OSCCON = 0b01000000;    //内蔵クロックの周波数を1MHzに設定
	ANSEL  = 0b00000000;	//全ての端子をデジタルモードで使用
    
    PORTA = 0x00;   // PORTAを初期化
    PORTB = 0x00;   // PORTBを初期化
    TRISA  = 0b00000000;    //ポートAはすべて出力とする
	TRISB  = 0b00000001;	//ポートBはRB0を入力端子とする

    CCP1CON = 0x0f;         //PWMモードに設定
    T2CON = 0b00000110;		//プリスケール:16
    PR2 = 0XFF;		//PR2最大値(255)に設定 ← PWM周期
    CCPR1L = 0;     //レジスタ初期化
    CCPR1H = 0;     //レジスタ初期化

    TMR2ON = 1;					//Timer2スタート

    /* 電源投入時にサーボモータを初期位置に移動。 */
    CCPR1L = 8;
    __delay_ms(1000);  // 1秒の待ち時間
    

    while(1){
        /* 入力電圧値のチェック */
        while(RB0 != 1){
            /* RB0への電圧が遮断される(=スイッチPush)まで待機 */
         }
        /* スイッチが押されたのでPWM波を出力する */                
         CCPR1L =35;
        __delay_ms(2000);  // 1秒の待ち時間
        
        CCPR1L = 8;
        __delay_ms(2000);  // 1秒の待ち時間
    }
    
    return (EXIT_SUCCESS);
}
