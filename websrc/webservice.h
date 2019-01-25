/**
 * @file webservice.h
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-11
 */
#pragma once
#include <string>

using namespace std;
class WebService
{
public:
    WebService();
    virtual ~WebService();

    /**
     * @brief 指定webservice监听的端口
     *
     * @param port
     */
    void listen(int port);

    /**
     * @brief 等待客户端连接
     *
     * @return 
     */
    int accept();

    /**
     * @brief 处理客户端的连接
     *
     * @paramconnfd
     */
    void handle_client(int connfd);

    /**
     * @brief 响应http的请求报文
     *
     * @param s 
     * @param header
     */
    void responed_http(const int& s, tuple<string, string, string> header);

    /**
     * @brief 退出
     */
    void exit();
private: 
    int         m_servicefd;
};


struct HttpHelper
{
    static tuple<string, string, string> parse_head(const string& request);
    static string generateResponHeader(int err);
    
    struct Splite
    {
        Splite(const string& str, size_t start = 0) :m_str(str) ,m_start(start) { }
        bool operator ()(char c, string& ret)
        {
            auto index = m_str.find(c, m_start);
            if (std::string::npos == index)
                return false;
            ret = m_str.substr(m_start, index - m_start);
            m_start = index + 1;
            return true;
        }
        string m_str;
        size_t m_start;
    };
};


