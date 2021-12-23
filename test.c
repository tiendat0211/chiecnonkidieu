#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


void Updatehidden(char*hidden,char *a,char*answer){
    for(int i =0;i<strlen(answer);i++){
        if(answer[i]== a[0] ) hidden[i]=a[0];
    }
}

int main(){
    char s1[50]="pham tien dat";
    char s2[50]="**** **** ***";
    char s[50];
    strcpy(s,"a");
    strcat(s,"1");
    printf("%s\n",s);
    Updatehidden(s2,s,s1);
    printf("%s\n",s2);
    
}