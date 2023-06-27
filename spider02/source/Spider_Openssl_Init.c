#include<spider.h>



SSL_t * Spider_Openssl_Init(int sockfd)
{
	SSL_t * ssl = (SSL_t *)malloc(sizeof(SSL_t));
	//1.加载错误处理函数  openssl有自己独立的错误处理函数，但是必须加载才能使用
	SSL_load_error_strings();
	//2.初始化OPENSSL库函数
	SSL_library_init();
	//3.初始化加密方式和散裂函数 之后发给服务端来选择加密方式
	OpenSSL_add_ssl_algorithms();
	//4.生成认证信息
	ssl->sslctx = SSL_CTX_new(SSLv23_method());
	//5.生成安全套接字
	ssl->sslsocket = SSL_new(ssl->sslctx);
	//6.sockfd已经链接web服务器，使用sockfd对sslsocket进行设置，sslsocket后续与web服务器完成认证过程
	SSL_set_fd(ssl->sslsocket,sockfd);
	//7.安全认证过程
	SSL_connect(ssl->sslsocket);//完成https认证与交互过程
	printf("Spider Step [*] Create OpenSSL ,Safe Connect successfuly!\n");	

	//认证完毕，保留sslsocket，后续与服务器交互都是使用sslsocket
	//不适用传统的send 和 recv（不能加密和解密），应该使用SSL—_read(sslsocket,buf,sizeof(buf))，SSL_write(sslsocket,buf,strlen(buf));//加密发送，解密读取


	return ssl;
}
