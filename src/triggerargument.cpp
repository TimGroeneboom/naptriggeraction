#include "triggerargument.h"

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::TriggerBaseArgument)
        RTTI_PROPERTY("Name", &nap::TriggerBaseArgument::mName, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

DEFINE_TRIGGERARGUMENT(nap::TriggerArgumentInt);
DEFINE_TRIGGERARGUMENT(nap::TriggerArgumentDouble);
DEFINE_TRIGGERARGUMENT(nap::TriggerArgumentString);
DEFINE_TRIGGERARGUMENT(nap::TriggerArgumentBool);
DEFINE_TRIGGERARGUMENT(nap::TriggerArgumentFloat);
DEFINE_TRIGGERARGUMENT(nap::TriggerArgumentLong);
DEFINE_TRIGGERARGUMENT(nap::TriggerArgumentVec2);
DEFINE_TRIGGERARGUMENT(nap::TriggerArgumentVec3);
DEFINE_TRIGGERARGUMENT(nap::TriggerArgumentVec4);