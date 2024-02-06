#pragma once

#include <nap/service.h>

namespace nap
{
    class NAPAPI TriggerActionService final : public Service
    {
    RTTI_ENABLE(Service)
    public:
        TriggerActionService(ServiceConfiguration* configuration);

        virtual ~TriggerActionService();

        void registerObjectCreators(rtti::Factory &factory) override;
    };
}
