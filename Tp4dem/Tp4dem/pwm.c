/*
 * pwm.c
 *
 * Created: 11/7/2024 19:04:49
 *  Author: Alexis
 */ 

#include "avr/io.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include "SerialPort.h"

 uint8_t potencia_Anterior;

//por sw
volatile uint8_t PWM_DELTA = 1;  // Definir PWM_DELTA como una variable global
#define PWM_PERIOD 255
#define PWM_OFF    PORTB &=~(1<<PINB5)
#define PWM_ON     PORTB |=(1<<PINB5)
#define PWM_START  DDRB |=(1<<PINB5)



volatile uint8_t flag_update;



//por software 
void Timer0_init(void){
	PWM_START;
	TCCR0A = (1<<COM0A1)|(1 << WGM01); // Configura el Timer0 en el modo CTC (Clear Timer on Compare Match) estableciendo el bit WGM01
	TCCR0B = (1 << CS01) | (1 << CS00); // Configura el prescaler del Timer0 a 64 a una frecuencia aprox de  488
	OCR0A = PWM_DELTA; 
	TIMSK0 = (1 << OCIE0A); // Habilita la interrupción del Timer0 cuando el contador alcanza el valor de OCR0A

}
void PWM_soft_Update(void) {
	static uint8_t PWM_position = 0;
	
	if (++PWM_position >= PWM_PERIOD) {
		PWM_position = 0;
	}
	if (PWM_position < PWM_DELTA) {
		PWM_ON;
		} else {		
		PWM_OFF;
	}
}

ISR (TIMER0_COMPA_vect)
{
	PWM_soft_Update();
	flag_update=1;
}



//por hardware

void pwm_init( ){
	DDRB |=(1<<PINB1);  //PIN PB1 corresponde a la salida OC1A
	DDRB |=(1<<PINB2);  //PIN PB2 corresponde a la salida OC1B
	OCR1A=255;
	OCR1B=255;
	
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11); // Configura el Timer1 para Fast PWM y establece el modo WGM11
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10) | (1 << CS12);
	ICR1 = 255;
	Timer0_init();
	sei();
}
void mostrar_Potencia(char* color, uint8_t potencia) {
	
	if (potencia_Anterior!=potencia){
		potencia_Anterior=potencia;
	   char mensaje[50];  // Tamaño suficiente para el mensaje
	   snprintf(mensaje, sizeof(mensaje), "El color %s tiene una potencia de %d\r\n", color, potencia);
	   SerialPort_Send_String(mensaje);
	}
}
void set_potencia_blue(uint8_t potencia) {
	//mostrar_Potencia("Azul",potencia);
	cli();
	OCR1A = 255-potencia;
	sei(); 
}

void set_potencia_green(uint8_t potencia) {
	   // mostrar_Potencia("Verde",potencia);
		cli();
		OCR1B = 255-potencia;
		sei(); 
}

void set_potencia_red(uint8_t potencia) {
	//mostrar_Potencia("Rojo",potencia);
	cli();
	PWM_DELTA= 255-potencia;
	sei();
}