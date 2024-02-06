#include "calendareventtrigger.h"
#include "triggerhandlercomponent.h"

RTTI_BEGIN_ENUM(nap::ECalendarEventTriggerType)
    RTTI_ENUM_VALUE(nap::ECalendarEventTriggerType::TRIGGER_ON_OPERATIONAL,     "Trigger On Operational"),
    RTTI_ENUM_VALUE(nap::ECalendarEventTriggerType::TRIGGER_ON_NON_OPERATIONAL, "Trigger On Non-Operational")
RTTI_END_ENUM

RTTI_BEGIN_CLASS(nap::CalendarEventTrigger)
    RTTI_PROPERTY("Calendar",       &nap::CalendarEventTrigger::mCalendar,      nap::rtti::EPropertyMetaData::Required)
    RTTI_PROPERTY("TriggerType",    &nap::CalendarEventTrigger::mTriggerType,   nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::CalendarEventTriggerInstance)
    RTTI_CONSTRUCTOR(nap::TriggerHandlerComponentInstance&, nap::Trigger&)
RTTI_END_CLASS

namespace nap
{
    std::unique_ptr<TriggerInstance> CalendarEventTrigger::createInstance(nap::TriggerHandlerComponentInstance &handlerInstance)
    {
        return std::make_unique<CalendarEventTriggerInstance>(handlerInstance, *this);
    }


    CalendarEventTriggerInstance::CalendarEventTriggerInstance(TriggerHandlerComponentInstance& handlerInstance, Trigger& resource)
        : TriggerInstance(handlerInstance, resource)
    {}


    bool CalendarEventTriggerInstance::onInit(utility::ErrorState& errorState)
    {
        auto& resource = static_cast<CalendarEventTrigger&>(mResource);
        mCalendar = resource.mCalendar.get();
        mTriggerType = resource.mTriggerType;
        mIsOperational = mTriggerType != ECalendarEventTriggerType::TRIGGER_ON_OPERATIONAL;
        return true;
    }


    void CalendarEventTriggerInstance::update(double deltaTime)
    {
        if(mCalendar->isOperational() && !mIsOperational)
        {
            mIsOperational = true;

            if(mTriggerType==TRIGGER_ON_OPERATIONAL)
                trigger();
        }else if(!mCalendar->isOperational() && mIsOperational)
        {
            mIsOperational = false;

            if(mTriggerType==TRIGGER_ON_NON_OPERATIONAL)
                trigger();
        }
    }
}