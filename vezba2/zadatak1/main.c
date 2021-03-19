#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char ledovka = 0x00;
unsigned long t0_cnt = 0;

ISR(TIMER0_COMPA_vect)
{
	t0_cnt++;
if(t0_cnt == 125)
		{
		    t0_cnt = 0;
		    ledovka ^= 1 << 5;
		    PORTB = ledovka;
		}
}


int main(){
	DDRB |= 1 << 5;

	TCCR0A = 0x02;
	TCCR0B = 0x04;
	OCR0A = 249;
	TIMSK0 = 0x02;
	sei();


	while(1);

	return 0;

}

