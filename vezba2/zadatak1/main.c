#include <avr/io.h>
#include <avr/interrupt.h>
//treptanje f=2Hz
unsigned long miliseconds=0;

ISR(TIMER0_COMPA_vect)
{
	miliseconds++;
}

unsigned char my_delay(unsigned long miliseconds) {
	if (miliseconds == 500) {
		PORTB ^= 1<<5 ; //xor, invertuje stalno PB5
		return 1;
	}
	return 0;
}

int main(void)
{
	//inicijalizacija tajmera 0:
	TCCR0A = 0x02; // CTC mod
	TCCR0B = 0x03; // fclk = fosc/64
	OCR0A = 249; //perioda tajmera 0: 250 Tclk (OCR0A + 1 = 250)
	TIMSK0 = 0x02; //dozvola prekida tajmera 0
	//usled dostizanja vrednosti registra OCR0A

	sei(); //I = 1 (dozvola prekida)

	DDRB |= 1 << 5; //PB5 je izlaz za diodu
	PORTB |= 1<<5; //setovanje diode na 1 (led ON)

	while(1) {
		if (my_delay(miliseconds)== 1) {
			//ako je vracena 1, znaci da treba resetovati milisekunde
			miliseconds=0;
		}
	}
	return 0;
}
