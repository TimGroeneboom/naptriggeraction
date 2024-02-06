#include "triggerhandlercomponent.h"
#include "nap/logger.h"

#include <entity.h>


RTTI_BEGIN_CLASS(nap::TriggerHandlerComponent)
    RTTI_PROPERTY("Triggers",   &nap::TriggerHandlerComponent::mTriggers,   nap::rtti::EPropertyMetaData::Default | nap::rtti::EPropertyMetaData::Embedded)
    RTTI_PROPERTY("Actions",    &nap::TriggerHandlerComponent::mActions,    nap::rtti::EPropertyMetaData::Default)
    RTTI_PROPERTY("Verbose",    &nap::TriggerHandlerComponent::mVerbose,    nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::TriggerHandlerComponentInstance)
    RTTI_CONSTRUCTOR(nap::EntityInstance&, nap::Component&)
RTTI_END_CLASS

namespace nap
{
    bool TriggerHandlerComponentInstance::init(utility::ErrorState &errorState)
    {
        auto& resource = *getComponent<TriggerHandlerComponent>();
        mVerbose = resource.mVerbose;

        for(auto& trigger : resource.mTriggers)
        {
            auto trigger_instance = trigger->createInstance(*this);
            if(!trigger_instance->init(errorState))
                return false;

            mTriggerInstances.emplace_back(std::move(trigger_instance));
        }

        for(auto& action : resource.mActions)
            mActions.emplace_back(action.get());

        return true;
    }

    void TriggerHandlerComponentInstance::update(double deltaTime)
    {
        for(auto& trigger : mTriggerInstances)
            trigger->update(deltaTime);

        APIEventPtr event;
        while(mEvents.try_dequeue(event))
        {
            for(auto* action : mActions)
            {
                if(mVerbose)
                    nap::Logger::info(*this, "Executing action %s", action->get_type().get_name().begin());

                action->execute(event);
            }
        }
    }


    void TriggerHandlerComponentInstance::onDestroy()
    {
        for(auto& trigger : mTriggerInstances)
            trigger->onDestroy();
    }


    void TriggerHandlerComponentInstance::trigger(TriggerInstance& trigger, APIEventPtr event)
    {
        if(mVerbose)
            nap::Logger::info(*this, "%s triggered at %s", trigger.getID().c_str(), DateTime().toString().c_str());

        mEvents.enqueue(std::move(event));
    }
}