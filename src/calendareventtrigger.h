#pragma once

#include <operationalcalendar.h>

#include "trigger.h"

namespace nap
{
    //////////////////////////////////////////////////////////////////////////
    // ECalendarEventTriggerType
    //////////////////////////////////////////////////////////////////////////

    /**
     * Describes behaviour of the CalendarEventTrigger
     */
    enum ECalendarEventTriggerType : int
    {
        TRIGGER_ON_OPERATIONAL = 0,
        TRIGGER_ON_NON_OPERATIONAL = 1
    };

    //////////////////////////////////////////////////////////////////////////
    // CalendarEventTrigger
    //////////////////////////////////////////////////////////////////////////

    /**
     * The CalendarEventTrigger is triggered from an operation calendar when it becomes operational or non-operational
     */
    class NAPAPI CalendarEventTrigger : public Trigger
    {
    RTTI_ENABLE(Trigger)
    public:
        /**
         * Creates instance of this trigger
         * @param handlerInstance reference to TriggerHandlerComponentInstance creating this TriggerInstance
         * @return unique pointer of TriggerInstance
         */
        std::unique_ptr<TriggerInstance> createInstance(nap::TriggerHandlerComponentInstance &handlerInstance) override;

        ResourcePtr<OperationalCalendar> mCalendar; ///< Property: "Calendar" Resource pointer to operational calendar
        ECalendarEventTriggerType mTriggerType = ECalendarEventTriggerType::TRIGGER_ON_OPERATIONAL; ///< Property: "TriggerType" when this trigger is triggered
    private:
        bool mIsOperational = false;
    };

    //////////////////////////////////////////////////////////////////////////
    // CalendarEventTriggerInstance
    //////////////////////////////////////////////////////////////////////////

    /**
     * The instance of CalendarEventTrigger
     */
    class NAPAPI CalendarEventTriggerInstance : public TriggerInstance
    {
    RTTI_ENABLE(TriggerInstance)
    public:
        /**
         * Constructor
         * @param handlerInstance reference to TriggerHandlerComponentInstance creating this TriggerInstance
         * @param resource reference to resource of Trigger
         */
        CalendarEventTriggerInstance(TriggerHandlerComponentInstance& handlerInstance, Trigger& resource);

        /**
         * Called from TriggerHandlerComponentInstance and checks whether the calendar just became operational or non-operational
         * @param deltaTime time since last frame
         */
        void update(double deltaTime) override;
    protected:
        /**
         * Initializes TriggerInstance, called from the TriggerHandlerComponentInstance::init method
         * @param errorState contains any errors
         * @return true on success
         */
        bool onInit(utility::ErrorState &errorState) override;
    private:
        bool mIsOperational;
        OperationalCalendar* mCalendar;
        ECalendarEventTriggerType mTriggerType = ECalendarEventTriggerType::TRIGGER_ON_OPERATIONAL;
    };
}
