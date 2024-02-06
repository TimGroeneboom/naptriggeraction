#pragma once

#include <parameterservice.h>

#include "triggeraction.h"
#include "parametergroup.h"

namespace nap
{
    class NAPAPI PresetLoadAction final : public TriggerAction
    {
    RTTI_ENABLE(TriggerAction)
    public:
        PresetLoadAction(ParameterService& parameterService);

        ResourcePtr<ParameterGroup> mGroup = nullptr;
        std::string mPresetName = "";
    protected:
        /**
         * Executes action
         * @param event the API event create by the trigger
         * @param errorState can contain any error on execution
         * @return true on success
         */
        bool onExecute(const APIEventPtr& event, utility::ErrorState &errorState) override;
    private:
        ParameterService& mParameterService;
    };

    using PresetLoadActionObjectCreator = rtti::ObjectCreator<PresetLoadAction, ParameterService>;
}