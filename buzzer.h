#ifndef	__BUZZER_H
#define __BUZZER_H
#include "systemc.h"
#include "math.h"

// speed = 800 MHz

SC_MODULE(Buzzer)
{
	sc_in_clk			    clk;
	sc_in<sc_uint<1> >		reset;
	sc_in<sc_uint<8> >      p_freq;  // P0: 8051 -> FIR, Prepared value which needs calculate. (port0o)
	sc_in<sc_uint<8> >      p_st;  	// P3: 8051 -> FIR, Tell FIR can catch value. (port3o)
	sc_out<sc_uint<8> >     p_done;  	// P2: FIR -> 8051, FIR calculate complete or not. (port2i)
	sc_out<sc_uint<8> >     p_wave;  	// P1: FIR -> 8051, FIR send result value back. (port1i)
    sc_signal<bool> rst;

	SC_CTOR(Buzzer)
	{
        rst = true;
		/* switch 1-cycle or N-cycle. */
		SC_CTHREAD(freq_generator, clk.pos());
		// SC_CTHREAD(FIR_N, clk.pos());
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
        int target_freq = 0;
        int cycle = 5;

        /* Pin connect in top.h */
        // buzzer_A = new Buzzer("buzzer_A");
        // buzzer_A->clk(clk);
        // buzzer_A->reset(reset);
        // buzzer_A->p_freq(port0o);
        // buzzer_A->p_st(port3o);
        // buzzer_A->p_done(port2i);
        // buzzer_A->p_wave(port1i);

        while(1){

            p_done.write(0); // process not done, write 0.
            wait();

            cout << "p_st.read() = " << p_st.read();

            if(p_st.read() == 1){
                
                cycle = 5; // 每次新接到的頻率跑五個週期
                target_freq = p_freq.read();
                cout << ", target_freq = " << target_freq << " Hz";
                full_wave = int(100*pow(10.0, 6)/target_freq); // 計算 100MHz 是 輸入頻率的幾倍，100MHz 是因為 buzzer clk 設 100MHz 
                cout << ", full_wave = " << full_wave << " counts";
                half_wave = int(full_wave/2); // 半個週期，切換輸出訊號
                cout << ", half_wave = " << half_wave << " counts" << endl;
                while(cycle > 0){
                    cout << "cycle = " << 5-cycle << endl;
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