# Spider
1.项目描述： 该项目实现爬取百度百科中英雄联盟相关内容（制作公司，游戏角色等）的标题和描述。
2.涉及技术： 通过URL解析模块提取协议类型、域名、存储路径和文件名。采用未处理队列和已处理队
列实现去重校验模块，以防止重复爬取。利用线程池实现并发任务处理。通过TCP协议连接到服务器，
并使用OPENSSL库完成HTTPS安全认证。使用安全套接字发送请求头、接收响应头等数据。爬取结果保存为HTML文件形式。
