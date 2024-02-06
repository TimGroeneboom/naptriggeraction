#include "trigger.h"
#include "nap/logger.h"
#include "triggerhandlercomponent.h"
#include "entity.h"

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::Trigger)
    RTTI_PROPERTY("Arguments", &nap::Trigger::mArguments, nap::rtti::EPropertyMetaData::Embedded)
RTTI_END_CLASS

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::TriggerInstance)
RTTI_END_CLASS

namespace nap
{
    TriggerInstance::TriggerInstance(nap::TriggerHandlerComponentInstance &handlerInstance, nap::Trigger &resource)
        : mHandler(handlerInstance), mResource(resource)
    {
    }


    bool TriggerInstance::init(utility::ErrorState& errorState)
    {
        mID = mHandler.mID + "_" + mResource.mID;

        for(auto& arg : mResource.mArguments)
            mArguments.emplace_back(arg.get());

        if(onInit(errorState))
            return true;

        return false;
    }


    void TriggerInstance::trigger()
    {
        mHandler.trigger(*this, createAPIEvent());
    }


    APIEventPtr TriggerInstance::createAPIEvent()
    {
        auto api_event = std::make_unique<APIEvent>(mID);
        for(auto* arg : mArguments)
        {
            api_event->addArgument(arg->createAPIValue());
        }
        return api_event;
    }
}