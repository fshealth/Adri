#include "system.h"

void grava_eeprom (int address, char data)
{
    EEADR = address;
    EEDATA = data;
    WREN = 1;           //Habilita escrita na memória
    GIE = 0;		//Desabilita interrupções

    EECON2 = 0x55;
    EECON2 = 0xAA;

    WR = 1;		//Inicia escrita
    GIE = 1;

    EEIF=0;
    __delay_ms(10);
}

char le_eeprom(int address)
{
    EEADR = address;	//Endereço
    WREN = 0;	//Operação de escrita
    RD = 1;	//Operação de leitura
    return(EEDATA);
}

