#include "triggerlogaction.h"

#include <nap/logger.h>

RTTI_BEGIN_CLASS(nap::TriggerLogAction)
        RTTI_PROPERTY("LogMessage", &nap::TriggerLogAction::mLogMessage, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

namespace nap
{
    bool TriggerLogAction::onExecute(const APIEventPtr& event, utility::ErrorState& errorState)
    {
        nap::Logger::info(mLogMessage);
        return true;
    }
}