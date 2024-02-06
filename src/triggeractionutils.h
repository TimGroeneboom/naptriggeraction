#pragma once

#include <apiargument.h>
#include <nap/core.h>

namespace nap
{
    namespace utility
    {
        /**
         * Extracts argument with type and name from given std::vector containing APIBaseValue pointers. Returns false
         * on failure and true on success. ErrorState contains any errors. On success, value contains value extracted
         * @tparam T the type of value to extract
         * @param value reference to value to set
         * @param argName the argument name
         * @param event the APIEvent to extract from
         * @param errorState contains any errors that occurred during extraction
         * @return true on success
         */
        template<typename T>
        bool extractArgumentValue(T& value, const std::string& argName, const APIEventPtr& event, utility::ErrorState& errorState)
        {
            // Get arguments
            const auto& args = event->getArguments();
            const APIArgument* base_arg = nullptr;

            // Find argument with name
            auto args_it = std::find_if(args.begin(), args.end(), [&argName](const auto& arg)
            {
                return arg->getName()==argName;
            });
            if(!errorState.check(args_it!=args.end(), "Cannot find argument with name %s", argName.c_str()))
                return false;

            // Check if argument has the correct type
            if(!errorState.check(base_arg->getValueType() == RTTI_OF(T),
                                 "Argument of wrong type, expected %s got %s",
                                 base_arg->getValueType().get_name().to_string().c_str(),
                                 RTTI_OF(T).get_name().to_string().c_str()))
                return false;

            // Set the value
            const auto& arg = static_cast<const APIValue<T>&>(base_arg->getValue());
            value = arg.mValue;

            return true;
        }
    }
}