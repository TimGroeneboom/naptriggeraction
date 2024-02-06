#include "parameterbuttontrigger.h"
#include "triggerhandlercomponent.h"

RTTI_BEGIN_CLASS(nap::ParameterButtonTrigger)
    RTTI_PROPERTY("Button", &nap::ParameterButtonTrigger::mButton, nap::rtti::EPropertyMetaData::Required)
RTTI_END_CLASS

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::ParameterButtonTriggerInstance)
    RTTI_CONSTRUCTOR(nap::TriggerHandlerComponentInstance&, nap::Trigger&)
RTTI_END_CLASS

namespace nap
{
    std::unique_ptr<TriggerInstance> ParameterButtonTrigger::createInstance(TriggerHandlerComponentInstance& triggerHandler)
    {
        return std::make_unique<ParameterButtonTriggerInstance>(triggerHandler, *this);
    }


    ParameterButtonTriggerInstance::ParameterButtonTriggerInstance(TriggerHandlerComponentInstance& triggerHandler, Trigger& trigger)
        : TriggerInstance(triggerHandler, trigger)
    {
        mButtonClickedSlot.setFunction([this](){ onButtonClicked(); });
    }


    bool ParameterButtonTriggerInstance::onInit(utility::ErrorState& errorState)
    {
        auto& parameter_button_trigger = static_cast<ParameterButtonTrigger&>(mResource);
        parameter_button_trigger.mButton->click.connect(mButtonClickedSlot);
        return true;
    }


    void ParameterButtonTriggerInstance::onDestroy()
    {
        mButtonClickedSlot.disconnect();
    }


    void ParameterButtonTriggerInstance::onButtonClicked()
    {
        trigger();
    }
}