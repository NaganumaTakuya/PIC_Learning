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
#pragma config CCPMX = RB3      // CCP1 Pin Selection bit (CCP1 function on RB3)  ��CCP1��RB3����o�͂���悤�ɐݒ�
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

#define _XTAL_FREQ 1000000 //__delay_ms()�֐����g�p���邽�߂̒�c

/*
 * 
 */
int main(int argc, char** argv) 
{
    OSCCON = 0b01000000;    //�����N���b�N�̎��g����1MHz�ɐݒ�
	ANSEL  = 0b00000000;	//�S�Ă̒[�q���f�W�^�����[�h�Ŏg�p
    
    PORTA = 0x00;   // PORTA��������
    PORTB = 0x00;   // PORTB��������
    TRISA  = 0b00000000;    //�|�[�gA�͂��ׂďo�͂Ƃ���
	TRISB  = 0b00000001;	//�|�[�gB��RB0����͒[�q�Ƃ���

    CCP1CON = 0x0f;         //PWM���[�h�ɐݒ�
    T2CON = 0b00000110;		//�v���X�P�[��:16
    PR2 = 0XFF;		//PR2�ő�l(255)�ɐݒ� �� PWM����
    CCPR1L = 0;     //���W�X�^������
    CCPR1H = 0;     //���W�X�^������

    TMR2ON = 1;					//Timer2�X�^�[�g

    /* �d���������ɃT�[�{���[�^�������ʒu�Ɉړ��B */
    CCPR1L = 8;
    __delay_ms(1000);  // 1�b�̑҂�����
    

    while(1){
        /* ���͓d���l�̃`�F�b�N */
        while(RB0 != 1){
            /* RB0�ւ̓d�����Ւf�����(=�X�C�b�`Push)�܂őҋ@ */
         }
        /* �X�C�b�`�������ꂽ�̂�PWM�g���o�͂��� */                
         CCPR1L =35;
        __delay_ms(2000);  // 1�b�̑҂�����
        
        CCPR1L = 8;
        __delay_ms(2000);  // 1�b�̑҂�����
    }
    
    return (EXIT_SUCCESS);
}
