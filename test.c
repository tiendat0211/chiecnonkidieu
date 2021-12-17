#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int main(){
    char buffer[1000]="\0";
    char s1[50]="Ban ten la gi";
    char s2[50];
    char s3[50]="pham tien dat";
    char chu[10]="\0";
    char *c;
    //printf("Nhap cau tra loi : ");
    //scanf("%[^\n]s",s2);
    //printf("%s\n%s\n",s2,s3);
    //fgets(s2,sizeof(s2),stdin);
    c=strtok(s3," ");
    printf("%s\n",c);
    c=strtok(NULL," ");
    printf("%s\n",c);
    c=strtok(NULL," ");
    printf("%s\n",c);
    
}