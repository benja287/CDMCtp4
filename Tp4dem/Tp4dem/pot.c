
#include <avr/io.h>
#include "pot.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include "serialPort.h"
#include <stdio.h>

void pot_init() {
	// Configurar el pin PC3 como entrada
	DDRC &= ~(1 << DDC3);
	// Configurar ADC: Vref = AVCC, canal ADC3 (PC3), ajustar a la izquierda el resultado
	ADMUX = (1 << REFS0) | (1 << ADLAR) | (1 << MUX1) | (1 << MUX0);
	
	// Habilitar ADC y establecer el prescaler a 128
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
uint8_t get_pot() {
	// Iniciar conversión ADC
	ADCSRA |= (1 << ADSC);
	
	// Esperar a que la conversión termine
	while (ADCSRA & (1 << ADSC));
	
	// Leer el resultado (8 bits)
	uint8_t adcResult = ADCH;
	
	return adcResult;
}