#pragma once

#include "triggeraction.h"

namespace nap
{
    //////////////////////////////////////////////////////////////////////////
    // TriggerLogAction
    //////////////////////////////////////////////////////////////////////////

    /**
     * Prints a message to the console when executed
     */
    class NAPAPI TriggerLogAction : public TriggerAction
    {
    RTTI_ENABLE(TriggerAction)
    public:
        /**
         * Prints a message to the console when executed
         */
        bool onExecute(const APIEventPtr& event, utility::ErrorState& errorState) override;

        std::string mLogMessage = ""; ///< Property: "LogMessage" message being printed
    };
}