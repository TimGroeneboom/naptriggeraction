#pragma once

#include <udpserver.h>
#include <sequenceplayereventoutput.h>

#include "trigger.h"

namespace nap
{
    //////////////////////////////////////////////////////////////////////////
    // SequenceEventTrigger
    //////////////////////////////////////////////////////////////////////////

    /**
     * SequenceEventTrigger is triggered from a sequencer output when it hits a given event
     * T is type of event to listen to
     */
    template<typename T>
    class NAPAPI SequenceEventTrigger : public Trigger
    {
    RTTI_ENABLE(Trigger)
    public:
        /**
         * Creates instance of this trigger
         * @param triggerHandler the trigger handler creating the instance
         * @return unique pointer of TriggerInstance
         */
        std::unique_ptr<TriggerInstance> createInstance(TriggerHandlerComponentInstance& triggerHandler) final;

        ResourcePtr<SequencePlayerEventOutput> mOutput; ///< Property: "Output" the sequence player output to register to
        T mValue; ///< Property: "TriggerValue" the value that activates the trigger
    };

    //////////////////////////////////////////////////////////////////////////
    // SequenceEventTriggerInstance<T>
    //////////////////////////////////////////////////////////////////////////

    /**
     * SequenceEventTriggerInstance is the instance of SequenceEventTrigger
     * @tparam T value type of the SequenceEvent to listen to
     */
    template<typename T>
    class NAPAPI SequenceEventTriggerInstance : public TriggerInstance
    {
    RTTI_ENABLE(TriggerInstance)
    public:
        SequenceEventTriggerInstance(TriggerHandlerComponentInstance& triggerHandler, Trigger& trigger);
    protected:
        /**
         * Registers to SequencePlayerEventOutput
         * @param errorState contains any errors
         * @return true on success
         */
        bool onInit(utility::ErrorState& errorState) override;

        /**
         * Removes from SequencePlayerEventOutput
         */
        void onDestroy() override;
    private:
        void onEvent(const SequenceEventBase& event);
        Slot<const SequenceEventBase&> mEventSlot = { this, &SequenceEventTriggerInstance::onEvent };

        SequencePlayerEventOutput* mOutput;
        T mValue;
    };

    //////////////////////////////////////////////////////////////////////////
    // SequenceEventTriggerInstance<T> template definitions
    //////////////////////////////////////////////////////////////////////////

    template<typename T>
    std::unique_ptr<TriggerInstance> SequenceEventTrigger<T>::createInstance(TriggerHandlerComponentInstance& triggerHandler)
    {
        return std::make_unique<SequenceEventTriggerInstance<T>>(triggerHandler, *this);
    }


    template<typename T>
    SequenceEventTriggerInstance<T>::SequenceEventTriggerInstance(TriggerHandlerComponentInstance& triggerHandler, Trigger& trigger)
        : TriggerInstance(triggerHandler, trigger), mOutput(nullptr){}


    template<typename T>
    bool SequenceEventTriggerInstance<T>::onInit(utility::ErrorState &errorState)
    {
        auto& trigger = static_cast<SequenceEventTrigger<T>&>(mResource);
        mOutput = trigger.mOutput.get();
        mValue = trigger.mValue;
        mOutput->mSignal.connect(mEventSlot);

        return true;
    }


    template<typename T>
    void SequenceEventTriggerInstance<T>::onDestroy()
    {
        mOutput->mSignal.disconnect(mEventSlot);
    }


    template<typename T>
    void SequenceEventTriggerInstance<T>::onEvent(const SequenceEventBase& event)
    {
        if(event.isEventType<SequenceEvent<T>>())
        {
            const auto& event_cast = event.getEventType<SequenceEvent<T>>();
            if(event_cast.getValue()==mValue)
            {
                trigger();
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // SequenceEventTrigger templated type definitions
    //////////////////////////////////////////////////////////////////////////

    using SequenceEventTriggerString    = SequenceEventTrigger<std::string>;
    using SequenceEventTriggerFloat     = SequenceEventTrigger<float>;
    using SequenceEventTriggerInt       = SequenceEventTrigger<int>;
    using SequenceEventTriggerVec2      = SequenceEventTrigger<glm::vec2>;
    using SequenceEventTriggerVec3      = SequenceEventTrigger<glm::vec3>;
    using SequenceEventTriggerVec4      = SequenceEventTrigger<glm::vec4>;

    //////////////////////////////////////////////////////////////////////////
    // SequenceEventTriggerInstance templated type definitions
    //////////////////////////////////////////////////////////////////////////

    using SequenceEventTriggerStringInstance    = SequenceEventTriggerInstance<std::string>;
    using SequenceEventTriggerFloatInstance     = SequenceEventTriggerInstance<float>;
    using SequenceEventTriggerIntInstance       = SequenceEventTriggerInstance<int>;
    using SequenceEventTriggerVec2Instance      = SequenceEventTriggerInstance<glm::vec2>;
    using SequenceEventTriggerVec3Instance      = SequenceEventTriggerInstance<glm::vec3>;
    using SequenceEventTriggerVec4Instance      = SequenceEventTriggerInstance<glm::vec4>;
}

/**
 * Helper macro
 */
#define DEFINE_SEQUENCEEVENTTRIGGER(Type)\
	RTTI_BEGIN_CLASS(Type)\
        RTTI_PROPERTY("Output",		    &Type::mOutput,	    nap::rtti::EPropertyMetaData::Required)\
        RTTI_PROPERTY("TriggerValue",	&Type::mValue,	    nap::rtti::EPropertyMetaData::Default)\
    RTTI_END_CLASS

/**
 * Helper macro
 */
#define DEFINE_SEQUENCEEVENTTRIGGERINSTANCE(Type)\
	RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(Type)                          \
        RTTI_CONSTRUCTOR(nap::TriggerHandlerComponentInstance&, nap::Trigger&) \
    RTTI_END_CLASS
