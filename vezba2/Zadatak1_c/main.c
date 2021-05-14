#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long ms = 0;

int main()
{

	unsigned long vreme = 500;
	DDRB |= (0X01 << 5);

	TCCR0A = 0X02;
	TCCR0B = 0X03;
	OCR0A = 249;
	TIMSK0 = 0X02;

	sei();

	while(1)
	{
		PORTB |= (1 << 5);
		my_delay(vreme);

		PORTB &= ~(1 << 5);
		my_delay(vreme);
	}
}

ISR(TIMER0_COMPA_vect)
{
	ms++;
}

void my_delay(unsigned long milisekunde)
{

	unsigned long t0;
	t0 = ms;
	while ((ms - t0) < milisekunde){};

}
