#ifndef SQLIST_H__
#define SQLIST_H__
#define DATASIZE 1024
typedef int datatype;
typedef struct st_node{
    datatype data[DATASIZE];
    int last;
}sqlist;
sqlist *sqlist_create();
void sqlist_create1(sqlist **); // 这里为啥是二级指针我还不太理解

int sqlist_insert(sqlist *, int i ,datatype *);

int sqlist_delete(sqlist *, int i);

int sqlist_find(sqlist *, datatype *);

int sqlist_isempty(sqlist *);

int sqlist_setempty(sqlist *);

int sqlist_getnum(sqlist *);

int sqlist_destory(sqlist *);

void sqlist_display(sqlist *);

int sqlist_union(sqlist *, sqlist *);
#endif