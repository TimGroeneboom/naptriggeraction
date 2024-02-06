#include "parameterdropdowntrigger.h"
#include "triggerhandlercomponent.h"

#include "triggerargument.h"

RTTI_BEGIN_CLASS(nap::ParameterDropdownTrigger)
    RTTI_PROPERTY("Dropdown",               &nap::ParameterDropdownTrigger::mDropdown,              nap::rtti::EPropertyMetaData::Required)
    RTTI_PROPERTY("IndexArgumentName",      &nap::ParameterDropdownTrigger::mIndexArgumentName,     nap::rtti::EPropertyMetaData::Default)
    RTTI_PROPERTY("SelectionArgumentName",  &nap::ParameterDropdownTrigger::mSelectionArgumentName, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::ParameterDropdownTriggerInstance)
    RTTI_CONSTRUCTOR(nap::TriggerHandlerComponentInstance&, nap::Trigger&)
RTTI_END_CLASS

namespace nap
{
    std::unique_ptr<TriggerInstance> ParameterDropdownTrigger::createInstance(TriggerHandlerComponentInstance& triggerHandler)
    {
        return std::make_unique<ParameterDropdownTriggerInstance>(triggerHandler, *this);
    }


    ParameterDropdownTriggerInstance::ParameterDropdownTriggerInstance(nap::TriggerHandlerComponentInstance &triggerHandler, nap::Trigger &trigger)
        : TriggerInstance(triggerHandler, trigger)
    {
        mSelectionChangedSlot.setFunction([this](int selection){ onSelectionChanged(selection); });
    }


    bool ParameterDropdownTriggerInstance::onInit(utility::ErrorState &errorState)
    {
        // copy resource properties
        auto& parameter_dropdown_trigger = static_cast<ParameterDropdownTrigger&>(mResource);
        mDropDown = parameter_dropdown_trigger.mDropdown.get();
        mSelectionArgumentName = parameter_dropdown_trigger.mSelectionArgumentName;
        mIndexArgumentName = parameter_dropdown_trigger.mIndexArgumentName;
        mDropDown->indexChanged.connect(mSelectionChangedSlot);

        // check if the argument names are already used
        auto it = std::find_if(mArguments.begin(), mArguments.end(), [this](const auto& argument)
        {
            return argument->mName == mIndexArgumentName || argument->mName == mSelectionArgumentName;
        });
        if(it!=mArguments.end())
        {
            errorState.fail(utility::stringFormat("ParameterDropdownTriggerInstance : Argument name %s already used", (*it)->mName.c_str()));
            return false;
        }

        return true;
    }


    void ParameterDropdownTriggerInstance::onDestroy()
    {
        mSelectionChangedSlot.disconnect();
    }


    void ParameterDropdownTriggerInstance::onSelectionChanged(int selection)
    {
        trigger();
    }


    APIEventPtr ParameterDropdownTriggerInstance::createAPIEvent()
    {
        auto api_event = TriggerInstance::createAPIEvent();
        api_event->addArgument(std::make_unique<APIValue<int>>(mIndexArgumentName, mDropDown->getSelectedIndex()));
        api_event->addArgument(std::make_unique<APIValue<std::string>>(mSelectionArgumentName, mDropDown->mItems[mDropDown->getSelectedIndex()]));
        return api_event;
    }
}