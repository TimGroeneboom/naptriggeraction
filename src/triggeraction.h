#pragma once

#include <nap/resource.h>
#include <nap/resourceptr.h>
#include <apivalue.h>
#include <parameternumeric.h>
#include <parametersimple.h>
#include <parametervec.h>

#include "trigger.h"
#include "triggeractionutils.h"

namespace nap
{
    //////////////////////////////////////////////////////////////////////////
    // TriggerAction
    //////////////////////////////////////////////////////////////////////////

    /**
     * TriggerAction is the base class of an action that can be triggered by a trigger. Extend execute to implement your
     * own Action
     */
    class NAPAPI TriggerAction : public Resource
    {
        friend class TriggerHandlerComponentInstance;
    RTTI_ENABLE(Resource)
    public:
        /**
         * Constructor, creates the mExecuteSlot
         */
        TriggerAction();

        /**
         * Initializes the trigger, registers it to triggers
         * @param errorState contains any errors
         * @return true on success
         */
        bool init(utility::ErrorState& errorState) final;

        /**
         * Removes itself from the triggers, calls virtual 'destroy'
         */
        void onDestroy() final;
    protected:
        /**
         * Override this method to provide your own initialization method
         * @param errorState contains any errors
         * @return true on success
         */
        virtual bool onInit(utility::ErrorState& errorState){ return true; }

        /**
         * Override this method to provide your own deconstruction method
         */
        virtual void destroy(){}

        /**
         * Extend this method to implement your own action logic
         * @param event event ptr containing arguments
         * @param errorState can contain errors during execution of action
         * @return true on success
         */
        virtual bool onExecute(const APIEventPtr& event, utility::ErrorState& errorState) = 0;
    private:
        /**
         * Called by TriggerHandlerComponentInstance on main thread
         * @param event event containing arguments
         */
        void execute(const APIEventPtr& event);
    };

    //////////////////////////////////////////////////////////////////////////
    // TriggerActionGroup
    //////////////////////////////////////////////////////////////////////////

    namespace group
    {
        namespace triggeraction
        {
            constexpr const char* members  = "TriggerActions";		///< Parameter Group members property name
            constexpr const char* children = "Groups";			    ///< Parameter Group children property name
        }
    }

    using TriggerActionGroup = Group<TriggerAction>;
}
