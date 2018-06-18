#ifndef OPTIONSVALIDATOR_H
#define OPTIONSVALIDATOR_H

#include "QtSensorChoiceDialog.h"

namespace iris {

namespace qt {

class OptionsValidator
{
public:
    OptionsValidator();
    ~OptionsValidator();
    
    static bool areDriverOptionsValid(const QtSensorChoiceDialog::driverOptionMapType&);
    
private:
    static bool isValidIpV4Host(const QString&);

    static bool isValidUip(const QString&);

    static bool isValidNetworkList(const QString&);

    static bool isValidHostList(const QString&);

    static bool isValidBoolean(const QString&);

    static bool isValidIpV4NetworkWithSubnet(const QString&);
};

}

}

#endif // OPTIONSVALIDATOR_H
