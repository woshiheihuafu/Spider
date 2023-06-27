#include<spider.h>

int Spider_Container_SetNode(container_t * ct,URL_t Node)
{
	if(ct->Max == ct->Cur)
		return -1;
	ct->list[ct->Front] = Node;
	ct->Front = (ct->Front + 1) % ct->Max;
	++ct->Cur;
	return 0;
}
