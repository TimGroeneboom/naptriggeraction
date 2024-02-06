#pragma once

#include <component.h>
#include <concurrentqueue.h>

#include "trigger.h"
#include "triggeraction.h"

namespace nap
{
    // forward declares
    class TriggerHandlerComponentInstance;

    //////////////////////////////////////////////////////////////////////////
    // TriggerHandlerComponent
    //////////////////////////////////////////////////////////////////////////

    /**
     * The TriggerHandlerComponent creates instances of trigger resources and calls their virtual init, update and destroy
     * methods.
     * Whenever a Trigger is triggered its APIEvent is moved to a ConcurrentQueue and passed on to the execute method of
     * set TriggerActions. This will always happen on update and thus happen from the application main thread.
     * Triggers are allowed to call their 'trigger' method from any thread. The TriggerHandlerComponentInstance makes sure
     * they Actions will be executed from the app update loop.
     */
    class NAPAPI TriggerHandlerComponent : public Component
    {
    RTTI_ENABLE(Component)
    DECLARE_COMPONENT(TriggerHandlerComponent, TriggerHandlerComponentInstance)
    public:
        std::vector<ResourcePtr<Trigger>> mTriggers; ///< Property: "Triggers" resource ptrs to Triggers
        std::vector<ResourcePtr<TriggerAction>> mActions; ///< Property: "Actions" resource ptrs to actions
        bool mVerbose = false; ///< Property: "Verbose" whether or not to log trigger events
    };

    //////////////////////////////////////////////////////////////////////////
    // TriggerHandlerComponentInstance
    //////////////////////////////////////////////////////////////////////////

    /**
     * The instance of TriggerHandlerComponent
     */
    class NAPAPI TriggerHandlerComponentInstance : public ComponentInstance
    {
        friend class TriggerInstance;

    RTTI_ENABLE(ComponentInstance)
    public:
        /**
         * Constructor
         */
        TriggerHandlerComponentInstance(EntityInstance& entity, Component& resource) :
            ComponentInstance(entity, resource){ }

        /**
         * Initializes TriggerHandlerComponentInstance by creating an instance of the Trigger resource and setting up
         * @param errorState contains any errors
         * @return true on success
         */
        bool init(utility::ErrorState& errorState) override;

        /**
         * Updates created TriggerInstance
         * @param deltaTime time since last frame
         */
        void update(double deltaTime) override;

        /**
         * Calls onDestroy on create TriggerInstance
         */
        void onDestroy() override;
    private:
        /**
         * Called from TriggerInstance when triggered, thread-safe call
         * @param triggerInstance reference to TriggerInstance
         * @param event the created APIEvent by the TriggerInstance
         */
        void trigger(TriggerInstance& triggerInstance, APIEventPtr event);

        std::vector<std::unique_ptr<TriggerInstance>> mTriggerInstances;
        std::vector<TriggerAction*> mActions;
        bool mVerbose = false;
        moodycamel::ConcurrentQueue<APIEventPtr> mEvents;
    };
}