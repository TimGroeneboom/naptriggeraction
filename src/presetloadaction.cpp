#include "presetloadaction.h"

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::PresetLoadAction)
    RTTI_CONSTRUCTOR(nap::ParameterService&)
    RTTI_PROPERTY("Group", &nap::PresetLoadAction::mGroup, nap::rtti::EPropertyMetaData::Required)
    RTTI_PROPERTY("PresetName", &nap::PresetLoadAction::mPresetName, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

namespace nap
{
    PresetLoadAction::PresetLoadAction(nap::ParameterService &parameterService) : TriggerAction(), mParameterService(parameterService){}

    bool PresetLoadAction::onExecute(const nap::APIEventPtr &event, utility::ErrorState &errorState)
    {
        std::string preset;
        if(!utility::extractArgumentValue(preset, mPresetName, event, errorState))
            return false;

        if(!mParameterService.loadPreset(*mGroup.get(), preset, errorState))
            return false;

        return true;
    }
}