// ***************************************************************************
// *    _      _       ____                                 _    ____ ___    *
// *   (_)_ __(_)___  / ___|  ___ _ __  ___  ___  _ __     / \  |  _ \_ _|   *
// *   | | '__| / __| \___ \ / _ \ '_ \/ __|/ _ \| '__|   / _ \ | |_) | |    *
// *   | | |  | \__ \  ___) |  __/ | | \__ \ (_) | |     / ___ \|  __/| |    *
// *   |_|_|  |_|___/ |____/ \___|_| |_|___/\___/|_|    /_/   \_\_|  |___|   *
// *                                                                         *
// *   Copyright (c) 2010 by iris-GmbH, Berlin         All rights reserved   *
// *                                                                         *
// ***************************************************************************

// ---------------------------------------------------------------------------
// Please refer to LICENSE.TXT for more information on copyright and licensing
// terms with respect to this library and its source codes.
// ---------------------------------------------------------------------------

#ifndef METROLOGY_GROUPAGGREGATOR_H
#define METROLOGY_GROUPAGGREGATOR_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureSink.h"

namespace iris {

namespace metrology {

class SENSORAPI GroupAggregator: public iris::dist500::PictureSink {

    unsigned int groupCount;

protected:

    GroupAggregator();

}; // class GroupAggregators

} // namespace metrology

} // namespace iris

#endif // METROLOGY_GROUPAGGREGATOR_H
