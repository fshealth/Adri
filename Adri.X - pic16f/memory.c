#include "system.h"

void grava_eeprom (int address, char data)
{
    EEADR = address;
    EEDATA = data;
    WREN = 1;           //Habilita escrita na mem�ria
    GIE = 0;		//Desabilita interrup��es

    EECON2 = 0x55;
    EECON2 = 0xAA;

    WR = 1;		//Inicia escrita
    GIE = 1;

    EEIF=0;
    __delay_ms(10);
}

char le_eeprom(int address)
{
    EEADR = address;	//Endere�o
    WREN = 0;	//Opera��o de escrita
    RD = 1;	//Opera��o de leitura
    return(EEDATA);
}

