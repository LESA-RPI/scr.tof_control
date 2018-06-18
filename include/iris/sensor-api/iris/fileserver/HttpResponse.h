#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include <vector>
#include <map>

// boost includes
#include <boost/asio.hpp>

#include "HttpServerTypes.h"

namespace iris {

namespace fileserver {

class HttpResponse
{
public:
    explicit HttpResponse(boost::asio::ip::tcp::socket& socket);
    ~HttpResponse();
    
    typedef std::map<std::string, std::string> HeaderMapType;
    
    void clearHeader();
    void addToHeader(const std::string& key, const std::string& value);
    void addToHeader(const std::string& key, uint32_t value);
    
    void setData(const std::string& data);
    void setData(const std::vector<char>& data);
    size_t getDataSize() const {return m_data.size();}
    void setCode(unsigned int code) {m_statusCode = code;}
    unsigned int getCode() const {return m_statusCode;}
    void setMessage(const std::string& msg) {m_statusMessage = msg;}
    std::vector<char>& getWritableData() {return m_data;}
    bool isSendSuccess() const {return m_isSendSuccess;}
    
    bool sendHeader();
    void send();
    bool writeToSocket(const std::string& str, bool binary = false);
    bool writeToSocket(const std::vector<char>& vec, bool binary = false);
    bool writeToSocket(const char* buf, size_t size, bool binary = false);
private:
    boost::asio::ip::tcp::socket& m_socket;
    HeaderMapType m_header;
    std::vector<char> m_data;
    bool m_isSendSuccess;
protected:
    std::string m_statusMessage;
    unsigned int m_statusCode;
};

}// namespace iris

}// namespace fileserver

#endif // HTTPRESPONSE_H
