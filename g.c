#include <stdio.h>
//
void gp(int* x, int y){

    int i1_4, i2_8, i3_12, i4_16, *i5_24, i6_28;

    i1_4 = 3;
    i2_8 = 0;
    i3_12 = 0;
    i4_16 = 0;
    i5_24 = x;
    i6_28 = y;

    *i5_24 = 2;
    i3_12 = 1;

    while(1){

        //L2
        if(i3_12 >= i6_28){
            // L10
            return;// i3_12
        } else {
            // L2 after
            if(i1_4 < i6_28*i6_28){
                // L9
                i4_16 = 1;
                i2_8 = 0;

                while(1){
                    // L3
                    if(i2_8 < i3_12){
                        // L6
//                        eax = i1_4;
//                        rcx = 4 * i2_8;
//                        rdx(*) = i5_24;
//                        rdx(*) = 4 * i2_8 + i5_24;
//                        ecx = *rdx;
//                        divl = i1_4/(*(4 * i2_8 + i5_24));
//                        eax = i1_4%(*(4 * i2_8 + i5_24));
                        if(i1_4%(*(i2_8 + i5_24)) != 0){  // (4 * i2_8 + i5_24)
                            // L4
                            i2_8 = i2_8 + 1;
                            // goto L3
                        } else {
                            i4_16 = 0;
                            break; // goto L5
                        }


                    } else {
                        break; // goto L5
                    }
                }

                // L5
                if(i4_16 == 0){
                    // goto L7
                } else {
                    // L5 after  todo ???
                    int eaxx = i3_12;
                    i3_12 = i3_12 + 1;
                    long raxx = eaxx;
//                    rdx=4*raxx;
//                    raxx = i5_24;
//                    rdx = raxx + rdx;
//                    *rdx = i1_4;
                    *(raxx + i5_24) = i1_4;  //(4*raxx + i5_24)
                    // goto L7
                }
                // L7
                i1_4 = i1_4 + 2;
                //goto L2

            } else {
                // L10
                return;// i6_28*i6_28
            }
        }
    }

    return;
}
