#include "system.h"

void configura_pic()
{
//  CONFIGURANDO IOs
    CMCON = 0xff;
    TRISA1 = 0;
    TRISB7 = 0;
    PORTA = 0x00;

//  CONFIGURANDO TIMER
    GIE = 1;  //habilita interrupcap global
    OPTION_REG = 0x01;   // prescaler e liga timer
    TMR0 = 6; //250 pulsos
    T0IF = 0;
    T0IE = 1;

//  CONFIGURANDO INTERRUPÇÃO EXTERNA
    TRISB0 = 1;
    INTE = 1;
    INTEDG = 0;
}


void configura_uart()
{
    TRISB2 = 0;  //  Tx
    TRISB2 = 1;  //  Rx
    TXSTA = 0x20;       //  Habilita a transmissão
    RCSTA = 0x90;       //  Habilita a porta serial e habilita recepção
    SPBRG = 0x4D;       //  Valor para ter o baud rate de 9600
    RCIE  = 1; //  Habilita interrução quando receber inf.
    PEIE = 1;
    RCIF = 0;

}

