#include<io51.h>

void init(void){
	P0=0;
	P1=0;
	P2=0;
	P3=0;
}

int main(void){
	unsigned char i;
	
    // generate frequency = P0 + P1*256, => output = 440, 550, 660 Hz 
	int freq_list_p0[] = {184, 38, 148};
	int freq_list_p1[] = {1, 2, 2};
	int len = sizeof(freq_list_p0)/sizeof(freq_list_p0[0]);

	init();
	
	for(i=0;i<len;i++){
		P0 = freq_list_p0[i]; // target frequency unit Hz.
		P1 = freq_list_p1[i]; // target frequency unit Hz.
		P3 = 1; // Tell Buzzer to catch value.
		while(P2 == 0); // Wait for Buzzer process frequency, if done P2 == 1. 
		P3 = 0; // Send complete, value is not ready.
	}

}