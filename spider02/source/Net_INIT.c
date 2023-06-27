#include<spider.h>

int Net_INIT(void)
{
	//struct sockaddr_in Myaddr;
	//bzero(&Myaddr,sizeof(Myaddr));
	//Myaddr.sin_family = AF_INET;
	//Myaddr.sin_port = htons(8080);
	//Myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	/*客户端会自动为服务端分配端口号，可以不bind，除非linux系统中rlogin命令应当调用bind函数绑定一个未用的保留端口号，还有当客户端需要用指定的网络设备接口和端口号进行通信等等*/
	int Mysock;
	if((Mysock = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("Socket Create Failed!");
	}
	//Bind
	printf("Spider step[2] Net Init Successfuly,Mysock = %d\n",Mysock);
	return Mysock;
	
}
