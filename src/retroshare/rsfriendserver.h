#include <functional>
#include <thread>
#include "util/rstime.h"

// The Friend Server component of Retroshare automatically adds/removes some friends so that the
//
// The current strategy is:
//
//   - if total nb of friends < S
//         request new friends to the FS
//   - if total nb of friends >= S
//         do not request anymore (and unpublish the key), but keep the friends already here
//
// Possible states:
//   - not started
//   - maintain friend list
//   - actively request friends
//
// The friend server internally keeps track of which friends have been added using the friend server.
// It's important to keep the ones that are already connected because they may count on us.
// Friends supplied by the FS who never connected for a few days should be removed automatically.

class RsFriendServer
{
public:
    virtual void startServer() =0;
    virtual void stopServer() =0;

    // Testing system. Since the test can take some time (contacting the proxy, setting the connection,
    // getting some ack from the server). The whole test is synchronous and might be blocking for a while.
    // Consequently, the client needs to take care to avoid blocking e.g. the UI when calling this.
    //
    virtual bool checkServerAddress(const std::string& addr,uint16_t port, uint32_t timeout_ms) =0;

    virtual void setServerAddress(const std::string&,uint16_t) =0;
    virtual void setFriendsToRequest(uint32_t) =0;

    /*!
     * \brief setProfilePassphrase
     * 		Needs to be called as least once, and before the friend server is enabled, so as to be able to decrypt incoming information
     * 		sent by the server. If not available, the passphrase will be asked by the GUI, which may cause some annoying
     *      side effects.
     */
    virtual void setProfilePassphrase(const std::string& passphrase) =0;

    virtual uint32_t friendsToRequest() =0;
    virtual uint16_t friendsServerPort() =0;
    virtual std::string friendsServerAddress() =0;
};

extern RsFriendServer *rsFriendServer;
