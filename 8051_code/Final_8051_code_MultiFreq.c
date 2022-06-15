#include<io51.h>

void init(void){
	P0=0;
	P1=0;
	P2=0;
	P3=0;
}

int main(void){
	unsigned char i;
	int freq_list[2] = {220, 570};
	int len = sizeof(freq_list)/sizeof(freq_list[0]);

	init();
	
	for(i=0;i<len;i++){
		P0 = freq_list[i]; // target frequency unit Hz.
		P3 = 1; // Tell Buzzer to catch value.
		while(P2 == 0); // Wait for Buzzer process frequency, if done P2 == 1. 
		P3 = 0; // Send complete, value is not ready.
	}

}