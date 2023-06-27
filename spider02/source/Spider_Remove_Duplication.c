#include<spider.h>

int Spider_Remove_Duplication(container_t * UCT,container_t * PCT,const char * URL)
{
	int flag;
	flag = UCT->Rear;
	while(flag % UCT->Max != UCT->Front)
	{
		if(strncmp(UCT->list[flag].origin_url,URL,strlen(URL)) == 0)
			return 0;
		flag++;
	}
	flag = PCT->Rear;
	while(flag % PCT->Max != PCT->Front)
	{
		if(strncmp(PCT->list[flag].origin_url,URL,strlen(URL)) == 0)
			return 0;
		flag++;
	}
	return 1;
	
}
