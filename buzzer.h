#ifndef	__BUZZER_H
#define __BUZZER_H
#include "systemc.h"
#include "math.h"

// speed = 800 MHz

SC_MODULE(Buzzer)
{
	sc_in_clk			    clk;
	sc_in<sc_uint<1> >		reset;
    // generate frequency = P0 + P1*256 => concat two 8 bit output pin
	sc_in<sc_uint<8> >      p_freq_0;   // P0: 8051 -> buzzer , frequency wants to generate. (port0o)
    sc_in<sc_uint<8> >      p_freq_1;   // P1: 8051 -> buzzer , frequency wants to generate. (port1o)
	sc_in<sc_uint<8> >      p_st;  	    // P3: 8051 -> buzzer , Tell buzzer can catch value. (port3o)
	sc_out<sc_uint<8> >     p_done;     // P2: buzzer -> 8051, buzzer calculate complete or not. (port2i)
	sc_out<sc_uint<8> >     p_wave;     // P1: output_signal (port1i)
    sc_signal<bool> rst;

	SC_CTOR(Buzzer)
	{
        rst = true;
		SC_CTHREAD(freq_generator, clk.pos());
	};

    void freq_generator() {
        if (rst)
        {
            p_done.write(0x00);
            p_wave.write(0x00);
            rst = false;
        }

        long double counter = 0;
        long double full_wave = 0;
        long double half_wave = 0;
        int target_freq_0 = 0;
        int target_freq_1 = 0;
        int target_freq = 0;
        int cycle = 5;

        /* Pin connect in top.h */
        // buzzer_A = new Buzzer("buzzer_A");
		// buzzer_A->clk(clk);
		// buzzer_A->reset(reset);
		// buzzer_A->p_freq_0(port0o);
		// buzzer_A->p_freq_1(port1o);
		// buzzer_A->p_st(port3o);
		// buzzer_A->p_done(port2i);
        // buzzer_A->p_wave(port1i);

        while(1){

            p_done.write(0); // process not done, write 0.
            wait();

            cout << "p_st.read() = " << p_st.read();

            if(p_st.read() == 1){
                
                cycle = 3; // 每次新接到的頻率跑3個週期
                target_freq_0 = p_freq_0.read();
                target_freq_1 = p_freq_1.read();
                target_freq = target_freq_0 + target_freq_1*256;
                cout << ", target_freq = " << target_freq << " Hz";
                full_wave = int(100*pow(10.0, 6)/target_freq); // 計算 100MHz 是 輸入頻率的幾倍，100MHz 是因為 buzzer clk 設 100MHz 
                cout << ", full_wave = " << full_wave << " counts";
                half_wave = int(full_wave/2); // 半個週期，切換輸出訊號
                cout << ", half_wave = " << half_wave << " counts" << endl;
                while(cycle > 0){
                    cout << "cycle = " << 3-cycle << endl;
                    counter = half_wave;
                    // 前半個週期
                    p_wave.write(1);
                    while(counter > 0){
                        counter--;
                        wait();
                    }
                    // 前半個週期
                    counter = half_wave;
                    p_wave.write(0);
                    while(counter > 0){
                        counter--;
                        wait();
                    }
                    cycle--;
                }
                p_done.write(1);
                wait();
            }
            cout << endl;
        }
    };
	
};

#endif