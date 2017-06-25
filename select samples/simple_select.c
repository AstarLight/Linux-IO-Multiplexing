#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{
	fd_set rd;
	struct timeval tv;
	int err;
	
	while(1)
	{
		FD_ZERO(&rd);
		FD_SET(stdin,&rd);
		
		tv.sec = 5;
		tv.usec = 0;
		err = select(stdin+1,&rd,NULL,NULL,&tv);
		
		if(err == 0) //超时
		{
			printf("select time out!\n");
		}
		else if(err == -1)  //失败
		{
			printf("fail to select!\n");
		}
		else  //成功
		{
			printf("data is available!\n");
		}
	}
	
	return 0;
}