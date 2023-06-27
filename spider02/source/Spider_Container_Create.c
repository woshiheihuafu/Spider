#include<spider.h>

container_t * Spider_Container_Create(int max)
{
	container_t * ct = (container_t *)malloc(sizeof(container_t));
	if((ct->list = (URL_t *)malloc(sizeof(URL_t) * max)) == NULL)
	{
		perror("Container_Create Failed,list Malloc Error\n");
		exit(0);
	}
	ct->Front = 0;
	ct->Rear = 0;
	ct->Max = max;
	ct->Cur = 0;
	return ct;
}
