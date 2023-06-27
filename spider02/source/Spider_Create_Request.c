#include<spider.h>

int Spider_Create_Request(URL_t Node,char * Request)
{
	bzero(Request,4096);
	sprintf(Request,"GET %s HTTP/1.1\r\n"\
			"Accept:text/html,application/xhtml+xml;q=0.9,image/webp;q=0.8\r\n"\
			"User-Agent:Mozilla/5.0 (x11; linux x85_64)\r\n"\
			"Host:%s\r\n"\
			"Connection:close\r\n\r\n",Node.origin_url,Node.domain);
	printf("Spider Step [4] Create Request Sucessfully!\n%s\n",Request);
	return 0;


}
