#include<spider.h>

int Spider_Download(int sockfd,const char * Request,URL_t Node,SSL_t * ssl)
{
	int code;//存储整型响应码
	char Buffer[8192];//读取缓冲区
	char Response[4096];//响应头缓冲区
	int Recv_size;//读取大小
	char * POS = NULL;//存储空行地址
	int fd;//存储文件描述符
	bzero(Buffer,sizeof(Buffer));
	bzero(Response,sizeof(Response));
	//判断是https 下载，还是 http 下载
	if(ssl == NULL)
	{
		//交互与下载
		//1.发送请求头
		if(send(sockfd,Request,strlen(Request),0) == -1)
		{
			printf("Spider Step [5] HTTP Send Failed!\n");
			close(sockfd);
			return -1;
		}
		printf("Spider Step [5] HTTP Send Request!\n");
		//2.第一次接收
		if((Recv_size = recv(sockfd,Buffer,sizeof(Buffer),0)) < 0)
		{
			printf("Spider Step [6] HTTP First Recv!\n");
			close(sockfd);
			return -1;
		}
		//3.从buffer，查找空行地址	
		if((POS = strstr(Buffer,"\r\n\r\n")) == NULL)
		{
			printf("strstr Call Failed,error Not Found!\n");
			close(sockfd);
			return -1;
		}
		//4.提取响应头
		snprintf(Response,POS - Buffer + 4,"%s",Buffer);//POS是/r/n/r/n中 / 的地址，+4将/r/n/r/n也包含进去
		printf("Spider Step [7] HTTP Get Response Head\n%s\n",Response);
		//5.获取并判断响应吗，决定是否进行下一步
		if((code = Spider_Get_Code(Response)) == 200)
		{
			//将首次读取的部分响应体写入到文件中
			fd = open(Node.fileName,O_RDWR|O_CREAT,0664);//0664权限
			write(fd,POS + 4,Recv_size - (POS - Buffer + 4));
			//循环读取存储，生育响应体内容
			while((Recv_size = recv(sockfd,Buffer,sizeof(Buffer),0)) > 0)
			{
				write(fd,Buffer,Recv_size);
				bzero(Buffer,sizeof(Buffer));
			}
			printf("Spider Step [8] HTTP Download Successfuly,File = %s,Response Code = %d !\n",Node.fileName,code);
			close(sockfd);
		}
		else
		{
			printf("Spider Step [8] HTTP Response code = %d,Download Failed!\n",code);
			close(sockfd);
			return -1;
		}
	}
	else
	{
		//交互与下载
		//1.发送请求头
		if(SSL_write(ssl->sslsocket,Request,strlen(Request)) == -1)
		{
			printf("Spider Step [5] HTTPS SSL_write Failed!\n");
			close(sockfd);
			free(ssl);
			ssl = NULL;
			return -1;
		}
		printf("Spider Step [5] Send Request!\n");
		//2.第一次接收
		if((Recv_size = SSL_read(ssl->sslsocket,Buffer,sizeof(Buffer))) < 0)
		{
			printf("Spider Step [6] HTTPS First SSL_read!\n");
			close(sockfd);
			free(ssl);
			ssl = NULL;
			return -1;
		}
		//3.从buffer，查找空行地址	
		if((POS = strstr(Buffer,"\r\n\r\n")) == NULL)
		{
			printf("strstr Call Failed,error Not Found!\n");
			close(sockfd);
			free(ssl);
			ssl = NULL;
			return -1;
		}
		//4.提取响应头
		snprintf(Response,POS - Buffer + 4,"%s",Buffer);//POS是/r/n/r/n中 / 的地址，+4将/r/n/r/n也包含进去
		printf("Spider Step [7] HTTPS Get Response Head\n%s\n",Response);
		//5.获取并判断响应吗，决定是否进行下一步
		if((code = Spider_Get_Code(Response)) == 200)
		{
			//将首次读取的部分响应体写入到文件中
			fd = open(Node.fileName,O_RDWR|O_CREAT,0664);//0664权限
			write(fd,POS + 4,Recv_size - (POS - Buffer + 4));
			//循环读取存储，生育响应体内容
			while((Recv_size = SSL_read(ssl->sslsocket,Buffer,sizeof(Buffer))) > 0)
			{
				write(fd,Buffer,Recv_size);
				bzero(Buffer,sizeof(Buffer));
			}
			printf("Spider Step [8] HTTPS Download Successfuly,File = %s,Response Code = %d !\n",Node.fileName,code);
			close(sockfd);
			free(ssl);
			ssl = NULL;
		}
		else
		{
			printf("Spider Step [8] HTTPS Response code = %d,Download Failed!\n",code);
			close(sockfd);
			free(ssl);
			ssl = NULL;
			return -1;
		}
	}
	
	
	return 0;
}
