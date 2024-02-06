#pragma once

#include <udpserver.h>
#include <concurrentqueue.h>
#include <nap/signalslot.h>

#include "trigger.h"

namespace nap
{
    //////////////////////////////////////////////////////////////////////////
    // UDPTrigger
    //////////////////////////////////////////////////////////////////////////

    /**
     * Triggers actions when UDP packet matches the contents of given mMessage string
     */
    class NAPAPI UDPTrigger : public Trigger
    {
    RTTI_ENABLE(Trigger)
    public:
        ResourcePtr<UDPServer> mServer;       ///< Property: "Server" resource point to UDPServer
        std::string mMessage = "trigger";     ///< Property: "Message" message to match

        std::unique_ptr<TriggerInstance> createInstance(nap::TriggerHandlerComponentInstance &handlerInstance) override;
    };

    //////////////////////////////////////////////////////////////////////////
    // UDPTriggerInstance
    //////////////////////////////////////////////////////////////////////////

    /**
     * Instance of UDPTrigger
     */
    class NAPAPI UDPTriggerInstance : public TriggerInstance
    {
    RTTI_ENABLE(TriggerInstance)
    public:
        /**
         * Constructor
         * @param handlerInstance TriggerHandlerComponentInstance reference
         * @param trigger reference to trigger resource reference
         */
        UDPTriggerInstance(TriggerHandlerComponentInstance& handlerInstance, Trigger& trigger);

        /**
         * Disconnects from UDP server
         */
        void onDestroy() override;
    protected:
        /**
         * Connects to UDP server
         * @param errorState contains any errors
         * @return true on success
         */
        bool onInit(utility::ErrorState &errorState) override;
    private:
        UDPServer* mServer;
        std::string mMessage = "trigger";

        /**
         * Called from thread running the UDP server
         * @param packet packet received
         */
        void onUDPPacketReceived(const UDPPacket& packet);
        Slot<const UDPPacket&> mPacketReceivedSlot = { this, &UDPTriggerInstance::onUDPPacketReceived };
    };
}