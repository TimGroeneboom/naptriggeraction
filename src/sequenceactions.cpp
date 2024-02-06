#include "sequenceactions.h"
#include "triggeractionutils.h"

RTTI_BEGIN_ENUM(nap::ETriggerSequenceActionTypes)
    RTTI_ENUM_VALUE(nap::ETriggerSequenceActionTypes::PLAY, "Play"),
    RTTI_ENUM_VALUE(nap::ETriggerSequenceActionTypes::STOP, "Stop"),
    RTTI_ENUM_VALUE(nap::ETriggerSequenceActionTypes::PAUSE, "Pause"),
    RTTI_ENUM_VALUE(nap::ETriggerSequenceActionTypes::UNPAUSE, "Unpause"),
    RTTI_ENUM_VALUE(nap::ETriggerSequenceActionTypes::STOP, "Stop"),
    RTTI_ENUM_VALUE(nap::ETriggerSequenceActionTypes::ENABLE_LOOP, "Enable Loop"),
    RTTI_ENUM_VALUE(nap::ETriggerSequenceActionTypes::DISABLE_LOOP, "Disable Loop"),
    RTTI_ENUM_VALUE(nap::ETriggerSequenceActionTypes::REWIND, "Rewind")
RTTI_END_ENUM

RTTI_BEGIN_CLASS(nap::SequenceAction)
    RTTI_PROPERTY("ActionType",     &nap::SequenceAction::mActionType,  nap::rtti::EPropertyMetaData::Default)
    RTTI_PROPERTY("SequencePlayer", &nap::SequenceAction::mPlayer,      nap::rtti::EPropertyMetaData::Required)
RTTI_END_CLASS

RTTI_BEGIN_CLASS(nap::SequenceSetTimeAction)
        RTTI_PROPERTY("FloatArgName",   &nap::SequenceSetTimeAction::mFloatArgName, nap::rtti::EPropertyMetaData::Default)
        RTTI_PROPERTY("SequencePlayer", &nap::SequenceSetTimeAction::mPlayer,       nap::rtti::EPropertyMetaData::Required)
RTTI_END_CLASS

RTTI_BEGIN_CLASS(nap::SequenceSetPlaybackSpeedAction)
        RTTI_PROPERTY("FloatArgName",   &nap::SequenceSetPlaybackSpeedAction::mFloatArgName, nap::rtti::EPropertyMetaData::Default)
        RTTI_PROPERTY("SequencePlayer", &nap::SequenceSetPlaybackSpeedAction::mPlayer,       nap::rtti::EPropertyMetaData::Required)
RTTI_END_CLASS

RTTI_BEGIN_CLASS(nap::SequenceLoadAction)
        RTTI_PROPERTY("ArgumentName",   &nap::SequenceLoadAction::mArgumentName,    nap::rtti::EPropertyMetaData::Default)
        RTTI_PROPERTY("SequencePlayer", &nap::SequenceLoadAction::mPlayer,          nap::rtti::EPropertyMetaData::Required)
RTTI_END_CLASS

namespace nap
{
    SequenceAction::SequenceAction()
    {
        mFunctionMap =
        {
            {ETriggerSequenceActionTypes::PLAY,         [this](){ mPlayer->setIsPlaying(true); }},
            {ETriggerSequenceActionTypes::STOP,         [this](){ mPlayer->setIsPlaying(false); }},
            {ETriggerSequenceActionTypes::PAUSE,        [this](){ mPlayer->setIsPaused(true); }},
            {ETriggerSequenceActionTypes::UNPAUSE,      [this](){ mPlayer->setIsPaused(false); }},
            {ETriggerSequenceActionTypes::DISABLE_LOOP, [this](){ mPlayer->setIsLooping(false); }},
            {ETriggerSequenceActionTypes::ENABLE_LOOP,  [this](){ mPlayer->setIsLooping(true); }},
            {ETriggerSequenceActionTypes::REWIND,       [this](){ mPlayer->setPlayerTime(0.0f); }},
        };
    }


    bool SequenceAction::onExecute(const APIEventPtr& event,
                                   utility::ErrorState &errorState)
    {
        assert(mFunctionMap.find(mActionType)!=mFunctionMap.end());
        mFunctionMap.find(mActionType)->second();
        return true;
    }


    bool SequenceSetTimeAction::onExecute(const APIEventPtr& event, utility::ErrorState &errorState)
    {
        float value = 0.0f;
        if(!utility::extractArgumentValue<float>(value, mFloatArgName, event, errorState))
        {
            return false;
        }

        mPlayer->setPlayerTime(value);

        return true;
    }


    bool SequenceSetPlaybackSpeedAction::onExecute(const APIEventPtr& event, utility::ErrorState &errorState)
    {
        float value = 0.0f;
        if(!utility::extractArgumentValue<float>(value, mFloatArgName, event, errorState))
            return false;

        mPlayer->setPlaybackSpeed(value);

        return true;
    }

    bool SequenceLoadAction::onExecute(const APIEventPtr& event, utility::ErrorState &errorState)
    {
        std::string value = "";
        if(!utility::extractArgumentValue<std::string>(value, mArgumentName, event, errorState))
            return false;

        if(!mPlayer->load(value, errorState))
            return false;

        return true;
    }
}