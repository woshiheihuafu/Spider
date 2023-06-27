#include<spider.h>

int Spider_Container_GetNode(container_t * ct,URL_t * Node)
{
	if(ct->Cur == 0)
		return -1;
	*Node = ct->list[ct->Rear];
	ct->Rear = (ct->Rear + 1) % ct->Max;
	--ct->Cur;
	return 0;
}
