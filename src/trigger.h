#pragma once

#include <nap/resource.h>
#include <nap/resourceptr.h>
#include <nap/group.h>
#include <apisignature.h>
#include <apiservice.h>
#include <nap/signalslot.h>

#include "triggerargument.h"

namespace nap
{
    // forward declares
    class TriggerInstance;
    class TriggerHandlerComponentInstance;

    //////////////////////////////////////////////////////////////////////////
    // Trigger
    //////////////////////////////////////////////////////////////////////////

    /**
     * Trigger is the base class of a trigger that can be used to trigger an action using a TriggerHandlerComponent. createInstance must be implemented in
     * derived classes.
     * createInstance will be called from the TriggerHandlerComponentInstance::init method. The TriggerInstance must implement
     * the logic needed for the trigger to call trigger on the TriggerHandlerComponentInstance.
     */
    class NAPAPI Trigger : public Resource
    {
        friend class TriggerHandlerComponentInstance;
        RTTI_ENABLE(Resource)
    public:
        std::vector<ResourcePtr<TriggerBaseArgument>> mArguments; ///< Property: "Arguments" Embedded arguments of this trigger
    protected:
        /**
         * Creates an instance of the Trigger
         * @param handlerInstance TriggerHandlerComponentInstance reference
         * @return unique_ptr to TriggerInstance
         */
        virtual std::unique_ptr<TriggerInstance> createInstance(TriggerHandlerComponentInstance& handlerInstance) = 0;
    };

    //////////////////////////////////////////////////////////////////////////
    // TriggerInstance
    //////////////////////////////////////////////////////////////////////////

    /**
     * TriggerInstance is the base class of an instance of a trigger that can be used to trigger an action using a TriggerHandlerComponentInstance.
     */
    class NAPAPI TriggerInstance
    {
    RTTI_ENABLE()
    public:
        /**
         * Constructor
         * @param handlerInstance reference to TriggerHandlerComponentInstance creating this TriggerInstance
         * @param resource reference to resource of Trigger
         */
        TriggerInstance(TriggerHandlerComponentInstance& handlerInstance, Trigger& resource);

        /**
         * Destructor
         */
        virtual ~TriggerInstance() = default;

        /**
         * Initializes TriggerInstance, called from the TriggerHandlerComponentInstance::init method
         * @param errorState contains any errors
         * @return true on success
         */
        bool init(utility::ErrorState& errorState);

        /**
         * Called from TriggerHandlerComponentInstance::update method, can contain logic needed to continuously check for trigger
         * @param deltaTime
         */
        virtual void update(double deltaTime){};

        /**
         * Called from TriggerHandlerComponentInstance::onDestroy method upon deconstruction of the TriggerInstance
         */
        virtual void onDestroy(){};

        /**
         * Returns ID of the TriggerInstance, is unique to this instance
         * @return ID of the TriggerInstance
         */
        const std::string& getID() const{ return mID; }
    protected:
        /**
         * Must be implemented in derived classes, called from TriggerHandlerComponentInstance::trigger method
         * @param errorState contains any errors
         * @return true on success
         */
        virtual bool onInit(utility::ErrorState& errorState) = 0;

        /**
         * Creates API event, you can override this method to create your own custom API events
         * @return APIEventPtr
         */
        virtual APIEventPtr createAPIEvent();

        /**
         * Creates APIEvent from TriggerValues, calls trigger on TriggerHandlerComponent. Thread-safe
         */
        void trigger();

        TriggerHandlerComponentInstance& mHandler;
        Trigger& mResource;
        std::vector<TriggerBaseArgument*> mArguments;
        std::string mID;
    };
}
