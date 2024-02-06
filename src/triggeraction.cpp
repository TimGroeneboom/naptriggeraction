#include "triggeraction.h"

#include <nap/logger.h>

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::TriggerAction)
RTTI_END_CLASS

RTTI_BEGIN_CLASS(nap::TriggerActionGroup)
    RTTI_PROPERTY(nap::group::triggeraction::members,	&nap::TriggerActionGroup ::mMembers,	nap::rtti::EPropertyMetaData::Embedded | nap::rtti::EPropertyMetaData::ReadOnly)
    RTTI_PROPERTY(nap::group::triggeraction::children,	&nap::TriggerActionGroup::mChildren,	nap::rtti::EPropertyMetaData::Embedded | nap::rtti::EPropertyMetaData::ReadOnly)
RTTI_END_CLASS

namespace nap
{
    template<>
    nap::Group<TriggerAction>::Group() : IGroup(RTTI_OF(TriggerAction), group::triggeraction::members, group::triggeraction::children) { }

    TriggerAction::TriggerAction()
    {
    }


    bool TriggerAction::init(utility::ErrorState& errorState)
    {
        if(!onInit(errorState))
            return false;

        return true;
    }


    void TriggerAction::onDestroy()
    {
        destroy();
    }


    void TriggerAction::execute(const APIEventPtr& event)
    {
        utility::ErrorState error_state;
        if(!onExecute(event, error_state))
        {
            nap::Logger::error(*this, error_state.toString());
        }
    }
}
