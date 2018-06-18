#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

// boost includes
#include <boost/asio.hpp>

#include "HttpServerTypes.h"

namespace iris {

namespace fileserver {

/**
 * @brief The HttpRequest class. See RFC 2616 for info on Hypertext Transfer Protocol -- HTTP/1.1
 *        Terms used here from that RFC: 
 *        Request-Line, general-header, request-header, entity-header, message-body,
 *        CRLF, SP, Method, Request-URI, HTTP-Version
 */
class HttpRequest
{
public:
    enum RequestState {READ_FIRSTLINE, READ_FIRSTLINE_WAITING, READ_HEADER, READ_HEADER_WAITING, READ_BODY, COMPLETE, CANCELLED};
    
    explicit HttpRequest(boost::asio::ip::tcp::socket&, iris::fileserver::HttpServerSettings&);
    ~HttpRequest();

    void readLineFromBuffer(const std::size_t bytes);
    
    void handleRequestLine(const boost::system::error_code& error, std::size_t bytes_transferred);
    
    /**
     * @brief readFirstline reads Request-Line with method, identifier, protocol version, line break.
     */
    void readRequestLine();
    /**
     * @brief readHeader may be called multiple times (trickling in byte per byte)
     *        this reads the header fields until it reaches CRLF CRLF where message-body commences.
     */
    void readHeader();
    
    void handleHeaderLine(const boost::system::error_code& error, std::size_t bytes_transferred);
    
    /**
     * @brief readBody may be called multiple times (trickling in byte per byte)
     */
    void readBody();
    void read();
    bool isRead() const {return (CANCELLED == m_state) || (COMPLETE == m_state);}
    bool isComplete() const {return (COMPLETE == m_state);}
    bool isHeadRequest() const {return m_isHeadRequest;}
    bool isOptionsRequest() const {return m_isOptionsRequest;}
    bool isRangeRequest() const {return m_isRangeRequest;}
    bool isRangeSatisfiable() const {return m_isRangeSatisfiable;}
    size_t getRangeOffset() const {return m_rangeOffset;}
    size_t getRangeSize() const {return m_rangeSize;}
    
    // request line contents (available if isComplete() is true)
    // method, uri, http version
    std::string getMethod() const {return m_method;}
    std::string getRequestUri() const {return m_requestUri;}
    std::string getHttpVersion() const {return m_httpVersion;}
    // peer address of the incoming connection
    std::string getPeerAddress() const {return m_peerAddress;}
    
    bool hasHeader(const std::string& key) const;
    std::string getHeader(const std::string& key) const;
    iris::fileserver::headerMapType getAllHeaders();
    
private:
    boost::asio::ip::tcp::socket& m_socket;
    iris::fileserver::HttpServerSettings& m_settings;
    std::string m_peerAddress;
    std::string m_method;
    std::string m_requestUri;
    std::string m_httpVersion;
    boost::asio::streambuf m_streamBuf;
    std::string m_dataTemp;
    std::string m_dataBody;
    
    RequestState m_state;
    bool m_isHeadRequest;
    bool m_isOptionsRequest;
    bool m_isRangeRequest;
    bool m_isRangeSatisfiable;
    size_t m_rangeOffset;
    size_t m_rangeSize;
    std::string m_currentHeaderFieldName;// stored because read() is called multiple times and headers can be multi-line
    std::string m_currentHeaderFieldValue;// stored because read() is called multiple times and headers can be multi-line
    iris::fileserver::headerMapType m_headerMap;
    
    /**
     * @brief evaluateHeader Evaluates the header lines once the header was read entirely.
     */
    void evaluateHeader();

};

}// namespace iris

}// namespace fileserver

#endif // HTTPREQUEST_H
