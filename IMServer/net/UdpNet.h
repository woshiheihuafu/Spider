#pragma once
#include"INet.h"

class UdpNet:public INet
{
public:
	UdpNet(INetMediator* pMediator);
	~UdpNet();	
	//初始化网络
	bool InitNet();
	//关闭网络
	void UninitNet();
	//发送数据
	bool SendData(long ISendIp,char* buf,int nLen );
protected:
	//接受数据
	void RecvData();//只要外部不调用尽量设成 protected
	SOCKET m_sock;
	bool m_isStop;
	HANDLE m_hThreadHandle;
	static unsigned int _stdcall RecvThrad(void* lpvoid);
	
};