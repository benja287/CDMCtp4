#include "mef.h"
#include "avr/io.h"
#include "ISR.h"
#include "avr/io.h"
#include "pwm.h"
#include "pot.h"
uint8_t potencia_red=255;
uint8_t potencia_blue=0;
uint8_t potencia_green=0;

estados estado;
void mef_init(){
	init_uart();
	mensajeInicial();
	pwm_init();
	pot_init();
	estado=RED;
	
}
estados siguienteEstado(){
	estados defecto= estado;
	if (flagBLUE){
		mensaje_estado_blue();
		flagBLUE=0;
		return BLUE;
		}else{
		if (flagGREEN){
			mensaje_estado_green();
			flagGREEN=0;
			return GREEN;
			}else{
				if (flagRED){
					mensaje_estado_red();
					flagRED=0;
					return RED;
				}else{
					uint8_t potencia=get_pot();
					switch(estado){
						case RED:
							potencia_red=potencia;
							break;
						case GREEN:
							potencia_green=potencia;
							break;	
						case BLUE:
						potencia_blue=potencia;
						break;
					}
					return defecto;
				}
			
		}
	}
}

void mef_update(){
	switch(estado){
		case RED:	
		set_potencia_red(potencia_red);
		estado=siguienteEstado();
		break;
		
		case GREEN:
		set_potencia_green(potencia_green);
		estado=siguienteEstado();
		break;
		
		case BLUE:
		set_potencia_blue(potencia_blue);
		estado=siguienteEstado();
		break;
	}
}


