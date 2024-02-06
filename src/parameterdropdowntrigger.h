#pragma once

#include <parameterdropdown.h>

#include "trigger.h"

namespace nap
{
    //////////////////////////////////////////////////////////////////////////
    // ParameterDropdownTrigger
    //////////////////////////////////////////////////////////////////////////

    /**
     * ParameterDropdownTrigger triggers when a ParameterDropdown selection is changed.
     * The TriggerInstance will add two TriggerValues when triggered:
     * - "DropdownSelectionIndex" the index of the selection, this is and APIValue<int> with argument name as set in the mIndexArgumentName property
     * - "DropdownSelection" the selection, this is and APIValue<std::string> with argument name as set in the mSelectionArgumentName property
     */
    class NAPAPI ParameterDropdownTrigger : public Trigger
    {
    RTTI_ENABLE(Trigger)
    public:
        /**
         * Creates instance of this trigger
         * @param triggerHandler reference to TriggerHandlerComponentInstance creating this TriggerInstance
         * @return unique pointer of TriggerInstance
         */
        std::unique_ptr<TriggerInstance> createInstance(TriggerHandlerComponentInstance& triggerHandler) final;

        ResourcePtr<ParameterDropDown> mDropdown;   ///< Property: "Dropdown" the ParameterDropdown to register to
        std::string mIndexArgumentName = "DropdownSelectionIndex"; ///< Property: "IndexArgumentName" the name of the argument that contains the selection index
        std::string mSelectionArgumentName = "DropdownSelection"; ///< Property: "SelectionArgumentName" the name of the argument that contains the selection
    };

    //////////////////////////////////////////////////////////////////////////
    // ParameterDropdownTriggerInstance
    //////////////////////////////////////////////////////////////////////////

    /**
     * The instance of ParameterDropdownTrigger
     */
    class NAPAPI ParameterDropdownTriggerInstance : public TriggerInstance
    {
    RTTI_ENABLE(TriggerInstance)
    public:
        /**
         * Constructor
         * @param triggerHandler reference to TriggerHandlerComponentInstance creating this TriggerInstance
         * @param trigger reference to resource of Trigger
         */
        ParameterDropdownTriggerInstance(TriggerHandlerComponentInstance& triggerHandler, Trigger& trigger);
    protected:
        /**
         * Connects to ParameterDropdown
         * @param errorState contains any errors
         * @return true on success
         */
        bool onInit(utility::ErrorState& errorState) override;

        /**
         * Disconnects from ParameterDropdown
         */
        void onDestroy() override;

        /**
         * Creates APIEvent with arguments and adds index argument and selection argument
         * @return APIEvent
         */
        APIEventPtr createAPIEvent() override;
    private:
        Slot<int> mSelectionChangedSlot;
        void onSelectionChanged(int selection);

        ParameterDropDown* mDropDown = nullptr;
        std::string mIndexArgumentName = "DropdownSelectionIndex";
        std::string mSelectionArgumentName = "DropdownSelection";
    };
}