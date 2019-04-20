
#include "defines.c"
/*========= Funções ============*/

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
    PORTAbits.RA1 = 0;
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


void grava_eeprom (int address, char data)
{

    EEADR = address;
    EEDATA = data;
    EECON1bits.EEPGD = 0;	//Acessa a EEPROM
    EECON1bits.CFGS = 0;	//Acessa a memoria
    EECON1bits.WREN = 1;	//Habilita escrita na memória
    INTCONbits.GIE = 0;		//Desabilita interrupções

    EECON2 = 0x55;
    EECON2 = 0xAA;

    EECON1bits.WR = 1;		//Inicia escrita
    INTCONbits.GIE = 1;

    PIR2bits.EEIF=0;
    EECON1bits.CFGS = 1;
    __delay_ms(10);
}

char le_eeprom(int address)
{
    EEADR = address;	//Endereço
    EECON1bits.WREN = 0;	//Operação de escrita
    EECON1bits.EEPGD = 0;	//Acesso à memória
    EECON1bits.RD = 1;	//Operação de leitura
    return(EEDATA);
}


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

void configura_pic()
{
    TRISAbits.RA0 = 1;
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 0;
    TRISDbits.RD7 = 0;

    T0CON = 0x17;   // prescaler e liga timer
    TMR0 = 0x48E4; //46875 pulsos
    TMR0ON = 1;
    INTCON = 0x20;
    TMR0IF = 0;

    TRISB=0b00000001;
    RBPU=0;
    LATBbits.LATB0 = 1;
    INT0IE=1;
    INTEDG0=0;

    PORTA = 0x00;
    ADCON1 = 0X0F;
}


void configura_uart()
{
    TRISCbits.RC6 = 0;  //  Tx
    TRISCbits.RC7 = 1;  //  Rx
    TXSTA = 0x20;       //  Habilita a transmissão
    RCSTA = 0x90;       //  Habilita a porta serial e habilita recepção
    SPBRG = 0x4D;       //  Valor para ter o baud rate de 9600
    PIE1bits.RCIE  = 1; //  Habilita interrução quando receber inf.
    RCONbits.IPEN = 0;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIR1bits.RCIF = 0;

}

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
        if(INT0IF == 1)
        {
            INT0IF = 0;
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
            TMR0 = 0x48E4; //46875 pulsos
            TMR0IF = 0;
            seg++;
            if(PORTBbits.RB0 == 1)
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
                PORTAbits.RA1 = ~PORTAbits.RA1;
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
