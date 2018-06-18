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

#ifndef DIST500_SOURCE_H_
#define DIST500_SOURCE_H_

// STL includes
#include <list>

// iris includes
#include "iris/Common.h"
#include "iris/dist500/Sink.h"

namespace iris {

namespace dist500 {

// forward declaration to avoid #include cycles
template <class T> class Sink;

/**
 * Template class defining a data source
 */
template <class T> class Source {

public:

    /**
     * Typedef for matching Sink instances
     */
    typedef Sink<T> SinkType;

    /**
     * Destructor
     */
    virtual ~Source() {
        detachAll();
    }

    // TODO synchronize access !

    /**
     * Attaches the given sink to the current source
     *
     * @param sink Sink to attach
     */
    void attachSink(SinkType* sink) {
        attachSink(sink, true);
    }

    /**
     * Detaches the given sink from the current source
     *
     * @param sink Sink to detach
     */
    void detachSink(SinkType* sink) {
        detachSink(sink, true);
    }

    /**
     * Checks whether the current source has any sinks attached
     *
     * @return <code>true</code> if there is at least one source attached,
     *         <code>false</code> otherwise
     */
    bool hasAnySinks(void) {
        return !pictureSinks.empty();
    }

    /**
     * Detaches the source from connected sinks
     */
    void detachAll(void) {
        iris::synchronization::Lock lock(mutex);
        // detach all connected sinks
        while (!pictureSinks.empty()) {
            typename SinkTypeList::iterator i = pictureSinks.begin();
            SinkType* sink = *i;
            sink->detach();
        }
        // clear sink list
        pictureSinks.clear();
    }

protected:

    iris::synchronization::Mutex mutex;

    /**
     * Defines a set of (typed) sinks
     */
    typedef std::list<SinkType*> SinkTypeList;

    /**
     * Holds the list of currently attaches sources
     */
    SinkTypeList pictureSinks;

    /**
     * Propagates new data to all attached sinks
     *
     * @param data Data to be propagated
     * @param index 0-based index of the data if the total number of
     *        data objects is known, 0 otherwise
     * @param indexCount Total number of data objects (0 if unknown)
     */
    void pushDataToSinks(T data, unsigned long index, unsigned long indexCount) {
        iris::synchronization::Lock lock(mutex);
        // pass on data to all sinks' processNewPicture() method
        for (typename SinkTypeList::const_iterator i = pictureSinks.begin(); i
                != pictureSinks.end(); ++i) {
            SinkType* sink = *i;
            sink->processNewData(data, index, indexCount);
        }
    }

    void detachSink(SinkType* sink, bool detachCall) {
        iris::synchronization::Lock lock(mutex);
        typename SinkTypeList::iterator it = std::find(pictureSinks.begin(), pictureSinks.end(), sink);
        if (sink && it != pictureSinks.end()) {
            pictureSinks.erase(it);
            if (detachCall) {
                sink->detach();
            }
        }
    }

    void attachSink(SinkType* sink, bool attachCall) {
        iris::synchronization::Lock lock(mutex);
        typename SinkTypeList::iterator it = std::find(pictureSinks.begin(), pictureSinks.end(), sink);
        if (sink && it == pictureSinks.end()) {
            pictureSinks.push_back(sink);
            if (attachCall) {
                sink->attachSource(this);
            }
        }
    }


    friend class Sink<T>;

}; // template class Source

} // namespace dist500

} // namespace iris

#endif // DIST500_SOURCE_H
