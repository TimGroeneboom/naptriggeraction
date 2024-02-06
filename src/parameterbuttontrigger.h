#pragma once

#include <parameterbutton.h>

#include "trigger.h"

namespace nap
{
    //////////////////////////////////////////////////////////////////////////
    // ParameterButtonTrigger
    //////////////////////////////////////////////////////////////////////////

    /**
     * ParameterButtonTrigger triggers when a ParameterButton is clicked
     */
    class NAPAPI ParameterButtonTrigger : public Trigger
    {
    RTTI_ENABLE(Trigger)
    public:
        /**
         * Creates instance of this trigger
         * @param triggerHandler reference to TriggerHandlerComponentInstance creating this TriggerInstance
         * @return unique pointer of TriggerInstance
         */
        std::unique_ptr<TriggerInstance> createInstance(TriggerHandlerComponentInstance& triggerHandler) final;

        ResourcePtr<ParameterButton> mButton; ///< Property: "Button" the ParameterButton to register to
    };

    //////////////////////////////////////////////////////////////////////////
    // ParameterButtonTriggerInstance
    //////////////////////////////////////////////////////////////////////////

    /**
     * The instance of ParameterButtonTrigger
     */
    class NAPAPI ParameterButtonTriggerInstance : public TriggerInstance
    {
    RTTI_ENABLE(TriggerInstance)
    public:
        /**
         * Constructor
         * @param triggerHandler reference to TriggerHandlerComponentInstance creating this TriggerInstance
         * @param trigger reference to resource of Trigger
         */
        ParameterButtonTriggerInstance(TriggerHandlerComponentInstance& triggerHandler, Trigger& trigger);
    protected:
        /**
         * Connects to ParameterButton
         * @param errorState contains any errors
         * @return true on success
         */
        bool onInit(utility::ErrorState& errorState) override;

        /**
         * Disconnects from ParameterButton
         */
        void onDestroy() override;
    private:
        Slot<> mButtonClickedSlot;
        void onButtonClicked();
    };
}