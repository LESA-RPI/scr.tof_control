#ifndef RESPONSECACHE_H
#define RESPONSECACHE_H

#include <string>
#include <map>
#include <vector>

#include "HttpServerTypes.h"

namespace iris {

namespace fileserver {

/**
 * @brief The ResponseDataCache class stores response data that is associated to a path, which is just a string.
 *        It can be used in an HTTP server or any other file server.
 *        Byte ranges of binary files can be returned also. This is useful when large files can not be handled
 *        due to hardware (embedded system) or protocol restrictions (CAN).
 *        In the case of HTTP1.1, these range requests are part of the specifications.
 * 
 * @see HttpServer
 */
class ResponseDataCache
{
public:
    ResponseDataCache();
    ~ResponseDataCache();
    
    void prepareResponseString(const std::string& path, const std::string& content);
    void prepareResponseBinaryFile(const std::string& path, const std::string& filename);
    bool hasResponseFor(const std::string& path) const;
    void getResponseDataFor(const std::string& path, std::vector<char>& dest);
    void getResponseDataRangeFor(const std::string& path, size_t offset, size_t size, std::vector<char>& dest);
    void getResponseMetaFor(const std::string& path, iris::fileserver::HttpResponseDataInfo::Metadata& dest);
    void removeResponseFor(const std::string& path);
    void listAvailablePaths(std::vector<std::string>& dest);
private:
    std::map<std::string, iris::fileserver::HttpResponseDataInfo> m_responseContainer;
};

}// namespace iris

}// namespace fileserver

#endif // RESPONSECACHE_H
