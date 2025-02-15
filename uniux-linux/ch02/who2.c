#include	<stdio.h>
#include	<utmpx.h>
#include	<fcntl.h>
#include    <stdlib.h>
#include	<unistd.h>
#define	SHOWHOST	/* include remote machine on output */
// 代码里show_info 并没有在main函数中提前声明。
void show_info(struct utmpx *utbufp ){
	if (utbufp->ut_type != USER_PROCESS) {
		// 用户未登录直接跳过
		return;
	}
	printf("%-8.8s", utbufp->ut_user);	/* the logname	*/
	printf(" ");				/* a space	*/
	printf("%-8.8s", utbufp->ut_line);	/* the tty	*/
	printf(" ");				/* a space	*/
	printf("%10ld", utbufp->ut_tv.tv_sec);	/* login time, 登录时间	*/
	printf(" ");				/* a space	*/
#ifdef	SHOWHOST
	printf("(%s)", utbufp->ut_host);	/* the host	*/
#endif
	printf("\n");				/* newline	*/
}
int main(){
	struct utmpx	current_record;	/* read info into here       */
	int		utmpfd;		/* read from this descriptor */
	int		reclen = sizeof(current_record);

	if ( (utmpfd = open(UTMPX_FILE, O_RDONLY)) == -1 ){
		
        perror( UTMPX_FILE );	/* UTMP_FILE is in utmp.h，在macos中UTMP_FILE 是没有定义的，    */
		exit(1); // 这个需要导入stdlib.h 头文件
	}

	while ( read(utmpfd, &current_record, reclen) == reclen ){
		show_info(&current_record);
    }
	close(utmpfd);
	return 0;			/* went ok */
}

