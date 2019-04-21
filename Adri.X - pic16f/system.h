#ifndef SYSTEM_H
#define	SYSTEM_H

#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       //RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define servo PORTBbits.RB7
#define _XTAL_FREQ 4000000

#include <xc.h>
/*========= Declarando estrutura de cadastro ============*/
struct cadastro{
    char d_hora;
    char u_hora;
    char d_minuto;
    char u_minuto;
    char passo;
};


/*========= Declarando variáveis ============*/
char i = 0, in = 0, libera = 0;
char flag = 0;
char dado, Min = 0, Hora = 0, led = 0, botao = 0;
char string[5];
unsigned char seg = 0;
char pendencia_remedio[4] = 0;

unsigned char add_d_hora = 0;
unsigned char add_u_hora = 4;
unsigned char add_d_minuto = 9;
unsigned char add_u_minuto = 14;
unsigned char add_passo = 24;

struct cadastro remedio[4];



/*========= Declarando funções ============*/
void grava_eeprom (int address, char data);
char le_eeprom(int address);
void enviaDados(char dados);
void enviaDados_eeprom(char data);
void configura_pic();
void configura_uart();
void incrementa_min();
void envia_dados_da_memoria();
void verifica();
void controle_servo(char numero_do_remedio);
void atualiza_relogio();
void atualiza_relogio_blue();
void cadastra_relogio();
void atualiza_remedio(char count);
void atualiza_variaveis();
void aciona();

#endif	/* SYSTEM_H */

