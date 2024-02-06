#pragma once

#include "trigger.h"

#include <parametersimple.h>
#include <parameternumeric.h>
#include <parametervec.h>

namespace nap
{
    //////////////////////////////////////////////////////////////////////////
    // EConditionalTriggerTypes
    //////////////////////////////////////////////////////////////////////////

    /**
     * Describes behaviour of the ConditionalNumericTrigger
     */
    enum NAPAPI EConditionalTriggerTypes : int
    {
        EQUALS,
        GREATER,
        SMALLER,
        GREATER_OR_EQUAL,
        SMALLER_OR_EQUAL
    };

    //////////////////////////////////////////////////////////////////////////
    // ConditionalNumericTrigger
    //////////////////////////////////////////////////////////////////////////

    /**
     * ConditionalNumericTrigger is triggered when a numeric parameter changes and the condition is met
     * @tparam T type of ParameterNumeric<T>
     */
    template<typename T>
    class NAPAPI ConditionalNumericTrigger : public Trigger
    {
    RTTI_ENABLE(Trigger)
    public:
        /**
         * Creates instance of this trigger
         * @param handlerInstance reference to TriggerHandlerComponentInstance
         * @return unique pointer of TriggerInstance
         */
        std::unique_ptr<TriggerInstance> createInstance(TriggerHandlerComponentInstance &handlerInstance) override;

        ResourcePtr<ParameterNumeric<T>> mParameter = nullptr; ///< Property: "Parameter" resource pointer to parameter
        T mValue = T(0); ///< Property: "TriggerValue" the value
        EConditionalTriggerTypes mCondition = EConditionalTriggerTypes::EQUALS; ///< Property: "Condition" the condition to be met
    };

    //////////////////////////////////////////////////////////////////////////
    // ConditionalNumericTriggerInstance<T>
    //////////////////////////////////////////////////////////////////////////

    /**
     * ConditionalNumericTriggerInstance is the instance of ConditionalNumericTrigger
     * @tparam T type of ParameterNumeric<T>
     */
    template<typename T>
    class NAPAPI ConditionalNumericTriggerInstance : public TriggerInstance
    {
    RTTI_ENABLE(TriggerInstance)
    public:
        /**
         * Constructor
         * @param handlerInstance reference to TriggerHandlerComponentInstance
         * @param resource reference to Trigger
         */
        ConditionalNumericTriggerInstance(TriggerHandlerComponentInstance& handlerInstance, Trigger& resource);

        /**
         * Removes from ParameterNumeric<T> changed signal
         */
        void onDestroy() override;
    protected:
        /**
         * Subscribes to ParameterNumeric<T> changed signal
         * @param errorState contains any errors
         * @return true on success
         */
        bool onInit(utility::ErrorState &errorState) override;
    private:
        /**
         * Called when ParameterNumeric<T> changes
         * @param newValue the new value
         */
        void onValueChanged(T newValue);
        Slot<T> mValueChangedSlot = { this, &ConditionalNumericTriggerInstance<T>::onValueChanged };

        ParameterNumeric<T>* mParameter = nullptr;
        T mValue = T(0);
        EConditionalTriggerTypes mCondition = EConditionalTriggerTypes::EQUALS;
        std::unordered_map<EConditionalTriggerTypes, std::function<void(const T&)>> mFunctionMap;
    };

    //////////////////////////////////////////////////////////////////////////
    // ConditionalNumericTrigger<T> template definitions
    //////////////////////////////////////////////////////////////////////////

    template<typename T>
    std::unique_ptr<TriggerInstance> ConditionalNumericTrigger<T>::createInstance(nap::TriggerHandlerComponentInstance &handlerInstance)
    {
        return std::make_unique<ConditionalNumericTriggerInstance<T>>(handlerInstance, *this);
    }

    //////////////////////////////////////////////////////////////////////////
    // ConditionalNumericTriggerInstance<T> template definitions
    //////////////////////////////////////////////////////////////////////////

    template<typename T>
    ConditionalNumericTriggerInstance<T>::ConditionalNumericTriggerInstance(TriggerHandlerComponentInstance& handlerInstance, Trigger& resource)
        : TriggerInstance(handlerInstance, resource)
    {
        mFunctionMap =
            {
                {EConditionalTriggerTypes::EQUALS,           [this](const T &newValue)
                                                             {
                                                                 if (newValue == mValue)
                                                                     trigger();
                                                             }},
                {EConditionalTriggerTypes::SMALLER,          [this](const T &newValue)
                                                             {
                                                                 if (newValue < mValue)
                                                                     trigger();
                                                             }},
                {EConditionalTriggerTypes::SMALLER_OR_EQUAL, [this](const T &newValue)
                                                             {
                                                                 if (newValue <= mValue)
                                                                     trigger();
                                                             }},
                {EConditionalTriggerTypes::GREATER,          [this](const T &newValue)
                                                             {
                                                                 if (newValue > mValue)
                                                                     trigger();
                                                             }},
                {EConditionalTriggerTypes::GREATER_OR_EQUAL, [this](const T &newValue)
                                                             {
                                                                 if (newValue >= mValue)
                                                                     trigger();
                                                             }}
            };
    }


    template<typename T>
    bool ConditionalNumericTriggerInstance<T>::onInit(utility::ErrorState &errorState)
    {
        auto& resource = static_cast<ConditionalNumericTrigger<T>&>(mResource);
        mParameter = resource.mParameter.get();
        mValue = resource.mValue;
        mCondition = resource.mCondition;
        mParameter->valueChanged.connect(mValueChangedSlot);
        return true;
    }

    template<typename T>
    void ConditionalNumericTriggerInstance<T>::onValueChanged(T newValue)
    {
        assert(mFunctionMap.find(mCondition)!=mFunctionMap.end());
        mFunctionMap[mCondition](newValue);
    }


    template<typename T>
    void ConditionalNumericTriggerInstance<T>::onDestroy()
    {
        mParameter->valueChanged.disconnect(mValueChangedSlot);
    }

    template<typename T>
    class NAPAPI ConditionalSimpleTrigger : public Trigger
    {
    RTTI_ENABLE(Trigger)
    public:
        std::unique_ptr<TriggerInstance> createInstance(nap::TriggerHandlerComponentInstance &handlerInstance) override;

        ResourcePtr<ParameterSimple<T>> mParameter = nullptr;
        T mValue = T(0);
        EConditionalTriggerTypes mCondition = EConditionalTriggerTypes::EQUALS;
    };

    template<typename T>
    class NAPAPI ConditionalSimpleTriggerInstance : public TriggerInstance
    {
    RTTI_ENABLE(TriggerInstance)
    public:
        ConditionalSimpleTriggerInstance(TriggerHandlerComponentInstance& handlerInstance, Trigger& resource);

        bool onInit(utility::ErrorState &errorState) override;

        void onDestroy() override;
    private:
        ParameterSimple<T>* mParameter = nullptr;
        T mValue;

        EConditionalTriggerTypes mCondition = EConditionalTriggerTypes::EQUALS;

        void onValueChanged(T newValue);
        Slot<T> mValueChangedSlot = { this, &ConditionalSimpleTriggerInstance<T>::onValueChanged };

        std::unordered_map<EConditionalTriggerTypes, std::function<void(const T&)>> mFunctionMap;
    };

    template<typename T>
    std::unique_ptr<TriggerInstance> ConditionalSimpleTrigger<T>::createInstance(nap::TriggerHandlerComponentInstance &handlerInstance)
    {
        return std::make_unique<ConditionalSimpleTriggerInstance<T>>(handlerInstance, *this);
    }

    template<typename T>
    ConditionalSimpleTriggerInstance<T>::ConditionalSimpleTriggerInstance(TriggerHandlerComponentInstance& handlerInstance, Trigger& resource)
        : TriggerInstance(handlerInstance, resource)
    {
        mFunctionMap =
            {
                {EConditionalTriggerTypes::EQUALS,           [this](const T &newValue)
                                                             {
                                                                 if (newValue == mValue)
                                                                     trigger();
                                                             }},
                {EConditionalTriggerTypes::SMALLER,          [this](const T &newValue)
                                                             {
                                                                 if (newValue < mValue)
                                                                     trigger();
                                                             }},
                {EConditionalTriggerTypes::SMALLER_OR_EQUAL, [this](const T &newValue)
                                                             {
                                                                 if (newValue <= mValue)
                                                                     trigger();
                                                             }},
                {EConditionalTriggerTypes::GREATER,          [this](const T &newValue)
                                                             {
                                                                 if (newValue > mValue)
                                                                     trigger();
                                                             }},
                {EConditionalTriggerTypes::GREATER_OR_EQUAL, [this](const T &newValue)
                                                             {
                                                                 if (newValue >= mValue)
                                                                     trigger();
                                                             }}
            };
    }


    template<typename T>
    bool ConditionalSimpleTriggerInstance<T>::onInit(utility::ErrorState &errorState)
    {
        auto& resource = static_cast<ConditionalSimpleTrigger<T>&>(mResource);
        mParameter = resource.mParameter.get();
        mValue = resource.mValue;
        mCondition = resource.mCondition;
        mParameter->valueChanged.connect(mValueChangedSlot);

        return true;
    }

    template<typename T>
    void ConditionalSimpleTriggerInstance<T>::onValueChanged(T newValue)
    {
        assert(mFunctionMap.find(mCondition)!=mFunctionMap.end());
        mFunctionMap[mCondition](newValue);
    }

    template<typename T>
    void ConditionalSimpleTriggerInstance<T>::onDestroy()
    {
        mParameter->valueChanged.disconnect(mValueChangedSlot);
    }

    //////////////////////////////////////////////////////////////////////////
    // ConditionalTrigger<T> type definitions
    //////////////////////////////////////////////////////////////////////////

    using ConditionalTriggerFloat   = ConditionalNumericTrigger<float>;
    using ConditionalTriggerInt     = ConditionalNumericTrigger<int>;
    using ConditionalTriggerDouble  = ConditionalNumericTrigger<double>;
    using ConditionalTriggerLong    = ConditionalNumericTrigger<long>;
    using ConditionalTriggerString  = ConditionalSimpleTrigger<std::string>;
    using ConditionalTriggerBool    = ConditionalSimpleTrigger<bool>;

    using ConditionalTriggerFloatInstance   = ConditionalNumericTriggerInstance<float>;
    using ConditionalTriggerIntInstance     = ConditionalNumericTriggerInstance<int>;
    using ConditionalTriggerDoubleInstance  = ConditionalNumericTriggerInstance<double>;
    using ConditionalTriggerLongInstance    = ConditionalNumericTriggerInstance<long>;
    using ConditionalTriggerStringInstance  = ConditionalSimpleTriggerInstance<std::string>;
    using ConditionalTriggerBoolInstance    = ConditionalSimpleTriggerInstance<bool>;
}

/**
 * Helper macro
 */
#define DEFINE_CONDITIONALTRIGGER(Type) \
	RTTI_BEGIN_CLASS(Type)\
		RTTI_PROPERTY("Parameter",		&Type::mParameter,		nap::rtti::EPropertyMetaData::Required)\
		RTTI_PROPERTY("TriggerValue",	&Type::mValue,	        nap::rtti::EPropertyMetaData::Default)\
        RTTI_PROPERTY("Condition",	    &Type::mCondition,	    nap::rtti::EPropertyMetaData::Default)\
    RTTI_END_CLASS

/**
 * Helper macro
 */
#define DEFINE_CONDITIONALTRIGGERINSTANCE(Type)\
	RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(Type)                          \
        RTTI_CONSTRUCTOR(nap::TriggerHandlerComponentInstance&, nap::Trigger&) \
    RTTI_END_CLASS
