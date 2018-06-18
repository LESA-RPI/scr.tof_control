#ifndef HTTPLISTENER_H
#define HTTPLISTENER_H

// STL includes
#include <string>

// boost includes
#include <boost/asio.hpp>

// iris includes
#include "iris/synchronization/Mutex.h"
#include "iris/threads/Thread.h"

#include "HttpServerTypes.h"
#include "HttpConnectionHandler.h"
#include "ResponseDataCache.h"

namespace iris {

namespace fileserver {

class IoServiceThread : public iris::threads::Thread
{
public:
    explicit IoServiceThread(boost::asio::io_service& ioService);
    virtual ~IoServiceThread();
    
    virtual unsigned int execute();
private:
    IoServiceThread(IoServiceThread&);// forbid
    IoServiceThread& operator=(const IoServiceThread&);// forbid

    boost::asio::io_service& m_ioService;
};

/**
 * @brief The HttpServer class. This class allows to serve contents from the local machine. 
 *        The HttpServerSettings are passed as a reference in the constructor.
 *        It can be useful to also pass a callback for status messages, so the HttpServer's status can be observed.
 * 
 * @note Internally uses HttpRequest, HttpResponse, HttpConnectionHandler. There is no need for using them as standalone.
 * @note ResponseDataCache is also useful for caching via other non-ethernet protocols like CAN.
 */
class HttpServer
{
public:
    typedef std::vector<HttpConnectionHandler*> HandlerContainer;
    
    explicit HttpServer(iris::fileserver::HttpServerSettings& settings, iris::fileserver::CALLBACK_STATUSMESSAGE pfnStatusMessage);
    ~HttpServer();
    
    /**
     * @brief startListening Must be run before any contents can be served.
     *        Will start listening according to settings that were provided in the constructor.
     * @note Use servePage or serveFile to actually start serving contents, this may happen before startListening.
     */
    void startListening();
    
    /**
     * @brief stopListening Stops any content from being served. Resume with startListening.
     */
    void stopListening();
    bool isListening() const {return m_ioServiceThread != 0;}
    
    /**
     * @brief getHostName Returns the host name where we are listening.
     * @return A string with the host name.
     */
    std::string getHostName() const {return m_hostName;}
    /**
     * @brief getPort Returns the port where we are listening.
     * @return integral port number.
     */
    unsigned int getPort() const {return m_currentPort;}
    
    /**
     * @brief servePage Takes a string for serving at the specified path. Useful to serve html pages etc.
     * @param path The path where the string will be available
     * @param content A string that is displayed as-is on accessing the specified path
     */
    void servePage(const std::string& path, const std::string& content);
    
    /**
     * @brief serveFile Takes a file from disk and serves its contents (along with metadata)
     * @param path The path where the file content will be available
     * @param filename Path including filename to load the file contents from
     */
    void serveFile(const std::string& path, const std::string& filename);
    
private:
    IoServiceThread* m_ioServiceThread;
    iris::fileserver::HttpServerSettings& m_settings;
    HandlerContainer m_handlers;
    ResponseDataCache m_responseDataCache;
    std::string m_hostName;
    unsigned int m_currentPort;
    boost::asio::io_service* m_ioService;
    boost::asio::ip::tcp::acceptor* m_acceptor;
    boost::asio::ip::tcp::socket* m_socket;
    boost::asio::ip::tcp::endpoint m_endpoint;
    iris::synchronization::Mutex m_receiveMutex;
    volatile bool m_isNetworkUp;
    
    iris::threads::Thread* m_newConnectionThread();
    
    bool startupNetwork();
    void shutdownNetwork();
    void expectConnection();
    void shutdownHandlers();
    void cleanupHandlers();
    void checkBoostResult(const boost::system::error_code& ec);
    
protected:
    iris::fileserver::CALLBACK_STATUSMESSAGE m_cbStatusMessage;
    
    void handleReceive(const boost::system::error_code& error);
    void sendStatus(const std::string& str);
    
    void statusMessage(const std::string& message);
};

}// namespace iris

}// namespace fileserver

#endif // HTTPLISTENER_H
