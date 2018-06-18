#ifndef NETWORKCALCULATORIPV4_H
#define NETWORKCALCULATORIPV4_H

#include <qglobal.h>

class QString;

/*
 * Network Calculator
 * 
 * Checking for IPv4 addresses, network names and netmasks
 * 
 * When passing "address with net prefix", pass addresses in this format:
 * 10.20.30.40/15
 * where 10.20.30.40 is the address and 15 is the network prefix
 * 
 * Note: In this implementation, leading zeros in a tuplet are not interpreted as octal numbers
 * 
 * Does not enforce Class A, B or C bitmasks, instead allows 
 * any bitmask from 0 to 32 to allow "Classless Inter-Domain Routing"
 * 
 */
class NetworkCalculatorIpV4
{
public:
    NetworkCalculatorIpV4() {}
    ~NetworkCalculatorIpV4() {}
    
    static bool splitAddressAndNetPrefix(const QString& addressWithNetPrefixLength, QString& outAddress, QString& outNetPrefixLength);
    
    static quint32 getIntegerFromAddress(const QString& addressWithoutNetPrefixLength, bool& outSuccess);
    
    static quint32 getIntegerFromNetPrefixLength(const QString& netPrefixLength, bool& outSuccess);
    
    static bool isValidNetPrefix(const int netPrefix);
    
    static quint32 getHostRangeSize(const QString& minHostAddressWithoutNetPrefix, const QString& maxHostAddressWithoutNetPrefix, bool& outSuccess);
    
    static QString addressToStringFromInteger(const quint32 address);
    
    static quint32 generateHostFromNetPrefixAndIndex(const QString& netPrefixLength, const quint32 index);

private:
    
    static quint32 getIntegerFrom4ByteTuples(const QString& fourByteTuples, bool& success);

};

#endif // NETWORKCALCULATORIPV4_H
