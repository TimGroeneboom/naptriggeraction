#include "udptrigger.h"
#include "triggerhandlercomponent.h"

RTTI_BEGIN_CLASS(nap::UDPTrigger)
    RTTI_PROPERTY("Server",     &nap::UDPTrigger::mServer,  nap::rtti::EPropertyMetaData::Required)
    RTTI_PROPERTY("Message",    &nap::UDPTrigger::mMessage, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::UDPTriggerInstance)
    RTTI_CONSTRUCTOR(nap::TriggerHandlerComponentInstance&, nap::Trigger&)
RTTI_END_CLASS

namespace nap
{
    std::unique_ptr<TriggerInstance> UDPTrigger::createInstance(nap::TriggerHandlerComponentInstance &handlerInstance)
    {
        return std::make_unique<UDPTriggerInstance>(handlerInstance, *this);
    }


    UDPTriggerInstance::UDPTriggerInstance(nap::TriggerHandlerComponentInstance &handlerInstance, Trigger& trigger)
        : TriggerInstance(handlerInstance, trigger), mServer(nullptr)
    {
    }


    bool UDPTriggerInstance::onInit(utility::ErrorState &errorState)
    {
        auto& udp_trigger = static_cast<UDPTrigger&>(mResource);
        mServer = udp_trigger.mServer.get();
        mMessage = udp_trigger.mMessage;

        mServer->registerListenerSlot(mPacketReceivedSlot);
        return true;
    }


    void UDPTriggerInstance::onUDPPacketReceived(const nap::UDPPacket &packet)
    {
        if(packet.toString()==mMessage)
        {
            trigger();
        }
    }


    void UDPTriggerInstance::onDestroy()
    {
        mServer->removeListenerSlot(mPacketReceivedSlot);
    }
}