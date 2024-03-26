#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <math.h>

int main(){
	
	stdio_init_all();
	adc_init();
	adc_gpio_init(27);

	adc_select_input(1);
	while(true) {
		sleep_ms(1000);
		uint16_t adler = adc_read();
		float Vreal = adler * (3.3 / 4096);
		printf("ADC: %d\n", adler);
		printf("Tension: %.2f\n", Vreal);
		//float Rntc=(Vreal*4700)/(3.3-Vreal);
		float I=(3.3-Vreal)/(4700);
		float Rntc = Vreal / I; 
		printf("Rntc = %.2f\n", Rntc);

		
		float steinhart = 4700 / Rntc;
		steinhart = log(steinhart);
		steinhart /= 3380;
		steinhart+= 1 /(25+273.15);
		steinhart = 1 /steinhart;
		steinhart -= 273.15;

		float A= 3380*25;
		float B= 298*(log(4700/Rntc))+3380;
		float temp = (A/B);



		printf("temp: %.2f\n",steinhart);
		printf("temp2: %.2f\n",temp);
	}
}
