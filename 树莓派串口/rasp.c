
#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
 
int main(){
	int fd;
	if(wiringPiSetup()<0)
		return 1;
	if((fd=serialOpen("/dev/ttyAMA0",9600))<0)
		return 1;
	printf("serial test start ...\n");
	serialPrintf(fd,"hello world!!\n");
	//while(1){
	//	serialPutchar(fd,serialGetchar(fd));
	//	printf("can recive the message..\n");
	//}
	serialClose(fd);
	return 0;
}