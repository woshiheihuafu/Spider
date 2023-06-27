#include<spider.h>

int main(void)
{
	char * alpha_url = "https://baike.baidu.com/item/%E5%8E%9F%E7%A5%9E/23583622";
	//char * alpha_url = "http://n.sinaimg.cn/sinakd10114/386/w640h1346/20211101/538f-500fac835288d366216f3a0ecfb391fc.jpg";
	//char * alpha_url = "https://baike.baidu.com/item/%E5%8E%9F%E7%A5%9E/23583622";
	Spider_Start(alpha_url,50);
	return 0;
}
