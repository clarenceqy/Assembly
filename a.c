#include<stdio.h>
int NP = 11;
int ask(){
    int i;
    puts("Press CTRL+C to exit."); 
    do {
        printf("Enter a positive integer for key size: ");
        scanf("%d", &i);
        if (i != 0) {
            if (i > 4) {
                if (i == NP) {
                    printf("%d is just right!\n", i);
                    return i;
                } 
                else if(i < NP){
                    puts("Whoops! That's too small. Please enter a higher number!");
                }
                else {
                    puts("Whoops! That's too big. Please enter a smaller number!");
                }
            } else {
                puts("Whoops! That's too small. Please enter a higher number!");
            }
        } else {
            puts("Sorry, did not understand your input. Repeating question.");
        }
    } while (1);

}
