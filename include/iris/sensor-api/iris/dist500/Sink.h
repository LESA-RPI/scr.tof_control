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

#ifndef DIST500_SINK_H
#define DIST500_SINK_H

// iris includes
#include "iris/Common.h"
#include "iris/synchronization/Mutex.h"
#include "iris/synchronization/Lock.h"

namespace iris {

namespace dist500 {

// forward declaration to avoid #include cycles
template <class T> class Source;

/**
 * Template class defining a data "sink"
 *
 * @note Subclasses need to implement the processNewData() method.
 **/
template <class T> class Sink {

public:

    /**
     * Typedef for matching Source instances
     */
    typedef Source<T> SourceType;

    /**
     * Constructor
     *
     */
    Sink<T>()
        : source(0) {
        
    }

    /**
     * Destructor
     */
    virtual ~Sink() {
        // tell source that we are gone
        detach();
    }

    /**
     * Detaches from the associated Source (if currently attached to any)
     */
    void detach(void) {
        iris::synchronization::Lock lock(mutex);
        // unlink and inform source if necessary
        if (source) {
            source->detachSink(this, false);
            source = 0;
        }
    }

    /**
     * Attaches to the given Source
     *
     * @param source Source instance to attach to
     */
    void attachSource(SourceType* source) {
        iris::synchronization::Lock lock(mutex);
        // ignore call if association already exists
        if (source != this->source) {
            // detach from previous source
            detach();
            // change link
            this->source = source;
            // register with new source
            if (source) {
                source->attachSink(this, false);
            }
        }
    }

protected:

    iris::synchronization::Mutex mutex;

    /**
     * Active (ie attached) Source instance (or <code>null</code> if
     * sink is currently not attached)
     */
    SourceType* source;

    /**
     * Signals the availability of new data from the source
     *
     * @param data Data object
     * @param index 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param indexCount Total number of data objects (0 if unknown)
     *
     * @note Subclasses need to implement this method.
     */
    virtual void processNewData(T data,
            unsigned long index, unsigned long indexCount) = 0;

    friend class Source<T>;

}; // template class Sink

} // namespace dist500

} // namespace iris

#endif // DIST500_SINK_H
