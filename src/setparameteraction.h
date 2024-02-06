#pragma once

#include <parameternumeric.h>
#include <parametersimple.h>
#include <parametervec.h>

#include "triggeraction.h"
#include "triggerhandlercomponent.h"

namespace nap
{
    //////////////////////////////////////////////////////////////////////////
    // SetParameterSimpleAction
    //////////////////////////////////////////////////////////////////////////

    /**
     * Sets a parameter on execution. Template type is type of Parameter to set.
     * Argument name is the argument name the actions expects to be present in the APIEvent
     * @tparam T type of parameter
     */
    template<typename T>
    class NAPAPI SetParameterSimpleAction : public TriggerAction
    {
    RTTI_ENABLE(TriggerAction)
    public:
        ResourcePtr<ParameterSimple<T>> mParameter; ///< Property: "Parameter" resource pointer to parameter
        std::string mArgumentName; ///< Property: "ArgumentName" expected argument in API Event that contains value to set parameter to
    protected:
        /**
         * Called on execution, sets parameter value
         * @param event the API event
         * @param errorState can contain errors
         * @return true on success
         */
        bool onExecute(const APIEventPtr& event, utility::ErrorState& errorState) override;
    };

    //////////////////////////////////////////////////////////////////////////
    // SetParameterNumericAction
    //////////////////////////////////////////////////////////////////////////

    /**
     * Sets a parameter on execution. Template type is type of Parameter to set.
     * Argument name is the argument name the actions expects to be present in the APIEvent
     * @tparam T type of parameter
     */
    template<typename T>
    class NAPAPI SetParameterNumericAction : public TriggerAction
    {
    RTTI_ENABLE(TriggerAction)
    public:
        ResourcePtr<ParameterSimple<T>> mParameter; ///< Property: "Parameter" resource pointer to parameter
        std::string mArgumentName; ///< Property: "ArgumentName" expected argument in API Event that contains value to set parameter to
    protected:
        /**
         * Called on execution, sets parameter value
         * @param event the API event
         * @param errorState can contain errors
         * @return true on success
         */
        bool onExecute(const APIEventPtr& event, utility::ErrorState& errorState) override;
    };

    //////////////////////////////////////////////////////////////////////////
    // SetParameterVecAction
    //////////////////////////////////////////////////////////////////////////

    /**
     * Sets a parameter on execution. Template type is type of Parameter to set.
     * Argument name is the argument name the actions expects to be present in the APIEvent
     * @tparam T type of parameter
     */
    template<typename T>
    class NAPAPI SetParameterVecAction : public TriggerAction
    {
    RTTI_ENABLE(TriggerAction)
    public:
        ResourcePtr<ParameterSimple<T>> mParameter; ///< Property: "Parameter" resource pointer to parameter
        std::string mArgumentName; ///< Property: "ArgumentName" expected argument in API Event that contains value to set parameter to
    protected:
        /**
         * Called on execution, sets parameter value
         * @param event the API event
         * @param errorState can contain errors
         * @return true on success
         */
        bool onExecute(const APIEventPtr& event, utility::ErrorState& errorState) override;
    };

    //////////////////////////////////////////////////////////////////////////
    // SetParameterAction type definitions
    //////////////////////////////////////////////////////////////////////////

    using SetParameterFloatAction   = SetParameterNumericAction<float>;
    using SetParameterStringAction  = SetParameterSimpleAction<std::string>;
    using SetParameterIntAction     = SetParameterNumericAction<int>;
    using SetParameterBoolAction    = SetParameterSimpleAction<bool>;
    using SetParameterLongAction    = SetParameterNumericAction<long>;
    using SetParameterDoubleAction  = SetParameterNumericAction<double>;
    using SetParameterVec2Action    = SetParameterVecAction<glm::vec2>;
    using SetParameterVec3Action    = SetParameterVecAction<glm::vec3>;
    using SetParameterVec4Action    = SetParameterVecAction<glm::vec4>;

    //////////////////////////////////////////////////////////////////////////
    // SetParameterSimpleAction template definition
    //////////////////////////////////////////////////////////////////////////

    template<typename T>
    bool SetParameterSimpleAction<T>::onExecute(const APIEventPtr& event, utility::ErrorState& errorState)
    {
        T value;
        if(!utility::extractArgumentValue<T>(value, mArgumentName, event, errorState))
            return false;
        mParameter->setValue(value);

        return true;
    }

    //////////////////////////////////////////////////////////////////////////
    // SetParameterNumericAction template definition
    //////////////////////////////////////////////////////////////////////////

    template<typename T>
    bool SetParameterNumericAction<T>::onExecute(const APIEventPtr& event, utility::ErrorState& errorState)
    {
        T value;
        if(!utility::extractArgumentValue<T>(value, mArgumentName, event, errorState))
            return false;
        mParameter->setValue(value);

        return true;
    }

    //////////////////////////////////////////////////////////////////////////
    // SetParameterVecAction template definition
    //////////////////////////////////////////////////////////////////////////

    template<typename T>
    bool SetParameterVecAction<T>::onExecute(const APIEventPtr& event, utility::ErrorState& errorState)
    {
        T value;
        if(!utility::extractArgumentValue<T>(value, mArgumentName, event, errorState))
            return false;
        mParameter->setValue(value);

        return true;
    }
}


/**
 * Helper macro that can be used to define the RTTI for a simple set parameter trigger action
 */
#define DEFINE_TRIGGERPARAMETERACTION(Type)															   \
	RTTI_BEGIN_CLASS(Type)																			   \
		RTTI_PROPERTY("Parameter",		&Type::mParameter,		nap::rtti::EPropertyMetaData::Required)\
		RTTI_PROPERTY("ArgumentName",	&Type::mArgumentName,	nap::rtti::EPropertyMetaData::Default) \
	RTTI_END_CLASS
