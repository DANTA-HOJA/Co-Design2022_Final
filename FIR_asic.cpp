#include "FIR_asic.h"

/* 1 cycle ： use multi adders and multi multipliers */
void FIR_asic::FIR_1() {
    if (rst)
    {
        C.write(0x00);
        D.write(0x00);
        rst = false;
    }
    
    const int FIR_LEN = 9;
    const int c[FIR_LEN] = {0, 0, 1, 2, 3, 4, 5, 6, 7};
    sc_uint<8> shift[FIR_LEN] = {0};
    
    sc_uint<8> sum = 0;

    while(1){

        C.write(0); // process not done, write 0.
        wait();

        cout << "B.read() = " << B.read();

        if(B.read() == 1){
            // calculate FIR value
            sum = c[0] * A.read() + 
                c[1] * shift[0] +
                c[2] * shift[1] +
                c[3] * shift[2] +
                c[4] * shift[3] +
                c[5] * shift[4] +
                c[6] * shift[5] +
                c[7] * shift[6] +
                c[8] * shift[7];

            cout << ", A.read() = " << A.read() << ", ";
            cout << "sum = "<< sum << ", ";

            D.write(sum);

            // right-shift
            shift[7] = shift[6];
            shift[6] = shift[5];
            shift[5] = shift[4];
            shift[4] = shift[3];
            shift[3] = shift[2];
            shift[2] = shift[1];
            shift[1] = shift[0];
            shift[0] = A.read();

            for (int i = 0; i < FIR_LEN-1; i++){
                cout << shift[i] << " ";
            }

            C.write(1);
            wait();
        }
        cout << endl;
    }
    /*
        TODO: 
        Design Your one-cycle FIR.
    */
}

/* N cycle ： use one adder and one multiplier */
void FIR_asic::FIR_N() {
    if (rst)
    {
        C.write(0x00);
        D.write(0x00);
        rst = false;
    }

    const int FIR_LEN = 9;
    const int c[FIR_LEN] = {0, 0, 1, 2, 3, 4, 5, 6, 7};
    sc_uint<8> shift[FIR_LEN] = {0};
    
    sc_uint<8> sum = 0;

    while(1){
        
        C.write(0); // process not done, write 0.
        wait();
        
        cout << "B.read() = " << B.read();

        if(B.read() == 1){

            // calculate FIR value
            cout << ", A.read() = " << A.read() << ", ";
            sum += c[0] * A.read();
            wait();
            sum += c[1] * shift[0];
            wait();
            sum += c[2] * shift[1];
            wait();
            sum += c[3] * shift[2];
            wait();
            sum += c[4] * shift[3];
            wait();
            sum += c[5] * shift[4];
            wait();
            sum += c[6] * shift[5];
            wait();
            sum += c[7] * shift[6];
            wait();
            sum += c[8] * shift[7];
            cout << "sum = "<< sum << ", ";

            D.write(sum);
            sum = 0;

            // right-shift
            shift[7] = shift[6];
            shift[6] = shift[5];
            shift[5] = shift[4];
            shift[4] = shift[3];
            shift[3] = shift[2];
            shift[2] = shift[1];
            shift[1] = shift[0];
            shift[0] = A.read();

            for (int i = 0; i < FIR_LEN-1; i++){
                cout << shift[i] << " ";
            }

            C.write(1); // process done, write 1.
            wait();
        }
        cout << endl;
    }
    /*
        TODO:
        Design Your N-cycle FIR.
    */
}