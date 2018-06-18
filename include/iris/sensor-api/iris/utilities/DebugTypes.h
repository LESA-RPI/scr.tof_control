// ***************************************************************************
// *    _      _       ____                                 _    ____ ___    *
// *   (_)_ __(_)___  / ___|  ___ _ __  ___  ___  _ __     / \  |  _ \_ _|   *
// *   | | '__| / __| \___ \ / _ \ '_ \/ __|/ _ \| '__|   / _ \ | |_) | |    *
// *   | | |  | \__ \  ___) |  __/ | | \__ \ (_) | |     / ___ \|  __/| |    *
// *   |_|_|  |_|___/ |____/ \___|_| |_|___/\___/|_|    /_/   \_\_|  |___|   *
// *                                                                         *
// *   Copyright (c) 2012 by iris-GmbH, Berlin         All rights reserved   *
// *                                                                         *
// ***************************************************************************

// ---------------------------------------------------------------------------
// Please refer to LICENSE.TXT for more information on copyright and licensing
// terms with respect to this library and its source codes.
// ---------------------------------------------------------------------------

#ifndef UTILITIES_DEBUGTYPES_H
#define UTILITIES_DEBUGTYPES_H

// iris includes
#include "IrisList.h"
#ifdef APIBUILD
    #include "UipTypes.h"
#else
    #include "iris/UipTypes.h"
#endif

namespace iris {

namespace utilities {

typedef IrisList<iris::uip::functionAreaStatus> DebugFunctionAreaStatusList;
typedef IrisList<iris::uip::category_counts> DebugCountList;
typedef IrisList<iris::uip::category> DebugCategoryList;
typedef IrisList<iris::uip::sensor_status> DebugSensorStatusSet;
typedef IrisList<iris::uip::category_type> DebugCategoryTypeSet;

} // namespace utilities

} // namespace iris

#endif // UTILITIES_DEBUGTYPES_H
