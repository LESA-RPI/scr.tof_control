#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H
#include <string>

// boost includes
#include <boost/asio.hpp>
#include <boost/asio/error.hpp>

//typedef void (*CALLBACK_READ_TIMEOUT) (void);

// iris includes
#include "iris/synchronization/Mutex.h"
#include "iris/threads/Thread.h"

#include "HttpServerTypes.h"
namespace iris {
    namespace fileserver {
        class ResponseDataCache;
    }
}

namespace iris {

namespace fileserver {

/**
 * @brief The HttpConnectionHandler class represents a thread handling one communication via a socket
 */
class HttpConnectionHandler : public iris::threads::Thread
{
public:
    typedef int SocketDescriptor;

    /**
     * @brief HttpConnectionHandler
     * @param socket
     * @param settings Passed by value because this lives in its own thread
     */
    explicit HttpConnectionHandler(boost::asio::ip::tcp::socket* socket, const iris::fileserver::HttpServerSettings settings, iris::fileserver::CALLBACK_STATUSMESSAGE pfnStatusMessage);
    virtual ~HttpConnectionHandler();
    
    virtual unsigned int execute();
    
    bool isFinished() {return m_isFinished;}
    void setResponseDataCache(iris::fileserver::ResponseDataCache* ptr) {m_responseDataCache = ptr;}
    unsigned int processInbound();
    
private:
    boost::asio::ip::tcp::socket* m_socket;
    iris::fileserver::HttpServerSettings m_settings;
    iris::synchronization::Mutex m_socketMutex;
    bool m_isFinished;
    iris::fileserver::CALLBACK_STATUSMESSAGE m_cbStatusMessage;
    iris::fileserver::ResponseDataCache* m_responseDataCache;
    boost::asio::deadline_timer m_deadlineTimer;
    std::string m_infoString;
    
    void sendStatus(const std::string& str);
    
protected:
    void on_readTimeout(const boost::system::error_code& errorCode);
};

}// namespace iris

}// namespace fileserver

#endif // HTTPCONNECTIONHANDLER_H
