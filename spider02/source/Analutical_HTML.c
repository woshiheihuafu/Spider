#include<spider.h>

int Analytical_HTML(URL_t Node,container_t * UCT,container_t * PCT)
{
	int fd;//文件描述符
	int Fsize;//文件大小
	char * html = NULL;//html文件首地址
	char * Jhtml = NULL;//记录遍历偏移
	URL_t tempNode;
	/*1.打开源码文件*/
	fd = open(Node.fileName,O_RDWR);
	/*2.获取文件大小*/
	Fsize = lseek(fd,0,SEEK_END);
	/*3.私有映射*/
	if((html = mmap(NULL,Fsize,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0)) == MAP_FAILED)
	{
		perror("mmap HTML Failed!\n");
		return -1;
	}
	Jhtml = html;//html是首地址
	close(fd);
	/*4.定义正则表达式变量*/
	regex_t Treg,Dreg,Nreg;
	regmatch_t Tma[2],Dma[2],Nma[2];
	/*5.创建正则表达式*/
	regcomp(&Treg,"<h1 >\\([^<]\\+\\?\\)</h1>",0);
	regcomp(&Dreg,"meta name=\"description\" content=\"\\([^\"]\\+\\?\\)\">",0);
	regcomp(&Nreg,"<a[^>]\\+\\?href=\"\\(/item[^\"]\\+\\?\\)\"[^>]\\+\\?>[^<]\\+\\?</a>",0);
	/*6.匹配与存储*/
	char Title[1024],Desc[8192],Newlink[8192];
	bzero(Title,sizeof(Title));
	bzero(Desc,sizeof(Desc));
	bzero(Newlink,sizeof(Newlink));
	
	if((regexec(&Treg,html,2,Tma,0)) == 0)
		snprintf(Title,Tma[1].rm_eo-Tma[1].rm_so+1,"%s",html+Tma[1].rm_so);
	if((regexec(&Dreg,html,2,Dma,0)) == 0)
		snprintf(Desc,Dma[1].rm_eo-Dma[1].rm_so+1,"%s",html+Dma[1].rm_so);
	++Result_Num;//提取了一个结果，+1
	//持久化模型 （持久化存储）
	Spider_Save_Result(Title,Desc,Node.origin_url);
	/*7.分析更多词条链接*/
	if(HTML_SHUTDOWN)
	{
		while((regexec(&Nreg,html,2,Nma,0)) == 0)
		{
			snprintf(Newlink,Nma[1].rm_eo-Nma[1].rm_so+24,"https://baike.baidu.com%s",html+Nma[1].rm_so);
			//新链接进入爬取流程
			//去重复校验
			if(Spider_Remove_Duplication(UCT,PCT,Newlink))
			{
				strcpy(tempNode.origin_url,Newlink);
				Spider_Container_SetNode(UCT,tempNode);
			}
			bzero(Newlink,sizeof(Newlink));
			html+=Nma[0].rm_eo;
			if(UCT->Cur == UCT->Max)
			{
				printf("Container UCT is Full!\n");
				break;
			}
			printf("full = %d,cur = %d\n",UCT->Max,UCT->Cur);
		}
	}
	unlink(Node.fileName);
	regfree(&Treg);regfree(&Dreg);regfree(&Nreg);
	munmap(Jhtml,Fsize);
	return 0;
	
	
}	
