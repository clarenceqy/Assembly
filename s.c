#include <stdio.h>


int ncmp = 0;

// swap(a,b)
void x(int *a, int *b) {
    int *i_24 = a;
    int *i_32 = b;
    int i_4 = *i_24;
    *i_24 = *i_32;
    *i_32 = i_4;
    return;
}

void s(int *a, int b) {
    char *i_24 = (char *)a;
    int i_28 = b;
    int i_4 = 1;
    int i_8;

    while (1) {
        // L3
        if (i_4 < i_28) {
            // L7
            i_8 = i_4;
            while (1) {

                // L4
                if (i_8 <= 0) {
                    // L5
                    i_4 = i_4 + 1;
                    break;// goto L3
                } else {
//            rdx = 4*i_8-4;
//            rax = i_24;  // does g.asm fault, xxi_24= i_24+xxxxx
//            rax = i_24 + 4*i_8-4;

//            edx = *(i_24 + 4*i_8-4);
//            rcx = 4*i_8;
//            rax = i_24;
//            rax = i_24 + 4*i_8;
//            eax = *(i_24 + 4 * i_8);
                    if (*(int *)(i_24 + 4 * i_8 - 4) < *(int*)(i_24 + 4 * i_8)) {
                        // L6
//                rdx = 4*i_8-4;
//                rax = i_24;
//                rdx = i_24 + 4*i_8-4;

//                rcx = 4*i_8;
//                rax = i_24;
//                rax = i_24 + 4*i_8;
                        x((int *)(i_24 + 4 * i_8 - 4), (int *)(i_24 + 4 * i_8));
                        ncmp = ncmp + 1;
                        i_8 = i_8 - 1;
                        // L4
                        continue;//goto L4
                    } else {
                        // L5
                        i_4 = i_4 + 1;
                        break;// goto L3
                    }

                }
            }
        } else {
            return;
        }
    }
}
