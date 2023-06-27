#include<spider.h>

int Spider_Save_Result(const char * Title,const char * Desc,const char * This_link)
{
	printf("title:%s\ndesc:%s\nlink:%s\n",Title,Desc,This_link);
	char Result[8192];
	bzero(Result,sizeof(Result));
	//html首部
	const char * start = "<html>\r\n<head>\r\n<meta http-equiv=\"Content_Type\" content=\"text/html\";charset=utf-8\">\r\n/<head>\r\n<table border=\"1\" cellspacing=\"0\" cellpadding=\"0\" width=\"1900\">\r\n<caption>爬虫抓取数据集<caption>\r\n<tr><th>ID</th><th>百科词条主标题</th><th>描述信息</th><th>本条词条地址</th>\r\n";
	//html尾部
	const char * end = "</table>\r\n</html>\r\n";
	if(Result_Num == 0)
	{
		write(Result_fd,start,strlen(start));
		return -1;
	}
	sprintf(Result,"<tr id=%d><td name=\"id\">%d</td><td name=\"Title\">%s</td><td name=\"description\">%s</td><td name=\"link\">%s</td></tr>\r\n",Result_Num,Result_Num,Title,Desc,This_link);
	write(Result_fd,Result,strlen(Result));
	if(Result_Num == Result_Max)
	{
		printf("-------------------\n");
		write(Result_fd,end,strlen(end));
		close(Result_fd);
	}
	return 0;
}
