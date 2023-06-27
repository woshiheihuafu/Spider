#include<spider.h>

int Spider_Get_Code(const char * Response)
{
	int Code;
	char Status_code[100];
	bzero(Status_code,100);
	//HTTP/1.1 200 ok
	regex_t reg;
	regmatch_t ma[2];
	regcomp(&reg,"HTTP/1.1 \\([^\n\n]\\+\\?\\)\r\n",0);
	if((regexec(&reg,Response,2,ma,0)) == 0)
	{
		snprintf(Status_code,ma[1].rm_eo - ma[1].rm_so + 1,"%s",Response + ma[1].rm_so);
		sscanf(Status_code,"%d ",&Code);//转换成整型传出
		regfree(&reg);
		return Code;
	}
	regfree(&reg);
	return -1;
}
