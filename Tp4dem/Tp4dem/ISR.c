/*
 * ISR.c
 *
 * Created: 11/7/2024 17:40:27
 *  Author: Alexis
 */ 
#include "ISR.h"
#include "serialPort.h"
#include "ctype.h"
#include "mef.h"

void init_uart(){
	SerialPort_Init(103);//inicializa el UART con una configuraci�n espec�fica, donde el valor 103 se usa para configurar la velocidad de transmisi�n y otros par�metros del UART, como la cantidad de bits de datos y la paridad
	SerialPort_TX_Enable();//habilita la transmisi�n (TX) del UART, permitiendo que el microcontrolador pueda enviar datos a trav�s del puerto serie.
	SerialPort_RX_Enable();//habilita la recepci�n (RX) del UART, permitiendo que el microcontrolador pueda recibir datos a trav�s del puerto serie
	SerialPort_RX_Interrupt_Enable(); // Habilitar interrupci�n RX completa
	sei(); // Habilitar interrupciones globales
}

uint8_t esIgual(char caracter, char caracter_recibido){
	return (caracter_recibido == caracter || caracter_recibido == toupper(caracter));
}

void mensajeInicial(){
	SerialPort_Send_String("Presione una de las siguientes teclas R, G o B para configurar su intencidad\r\n");
}
void mensaje_estado_red(){
	SerialPort_Send_String("Estas en el estado rojo\r\n");
}
void mensaje_estado_green(){
	SerialPort_Send_String("Estas en el estado verde\r\n");
}
void mensaje_estado_blue(){
	SerialPort_Send_String("Estas en el estado azul\r\n");
}
ISR(USART_RX_vect) {
	

	char recibir_caracter = UDR0; // Leer el car�cter recibido
	flagRED   = esIgual('r',recibir_caracter);// Ajustar flag para rojo
	flagGREEN = esIgual('g',recibir_caracter);// Ajustar flag para verde
	flagBLUE  = esIgual('b',recibir_caracter);// Ajustar flag para azul
}

