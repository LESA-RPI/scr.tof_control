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

#ifndef UFF_UFFPLAYER_H_
#define UFF_UFFPLAYER_H_

// boost includes
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

// iris includes
#include "iris/Common.h"
#include "UffDecoder.h"

namespace iris {

namespace uff {

/**
 * Implements a player class for DIST500 uff movies
 */
class SENSORAPI UffPlayer: public iris::uff::UffDecoder {

protected:

    /**
     *
     */
    class UffPlayerThread {

    protected:

        /**
         *
         */
        UffPlayer* player;

    public:

        /**
         *
         */
        UffPlayerThread(UffPlayer* player);

        /**
         *
         */
        void operator()();

    };

    /**
     *
     */
    /*static*/ boost::asio::io_service io;

    /**
     *
     */
    boost::asio::deadline_timer timer;

    /**
     *
     */
    boost::thread *thread;

    unsigned long playbackIndex;

    /**
     *
     */
    bool paused;

    /**
     *
     */
    void timerEvent(void);

    /**
     *
     */
    double speed;

    /**
     *
     */
    bool stopRequested;

    bool playingForward;

public:

    /**
     *
     */
    UffPlayer();

    /**
     *
     */
    virtual ~UffPlayer();

    /**
     *
     */
    void startPlayback(unsigned long maxPictures = 0,
            unsigned long long maxTime = 0);

    /**
     *
     */
    void stopPlayback(void);

    /**
     *
     */
    void setSpeed(double newSpeed);

    /**
     *
     */
    double getSpeed(void);

    /**
     *
     */
    void waitForEndOfPlayback(void);

    /**
     *
     */
    void setPaused(bool paused);

    /**
     *
     */
    void pause(void);

    /**
     *
     */
    void unpause(void);

    /**
     *
     */
    bool isPaused(void);

    /**
     *
     */
    void setPlaybackDirection(bool forward);

    /**
     *
     */
    void forward(void);

    /**
     *
     */
    void backward(void);

    /**
     *
     */
    void rewind(void);

    bool isPlayingForward(void);

}; // class UffPlayer

} // namespace uff

} // namespace iris

#endif // UFF_UFFPLAYER_H
