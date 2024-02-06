#include "conditionaltrigger.h"
#include "triggerhandlercomponent.h"

RTTI_BEGIN_ENUM(nap::EConditionalTriggerTypes)
    RTTI_ENUM_VALUE(nap::EConditionalTriggerTypes::EQUALS, "Equals"),
    RTTI_ENUM_VALUE(nap::EConditionalTriggerTypes::SMALLER, "Smaller"),
    RTTI_ENUM_VALUE(nap::EConditionalTriggerTypes::GREATER, "Greater"),
    RTTI_ENUM_VALUE(nap::EConditionalTriggerTypes::SMALLER_OR_EQUAL, "Smaller or Equals"),
    RTTI_ENUM_VALUE(nap::EConditionalTriggerTypes::GREATER_OR_EQUAL, "Greater or Equals")
RTTI_END_ENUM

DEFINE_CONDITIONALTRIGGER(nap::ConditionalTriggerFloat)
DEFINE_CONDITIONALTRIGGER(nap::ConditionalTriggerInt)
DEFINE_CONDITIONALTRIGGER(nap::ConditionalTriggerDouble)
DEFINE_CONDITIONALTRIGGER(nap::ConditionalTriggerLong)
DEFINE_CONDITIONALTRIGGER(nap::ConditionalTriggerString)
DEFINE_CONDITIONALTRIGGER(nap::ConditionalTriggerBool)

DEFINE_CONDITIONALTRIGGERINSTANCE(nap::ConditionalTriggerFloatInstance)
DEFINE_CONDITIONALTRIGGERINSTANCE(nap::ConditionalTriggerIntInstance)
DEFINE_CONDITIONALTRIGGERINSTANCE(nap::ConditionalTriggerDoubleInstance)
DEFINE_CONDITIONALTRIGGERINSTANCE(nap::ConditionalTriggerLongInstance)
DEFINE_CONDITIONALTRIGGERINSTANCE(nap::ConditionalTriggerStringInstance)
DEFINE_CONDITIONALTRIGGERINSTANCE(nap::ConditionalTriggerBoolInstance)