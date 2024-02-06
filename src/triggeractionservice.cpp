#include "triggeractionservice.h"
#include "presetloadaction.h"


RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::TriggerActionService)
        RTTI_CONSTRUCTOR(nap::ServiceConfiguration*)
RTTI_END_CLASS

namespace nap
{
    TriggerActionService::TriggerActionService(ServiceConfiguration* configuration) : Service(configuration)
    {
    }

    TriggerActionService::~TriggerActionService(){}


    void TriggerActionService::registerObjectCreators(rtti::Factory &factory)
    {
        auto* parameter_service = getCore().getService<ParameterService>();
        factory.addObjectCreator(std::make_unique<PresetLoadActionObjectCreator>(*parameter_service));
    }
}