#include <stdio.h>
#include <stdlib.h>
#include "project.h"
static int i =100;
void funcTest(void){
    printf("[%s]:i = %d \n",__FUNCTION__, i);
    exit(0);
}