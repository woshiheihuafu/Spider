#include<spider.h>
int Spider_Start(char * Alpha_url,int Max)
{
	Result_Num = 0;
	Result_Max = Max;
	Result_fd = open("Result.html",O_RDWR|O_CREAT,0664);//UCT 为处理队列
	Spider_Save_Result(NULL,NULL,NULL);
	container_t * UCT = Spider_Container_Create(Result_Max);
	container_t * PCT = Spider_Container_Create(Result_Max);
	SSL_t * ssl = NULL;
	int sockfd;
	char Request[4096];
	URL_t Node;
	URL_t TmpNode;
	strcpy(Node.origin_url,Alpha_url);
	if(Spider_Remove_Duplication(UCT,PCT,Alpha_url))
		Spider_Container_SetNode(UCT,Node);
	//循环爬取
	while(UCT->Cur > 0 && PCT->Cur < Result_Max)
	{
		if(UCT->Cur >= 50)
		{
			printf("Analytical ShutDown Down!\n");
			HTML_SHUTDOWN = 0;
		}
		else if(UCT->Cur <= 10)
		{
			printf("Analytical ShutDown UP!\n");
			HTML_SHUTDOWN = 1;
		}
		printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
		Spider_Container_GetNode(UCT,&TmpNode);
		sockfd = Net_INIT();
		Analytical_URL(&TmpNode);
		Connect_Web(&TmpNode,sockfd);
		Spider_Create_Request(TmpNode,Request);
		if(TmpNode.type)
			ssl = Spider_Openssl_Init(sockfd);
		if((Spider_Download(sockfd,Request,TmpNode,ssl)) == -1)
			continue;//失败从头开始
		Spider_Container_SetNode(PCT,TmpNode);//PCT已处理队列
		Analytical_HTML(TmpNode,UCT,PCT);
	}	
	printf("抓取完毕，结果[%d]",Result_Num);
	return 0;
}
