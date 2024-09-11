/*
 * Controller for the QN8066 device (FM transmitter). 
 * Microcontroller: PIC16F876A. XC8 Compiler (MPLAB).
 *
 * Author: Ricardo Lima Caratti
 * Created on August, 2024
 * Copyright - This code can be freely obtained and distributed under 
 * the MIT license (https://github.com/pu2clr/QN8066_PIC16F/blob/main/LICENSE).
 */


#include <xc.h>
// #include "QN8066.h"


#include <xc.h>

// Check the _XTAL_FREQ value defined in QN8066.h and change it for your desired value
#define _XTAL_FREQ 4000000  // defines the oscillator (defined in QN8066.h)

// PIC16F876A Configuration Bit Settings 
#pragma config FOSC = HS      // 
#pragma config WDTE = OFF       // Watchdog Timer disabled 
#pragma config PWRTE = OFF      // Power-up Timer disabled
#pragma config BOREN = OFF      // Brown-out Reset disabled
#pragma config LVP = OFF        // Low Voltage Programming disabled
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection disabled
#pragma config CP = OFF         // Flash Program Memory Code Protection disabled

// Definição dos pinos do LCD
#define LCD_RS  RA0  // Pino RS do LCD
#define LCD_E   RA1  // Pino Enable (E) do LCD

// Definição dos pinos de dados do LCD
#define LCD_DB4 RB3  // Pino DB4 do LCD
#define LCD_DB5 RB2  // Pino DB5 do LCD
#define LCD_DB6 RB1  // Pino DB6 do LCD
#define LCD_DB7 RB0  // Pino DB7 do LCD


// Funções de controle do LCD
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(unsigned char, unsigned char);
void lcd_write_string(const char *);

void lcd_pulse_enable(void);
void lcd_send_nibble(unsigned char);




// Função para enviar um comando ao LCD
void lcd_command(unsigned char cmd) {
    LCD_RS = 0;  // RS = 0 para comando
    lcd_send_nibble(cmd >> 4);  // Enviar os 4 bits mais significativos
    lcd_send_nibble(cmd);       // Enviar os 4 bits menos significativos
    __delay_ms(2);  // Pequeno atraso para o LCD processar o comando
}

// Função para enviar um dado ao LCD
void lcd_data(unsigned char data) {
    LCD_RS = 1;  // RS = 1 para dado
    lcd_send_nibble(data >> 4);  // Enviar os 4 bits mais significativos
    lcd_send_nibble(data);       // Enviar os 4 bits menos significativos
    __delay_ms(2);  // Pequeno atraso para o LCD processar o dado
}

// Função para inicializar o LCD
void lcd_init(void) {
    __delay_ms(15);  // Aguardar o LCD estabilizar após ser energizado
    
    lcd_command(0x03);  // Inicialização em modo de 8 bits
    __delay_ms(5);
    lcd_command(0x03);
    __delay_us(100);
    lcd_command(0x03);
    lcd_command(0x02);  // Configurar o modo de 4 bitsx`
    // Configurar o LCD para 2 linhas e caracteres de 5x8
    lcd_command(0x28);
    lcd_command(0x0C);  // Display ligado, cursor desligado
    lcd_command(0x06);  // Incrementar cursor automaticamente
    lcd_clear();        // Limpar o display
}

// Função para limpar o display LCD
void lcd_clear(void) {
    lcd_command(0x01);  // Comando para limpar o display
    __delay_ms(2);      // Aguardar a conclusão da limpeza
}

// Função para mover o cursor para uma posição específica
void lcd_set_cursor(unsigned char row, unsigned char col) {
    unsigned char pos;
    
    if (row == 0)
        pos = 0x80 + col;  // Linha 1
    else
        pos = 0xC0 + col;  // Linha 2
    
    lcd_command(pos);  // Enviar comando de posição
}

// Função para escrever uma string no LCD
void lcd_write_string(const char *str) {
    while (*str) {
        lcd_data(*str++);  // Enviar caractere por caractere
    }
}

// Função para enviar um nibble (4 bits) ao LCD
void lcd_send_nibble(unsigned char nibble) {
    // Enviar o nibble para os pinos de dados do LCD
    LCD_DB4 = (nibble >> 0) & 0x01;
    LCD_DB5 = (nibble >> 1) & 0x01;
    LCD_DB6 = (nibble >> 2) & 0x01;
    LCD_DB7 = (nibble >> 3) & 0x01;
    
    lcd_pulse_enable();  // Pulso no pino Enable para enviar o nibble
}

// Função para gerar um pulso no pino Enable (E) do LCD
void lcd_pulse_enable(void) {
    LCD_E = 1;   // Enable em nível alto
    __delay_us(10);  // Pequeno atraso
    LCD_E = 0;   // Enable em nível baixo
    __delay_us(10);  // Pequeno atraso
}


void main(void) {
       
  
    TRISA = 0x00;  // Configurar os pinos de controle do LCD como saída
    TRISB = 0x00;  // Configurar os pinos de dados do LCD como saída
    
    lcd_init();    // Inicializa o LCD
    

   
    while (1) {
        
    lcd_clear();
    __delay_ms(1000);
    lcd_set_cursor(0,0);
    lcd_write_string("QN8066 WITH");  // Escreve mensagem no LCD
    lcd_set_cursor(0,1);
    lcd_write_string("PIC16F876A"); 
    __delay_ms(1000);

    }
    
    return;
}
