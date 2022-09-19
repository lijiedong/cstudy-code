#include <stdio.h>
#include <sys/termios.h>
#include <termios.h>
#define QUESTION "Do you want another transaction"
int get_response(char *);
void tty_mode(int how){
    static struct termios original_mode;
    if (how==0) {
        tcgetattr(0 , &original_mode);
    }else {
        tcsetattr(0, TCSANOW, &original_mode);
    }
}
void set_crmode(){
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_cflag &=~ICANON;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}
int main(){
    int response;
    tty_mode(0);
    response = get_response(QUESTION);
    return response;
}
int get_response(char * question){
    printf("%s(y/n)", question);
    int input;
    while (1) {
        switch (input=getchar()) {
            case 'y':
            case 'Y': return 0;
            case 'n':
            case 'N':
            case EOF: return 1;
            default:
                printf("\ncannot understand %c,\n", input);
                printf("Please type y or no \n");
        }
    }
}