#include "system.h"

void incrementa_min()
{
    Min++;
    if(Min == 60)
        {
            Hora++;
            Min = 0;
            if(Hora == 24)
                Hora = 0;
        }
}

void aciona()
{
    for(in = 0; in < 4; in++)
    {
        if(pendencia_remedio[in] == 1)
        {
             atualiza_remedio(in);
             while(pendencia_remedio[in] == 1)
            {
                controle_servo(in+1);
            }
        }
    }
    libera = 0;
    led = 0;
    RA1 = 0;
}

void atualiza_variaveis()
{
    char count;
    for(count = 0; count < 4; count++)
    {
        remedio[count].d_hora = le_eeprom(add_d_hora + count);
        remedio[count].u_hora = le_eeprom(add_u_hora + count);
        remedio[count].d_minuto = le_eeprom(add_d_minuto + count);
        remedio[count].u_minuto = le_eeprom(add_u_minuto + count);
        remedio[count].passo = le_eeprom(add_passo + count);
    }
}

void verifica()
{
    char count;
    for(count = 0; count < 4; count++)
    {
        if((remedio[count].d_hora) == (Hora/10) && (remedio[count].u_hora) == (Hora%10))
        {
            if((remedio[count].d_minuto) == (Min/10) && (remedio[count].u_minuto) == (Min%10 ))
            {
                 pendencia_remedio[count] = 1;
                 led = 1;
            }
        }
    }
}

void controle_servo(char numero_do_remedio)
{
        if(numero_do_remedio == 0)
        {
            servo = 1;
            __delay_ms(0.5);
            servo = 0;
            __delay_ms(19.5);
        }
        else if(numero_do_remedio == 1)
        {
            servo = 1;
            __delay_ms(0.9);
            servo = 0;
            __delay_ms(19.1);
        }
        else if(numero_do_remedio == 2)
        {
            servo = 1;
            __delay_ms(1.4);
            servo = 0;
            __delay_ms(18.6);
        }
        else if(numero_do_remedio == 3)
        {
            servo = 1;
            __delay_ms(2);
            servo = 0;
            __delay_ms(18);
        }
        else if(numero_do_remedio == 4)
        {
            servo = 1;
            __delay_ms(2.4);
            servo = 0;
            __delay_ms(17.6);
        }
}

void atualiza_relogio()
{
    Hora = le_eeprom(add_d_hora + 20) * 10;
    Hora += le_eeprom(add_d_hora + 21);
    Min = le_eeprom(add_d_hora + 22) * 10;
    Min += le_eeprom(add_d_hora + 23);
}
void atualiza_relogio_blue()
{
    char i;
    for(i = 1; i < 5; i++)
    {
        grava_eeprom(add_d_hora + 20 + i - 1, (string[i] - 48));
    }
    Hora = le_eeprom(add_d_hora + 20) * 10;
    Hora += le_eeprom(add_d_hora + 21);
    Min = le_eeprom(add_d_hora + 22) * 10;
    Min += le_eeprom(add_d_hora + 23);
}

void cadastra_relogio()
{
    grava_eeprom(add_d_hora + 20, Hora/10);
    grava_eeprom(add_d_hora + 21, Hora%10);
    grava_eeprom(add_d_hora + 22, Min/10);
    grava_eeprom(add_d_hora + 23, Min%10);
}

void atualiza_remedio(char count)
{
    char dados;
    remedio[count].d_hora = (Hora/10 +  (remedio[count].passo)/10);
    remedio[count].u_hora = (Hora%10 +  (remedio[count].passo)%10);
    dados = (remedio[count].d_hora * 10 + remedio[count].u_hora);
    if( dados > 23)
    {
        dados = dados - 24;
    }
    grava_eeprom(add_d_hora + count, dados/10);
    grava_eeprom(add_u_hora + count, dados%10);
    remedio[count].d_hora =  dados/10;
    remedio[count].u_hora = dados%10;
}

