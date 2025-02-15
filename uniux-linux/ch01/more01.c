#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 1
#define LINELEN 12
void do_more(FILE *);
int see_more();
int main (int ac,char* av[]){
    FILE * fp;
    printf("argument count:%d\n", ac);
    if (ac==1) {
        // 如果参数只有一个就，就走这段逻辑，./more01.o 只运行这个程序就是一个参数
        printf("%s\n", av[0]);
        do_more(stdin);
    }else {
        printf("%s\n", av[1]);
        // 这个是判断命令行中携带的参数是否真的是超过了1个，但是我感觉外面有if判断
        // 似乎不需要这个。
        while (--ac) {
            //av里面存储的是命令行执行的参数，第二个参数就是执行的文件名
            if ((fp=fopen(* ++av,"r"))!=NULL) {
                do_more(fp);
                fclose(fp);
            }else {
                exit(1);
            }
        }
    }
    return 0;
}
void do_more(FILE *fp){
    char line[LINELEN];
    int num_of_lines =0;
    // 这里只是声明see_more函数
    int see_more(),reply;
    while(fgets(line, LINELEN, fp)){
        if (num_of_lines == PAGELEN) {
            reply = see_more();
            if (reply ==0) {
                break;
            }
            num_of_lines -= reply;
        }
        if (fputs(line, stdout)==EOF) {
            exit(1);
        }
        num_of_lines ++;
    }
}
int see_more(){
    int c;
    printf("\033[7m more? \033[m");		/* reverse on a vt100	*/
	while( (c=getchar()) != EOF )			/* get response	*/
	{
		if ( c == 'q' )			/* q -> N		*/
			return 0;
		if ( c == ' ' )			/* ' ' => next page	*/
			return PAGELEN;		/* how many to show	*/
		if ( c == '\n' )		/* Enter key => 1 line	*/
			return 1;		
	}
	return 0;
}