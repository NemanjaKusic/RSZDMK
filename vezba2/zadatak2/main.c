#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long t0 = 0, us = 0, us_pom = 0;
int fi = 1;
int smer = 1;

ISR(TIMER0_COMPA_vect)
{
	us++;
	us_pom++;

	if(us_pom  == 1000)
	{
		us_pom = 0;
		if(smer == 1)
		{
			if(fi < 255)
				fi++;
			else
				smer = 0;
		}
		else
		{
			if(fi > 0)
				fi--;
			else
				smer = 1;
		}

	}

	if(t0 + 255 == us)
		t0 = us;

	if(us < t0 + fi)
		PORTB |= 1 << 5; //LED ON
	else
		PORTB &= ~(1 << 5); //LED OFF
}


int main()
{
	DDRB |= 1 << 5; //PB5 je izlaz

	TCCR0A = 0x02; //tajmer 0: CTC mod
	TCCR0B = 0x01; //tajmer 0: fclk = fosc
	OCR0A = 159; //perioda tajmera 0: 159 Tclk (OCR0A + 1 = 160)

	TIMSK0 = 0x02; //dozvola prekida tajmera 0

	sei(); //I = 1 (dozvola prekida)

	while (1);

	return 0;
}
