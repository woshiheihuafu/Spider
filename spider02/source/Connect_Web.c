#include<spider.h>

int Connect_Web(URL_t * Node,int Mysock)
{
	struct sockaddr_in WebAddr;
	bzero(&WebAddr,sizeof(WebAddr));
	WebAddr.sin_family = AF_INET;
	WebAddr.sin_port = htons(Node->port);
	inet_pton(AF_INET,Node->ip,&WebAddr.sin_addr.s_addr);
	if((connect(Mysock,(struct sockaddr *)&WebAddr,sizeof(WebAddr))) == -1)
	{
		perror("Connect Web Failed!\n");
		exit(0);
	}
	printf("Spider Step[3] Connect Web successfuly!\n");
	return 0;
}
