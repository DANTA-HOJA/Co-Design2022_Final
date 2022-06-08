#include<io51.h>

void init(void){
	P0=0;
	P1=0;
	P2=0;
	P3=0;
}

int main(void){
	unsigned char i;
	
	init();
	
	P0 = 220; // target frequency unit Hz.
	P3 = 1; // Tell Buzzer to catch value.
	while(P2 == 0); // Wait for Buzzer process frequency, if done P2 == 1. 
	P3 = 0; // Send complete, value is not ready.

	// for(i=0;i<11;i++){
		
	// 	P0 = i; // Value already prepared.
	// 	P3 = 1; // Tell FIR to catch value.
	// 	while(P2 == 0); // Wait for FIR does calculate, if done P2 == 1. 
	// 	P3 = 0; // Send complete, value is not ready.
	// }
}