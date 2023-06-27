#include<spider.h>

int Analytical_URL(URL_t * Node)
{
	bzero(Node->domain,sizeof(Node->domain));
	bzero(Node->path,sizeof(Node->path));
	bzero(Node->fileName,sizeof(Node->fileName));
	bzero(Node->ip,sizeof(Node->ip));
	int flag = 0;//遍历url下标
	int j = 0;//存储下标
	int start_len;//起始长度
	int fsize;//文件名长度
	const char * http_array[]={"http://","https://",NULL};
	/*1.辨别协议类型*/
	if(strncmp(Node->origin_url,http_array[0],strlen(http_array[0])) == 0)
	{
		Node->type = 0;//http协议的url
		Node->port = 80;
		start_len = strlen(http_array[0]);	
	}
	else
	{
		Node->type = 1;//http协议的url
		Node->port = 443;
		start_len = strlen(http_array[1]);
	}
	/*2.获取网站域名*/
	for(flag = start_len;Node->origin_url[flag] != '/' && Node->origin_url[flag] != '\0';flag++)
	{
		Node->domain[j] = Node->origin_url[flag];
		j++;
		
	}
	j = 0;
	/*3.获取文件名长度*/
	for(flag = strlen(Node->origin_url);Node->origin_url[flag] != '/';flag--,fsize++);
	/*4.获取资源文件名*/
	for(flag = strlen(Node->origin_url) - fsize + 1;Node->origin_url[flag] != '\0';flag++)
	{
		Node->fileName[j] = Node->origin_url[flag];
		j++;
	}
	j = 0;
	/*5.获取路径*/
	for(flag = start_len + strlen(Node->domain);flag < (int)strlen(Node->origin_url) - fsize + 1;flag++)
	{
		Node->path[j] = Node->origin_url[flag];
		j++;
	}
	/*6.获取ip地址   网络字节序 -> 字符串*/
	struct hostent * ent = NULL;
	if((ent = gethostbyname(Node->domain)) == NULL )
	{
		printf("GetHostByName Call Failed!\n");
		exit(0);
	}
	inet_ntop(AF_INET,ent->h_addr_list[0],Node->ip,16);//将地址表中的大端序ip，转成字符串存在ip数组中
	printf("Spider Step [1] Analytical_URL successfuly:\norigin_url=%s\ndomain=%s\npath=%s\nfileName=%s\nip=%s\nport=%d\ntype=%d\n",Node->origin_url,Node->domain,Node->path,Node->fileName,Node->ip,Node->port,Node->type);//第一步，解析URL，完成！
	return 0;
}
