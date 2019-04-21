#include "system.h"

/*========= Funções ============*/
void enviaDados(char dados)
{
    while(!TXIF);
    TXREG = dados;
}

void enviaDados_eeprom(char data)
{
    while(!TXIF);
    TXREG = data + 48;
}

void envia_teste()
{
        envia_dados_da_memoria();
        enviaDados('-');
        enviaDados(' ');
        enviaDados(((Hora/10) + 48));
        enviaDados(((Hora%10) + 48));
        enviaDados(':');
        enviaDados(((Min/10) + 48));
        enviaDados(((Min%10) + 48));
        enviaDados(':');
        enviaDados(((seg/10) + 48));
        enviaDados(((seg%10) + 48));
        enviaDados('\n');
}

void comunica()
{
     if(string[0] == 'R')
        {
            atualiza_relogio_blue();
            return;
        }


        i = string[0] - 48; // elemento da struct


        remedio[i].d_hora = (string[1] - 48);
        remedio[i].u_hora = (string[2] - 48);
        remedio[i].passo = ((remedio[i].d_hora * 10) + remedio[i].u_hora);
        grava_eeprom(add_passo + i, remedio[i].passo);
        dado =  remedio[i].passo + Hora;
        if( dado > 23)
        {
            dado = dado - 24;
        }
        grava_eeprom((add_d_hora + i), dado/10);
        grava_eeprom((add_u_hora + i), dado%10);
        remedio[i].d_hora =  dado/10;
        remedio[i].u_hora = dado%10;
        grava_eeprom((add_d_minuto + i), Min/10);
        grava_eeprom((add_u_minuto + i), Min%10);
        remedio[i].d_minuto = Min/10;
        remedio[i].u_minuto = Min%10;
        pendencia_remedio[i] = 1;
        libera = 1;
}

void interrupt serial (void)
{
        if(INTF == 1)
        {
            INTF = 0;
            if(botao == 0)
            {
                if(libera)
                    pendencia_remedio[in] = 0;
                botao = 1;
                libera = 1;
            }

        }

        if(TMR0IF == 1)
        {
            TMR0 = 6;
            TMR0IF = 0;
            seg++;
            if(RB0 == 1)
                botao = 0;

            if(seg == 60)
            {
                incrementa_min();
                cadastra_relogio();
                seg = 0;
            }
            if(seg == 0)
            {
                verifica();
            }
            envia_teste();
            if(led == 1)
            {
                RA1 = ~RA1;
            }
        }

        if(RCIF == 1)
        {
            RCIF = 0;
            string[flag] = RCREG;
            flag++;
            if(flag >= 5)
            {
                flag = 0;
                comunica();
            }
        }
}


void envia_dados_da_memoria()
{
    char indice;
    for(indice = 0; indice < 4; indice++)
    {
        enviaDados(remedio[indice].d_hora + 48);
        enviaDados(remedio[indice].u_hora + 48);
        enviaDados(':');
        enviaDados(remedio[indice].d_minuto + 48);
        enviaDados(remedio[indice].u_minuto + 48);
        enviaDados('\t');
    }
}
