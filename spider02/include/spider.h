#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <regex.h>
//
#include <openssl/ssl.h>
#include <openssl/err.h>
int Result_Max;//抓取最大值
int Result_Num;//当前抓取值
int HTML_SHUTDOWN;//url 解析 开关
int Result_fd;//结果文件描述符

typedef struct
{
	SSL * sslsocket;//安全套接字
	SSL_CTX * sslctx;//认证上下文信息
}SSL_t;
typedef struct
{
	char origin_url[4096];
	char domain[1024];
	char path[1024];
	char fileName[1024];
	char ip[16];
	int port;
	int type;
}URL_t;

typedef struct//头放尾拿   1 2 3 4 5 6
{
	URL_t * list;
	int Front;//016661
	int Rear;// 000122
	int Cur;//  016545
	int Max;//  6
}container_t;

int Analytical_URL(URL_t * Node);//URL解析模块
int Net_INIT(void);//网络初始化
int Connect_Web(URL_t * Node,int Mysock);//TCP链接
int Spider_Create_Request(URL_t Node,char * Request);//创建请求头
int Spider_Download(int sockfd,const char * Request,URL_t Node,SSL_t * ssl);//交互过程，下载
int Spider_Get_Code(const char * Response);//获取响应头中的响应码
SSL_t * Spider_Openssl_Init(int sockfd);//使用openssl完成https认证过程
container_t * Spider_Container_Create(int max);//创建容器
int Spider_Container_SetNode(container_t *,URL_t);//想容器中添加一个节点
int Spider_Container_GetNode(container_t *,URL_t *);//从容器中获取一个节点
int Spider_Remove_Duplication(container_t *,container_t *,const char * link);//去重校验，重复返回 0 , 未重复返回 1
int Analytical_HTML(URL_t ,container_t *,container_t *);//从词条源码中匹配，提取数据
int Spider_Save_Result(const char * title,const char * description,const char * link);//将结果持久化，存储在文件中磁盘保存
int Spider_Start(char * alpha_url,int Result_Max);//爬虫启动接口

