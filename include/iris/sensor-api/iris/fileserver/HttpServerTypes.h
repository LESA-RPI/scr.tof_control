#ifndef HTTPSERVERTYPES_H
#define HTTPSERVERTYPES_H

// standard includes
#include <stdint.h>
//#include <cstdint> // preferred, but requires C++11

// STL includes
#include <string>
#include <vector>
#include <map>

namespace iris {

namespace fileserver {

typedef std::map<std::string, std::string> headerMapType;

typedef void (*CALLBACK_STATUSMESSAGE) (const std::string& str);

struct HttpServerSettings {
    std::string hostedFile;
    std::string listenNicAddressPreferred;
    std::string pathPrefix;
    uint32_t listenPort;
    uint32_t socketReadSizeMax;
    bool autoStart;
    uint32_t timeoutReadMs;
};

/**
 * @brief The HttpResponseDataInfo struct contains both metadata and the data to be responded with.
 */
struct HttpResponseDataInfo {
    std::vector<char> data;
    struct Metadata {
        std::string timestampModified;
        std::string contentType;
        std::string contentName;
        size_t contentSize;
        bool binary;
    } meta;
};

}// namespace iris

}// namespace fileserver

#endif // HTTPSERVERTYPES_H

