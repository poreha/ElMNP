#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
//#include <fstream.h> отсутствует хэдер
using namespace std;

int main()
{
FILE *inputf = fopen("Vvodnoe.txt","r");
char str[12];
//int all[8192],i,c;
int a=0,b=0,i=0;
int all[8192];
if(inputf==NULL){
	printf("could not open\n");
	exit(1);
}
	/*while(p!=0){
		sscanf(p,"%d",&all[i++]);
		p=strtok(0," ");
	}*/
				
while(!feof(inputf)){
	//if(
		fgets(str,12,inputf);
		printf("%s",str);
		//scanf("%d%d",&a,&b);
		//printf("%d%d",a,b);
		//c=atoi(a);
		//all[i]=atoi(str);
		//i++;
		//printf("%d ",c/*all[i]*/);
	
					}
fclose(inputf);
return(0);
}
