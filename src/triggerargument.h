#pragma once

#include <apisignature.h>
#include <apiservice.h>


namespace nap
{
    //////////////////////////////////////////////////////////////////////////
    // TriggerBaseValue
    //////////////////////////////////////////////////////////////////////////

    /**
     * TriggerBaseArgument is abstract class, contains a method called createAPIValue to create a unique ptr to an
     * APIBaseValue
     */
    class NAPAPI TriggerBaseArgument : public Resource
    {
    RTTI_ENABLE(Resource)
    public:
        /**
         * Must be extended
         * @return unique pointer to APIBaseValue containing value
         */
        virtual std::unique_ptr<APIBaseValue> createAPIValue() = 0;

        std::string mName = ""; ///< Property: "Name" name of value
    };

    //////////////////////////////////////////////////////////////////////////
    // TriggerArgument<T>
    //////////////////////////////////////////////////////////////////////////

    template<typename T>
    class NAPAPI TriggerArgument : public TriggerBaseArgument
    {
    RTTI_ENABLE(TriggerBaseArgument)
    public:
        std::unique_ptr<APIBaseValue> createAPIValue() override;

        T mValue = T(); ///< Property: "Value" contains the value
    };


    template<typename T>
    std::unique_ptr<APIBaseValue> TriggerArgument<T>::createAPIValue()
    {
        APIValue<T> api_value = APIValue<T>(mName, mValue);
        return std::make_unique<APIValue<T>>(api_value);
    }

    //////////////////////////////////////////////////////////////////////////
    // TriggerArgument template type definitions
    //////////////////////////////////////////////////////////////////////////

    using TriggerArgumentInt       = TriggerArgument<int>;
    using TriggerArgumentBool      = TriggerArgument<bool>;
    using TriggerArgumentFloat     = TriggerArgument<float>;
    using TriggerArgumentDouble    = TriggerArgument<double>;
    using TriggerArgumentString    = TriggerArgument<std::string>;
    using TriggerArgumentLong      = TriggerArgument<long>;
    using TriggerArgumentVec2      = TriggerArgument<glm::vec2>;
    using TriggerArgumentVec3      = TriggerArgument<glm::vec3>;
    using TriggerArgumentVec4      = TriggerArgument<glm::vec4>;
}

/**
 * Helper macro
 */
#define DEFINE_TRIGGERARGUMENT(Type)\
	RTTI_BEGIN_CLASS(Type)                          \
        RTTI_PROPERTY("Value", &Type::mValue, nap::rtti::EPropertyMetaData::Default) \
    RTTI_END_CLASS
