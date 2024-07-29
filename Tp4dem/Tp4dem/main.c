#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "mef.h"
#include "util/delay.h"
extern volatile uint8_t flag_update;
int main(void) {
	
	mef_init();

	while (1) {
	//if (flag_update){
	   // flag_update=0;
	    mef_update();
	//}
	//	 _delay_ms(500);
	}
}


