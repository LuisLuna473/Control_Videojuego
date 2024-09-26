/*
 * Control.c
 *
 * Created: 20/09/2024 11:09:08
 * Author : luisa
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h> //Función para usar Delays
#include <avr/interrupt.h>
#include "UART/UART0.h"

void Setup(void);

volatile uint8_t comando = 6;
int main(void)
{
    Setup();
    while (1) 
    {
		/*if(comando == 0){
			PORTC |= (1<<PORTC0);
			PORTC &= ~((1<<PORTC5)|(1<<PORTC4)|(1<<PORTC3)|(1<<PORTC2)|(1<<PORTC1));	
		}else if(comando == 1){
			PORTC |= (1<<PORTC1);
			PORTC &= ~((1<<PORTC5)|(1<<PORTC4)|(1<<PORTC3)|(1<<PORTC2)|(1<<PORTC0));
		}else if(comando == 2){
			PORTC |= (1<<PORTC2);
			PORTC &= ~((1<<PORTC5)|(1<<PORTC4)|(1<<PORTC3)|(1<<PORTC1)|(1<<PORTC0));
		}else if(comando == 3){
			PORTC |= (1<<PORTC3);
			PORTC &= ~((1<<PORTC5)|(1<<PORTC4)|(1<<PORTC2)|(1<<PORTC1)|(1<<PORTC0));
		}else if(comando == 4){
			PORTC |= (1<<PORTC4);
			PORTC &= ~((1<<PORTC5)|(1<<PORTC3)|(1<<PORTC2)|(1<<PORTC1)|(1<<PORTC0));
		}else if(comando == 5){
			PORTC |= (1<<PORTC5);
			PORTC &= ~((1<<PORTC4)|(1<<PORTC3)|(1<<PORTC2)|(1<<PORTC1)|(1<<PORTC0));
		}*/
		switch(comando){
			case 0:
				writeUART('f');
				PORTC |= (1<<PORTC0);
				PORTC &= ~((1<<PORTC5)|(1<<PORTC4)|(1<<PORTC3)|(1<<PORTC2)|(1<<PORTC1));
				comando = 6; 
				break;
			case 1:
				//Enviar comando 'a'
				writeUART('a');
				PORTC |= (1<<PORTC1);
				PORTC &= ~((1<<PORTC5)|(1<<PORTC4)|(1<<PORTC3)|(1<<PORTC2)|(1<<PORTC0));
				comando = 6;
				break;
			case 2:
				//Enviaiar comando 'b'
				writeUART('b');
				PORTC |= (1<<PORTC2);
				PORTC &= ~((1<<PORTC5)|(1<<PORTC4)|(1<<PORTC3)|(1<<PORTC1)|(1<<PORTC0));
				comando = 6;
				break;
			case 3:
				//Enviar comando 'c'
				writeUART('c');
				PORTC |= (1<<PORTC3);
				PORTC &= ~((1<<PORTC5)|(1<<PORTC4)|(1<<PORTC2)|(1<<PORTC1)|(1<<PORTC0));
				comando = 6;
				break;
			case 4:
				//
				writeUART('d');
				PORTC |= (1<<PORTC4);
				PORTC &= ~((1<<PORTC5)|(1<<PORTC3)|(1<<PORTC2)|(1<<PORTC1)|(1<<PORTC0));
				comando = 6;
				break;
			case 5:
				//
				writeUART('e');
				PORTC |= (1<<PORTC5);
				PORTC &= ~((1<<PORTC4)|(1<<PORTC3)|(1<<PORTC2)|(1<<PORTC1)|(1<<PORTC0));
				comando = 6;
				break;
			case 6:
				break;
			default:
				break;
		}
    }
}

void Setup(void){
	cli();
	DDRB &= ~((1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0));
	PORTB |= ((1<<PORTB4)|(1<<PORTB3)|(1<<PORTB2)|(1<<PORTB1)|(1<<PORTB0));
	DDRD &= ~(1<<DDD7);
	PORTD |= (1<<PORTD7);

				//PB0-PB5
	PCMSK0 = (1<<PCINT4)|(1<<PCINT3)|(1<<PCINT2)|(1<<PCINT1)|(1<<PCINT0);
	PCICR |= (1<< PCIE0);
	
	//PD7
	PCMSK2 = (1<<PCINT23);
	PCICR |= (1<<PCIE2);
	
	DDRC |= (1<<DDC5)|(1<<DDC4)|(1<<DDC3)|(1<<DDC2)|(1<<DDC1)|(1<<DDC0);
	PORTC = 0;
	SetupUART0(M9600);
	sei(); 
}

ISR(PCINT0_vect){
	/*if ((PINB & (1<<PINB5)) == 0){
		//Encender Led <-
		comando = 5;
		PORTC |= (1<<PORTC5);
	}*/
	if ((PINB & (1<<PINB0)) == 0){
		//Encender Led <-
		comando = 0;
		//PORTC |= (1<<PORTC0);
	}
	if ((PINB & (1<<PINB1)) == 0){
		//Encender Led <-
		comando = 1;
		//PORTC |= (1<<PORTC1);
	}
	if ((PINB & (1<<PINB2)) == 0){
		//Encender Led <-
		comando = 2;
		//PORTC |= (1<<PORTC2);
	}
	if ((PINB & (1<<PINB3)) == 0){
		//Encender Led <-
		comando = 3;
		//PORTC |= (1<<PORTC3);
	}
	if ((PINB & (1<<PINB4)) == 0){
		//Encender Led <-
		comando = 4;
		//PORTC |= (1<<PORTC4);
	}
	
	PCIFR &= ~(1<<TOV0);
}

ISR(PCINT2_vect){
	if ((PIND & (1<<PIND7)) == 0){
		//Encender Led <-
		comando = 5;
		//PORTC |= (1<<PORTC5);
	}
	PCIFR &= ~(1<<TOV2);
}