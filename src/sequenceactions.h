#pragma once

#include <sequenceplayer.h>

#include "triggeraction.h"

namespace nap
{
    /**
     * TriggerSequenceActionTypes
     * Enum containing different actions that a SequenceAction can perform
     */
    enum ETriggerSequenceActionTypes : int
    {
        PLAY            = 0,
        STOP            = 1,
        PAUSE           = 2,
        UNPAUSE         = 3,
        REWIND          = 4,
        ENABLE_LOOP     = 5,
        DISABLE_LOOP    = 6
    };

    //////////////////////////////////////////////////////////////////////////
    // SequenceAction
    //////////////////////////////////////////////////////////////////////////

    /**
     * A SequenceAction performs actions on a SequencePlayer when triggerred. Actions are set by 'mActionType' property
     * which is a ETriggerSequenceActionTypes enum
     */
    class NAPAPI SequenceAction : public TriggerAction
    {
    RTTI_ENABLE(TriggerAction)
    public:
        /*
         * Constructor, creates function map for each ETriggerSequenceActionTypes type
         */
        SequenceAction();

        ETriggerSequenceActionTypes mActionType = ETriggerSequenceActionTypes::PLAY; ///< Property: "ActionType" describes the SequenceAction
        ResourcePtr<SequencePlayer> mPlayer = nullptr; ///< Property: "Player" required ResourcePtr to SequencePlayer
    protected:
        /**
         * Executes action
         * @param event the API event created by the trigger
         * @param errorState can contain any error on execution
         * @return true on success
         */
        bool onExecute(const APIEventPtr& event, utility::ErrorState &errorState) override;
    private:
        std::unordered_map<ETriggerSequenceActionTypes, std::function<void()>> mFunctionMap;
    };

    //////////////////////////////////////////////////////////////////////////
    // SequenceSetTimeAction
    //////////////////////////////////////////////////////////////////////////

    /**
     * Sets SequencePlayer time when triggered, time is given to the action by an APIArgument coming from the trigger.
     * Trigger must have an float argument with name as property set by 'mFloatArgName'
     */
    class NAPAPI SequenceSetTimeAction : public TriggerAction
    {
    RTTI_ENABLE(TriggerAction)
    public:
        ResourcePtr<SequencePlayer> mPlayer = nullptr; ///< Property: "Player" required ResourcePtr to SequencePlayer
        std::string mFloatArgName = "SequenceTime"; ///< Property: "FloatArgName" the APIValue name to try to extract
    protected:
        /**
         * Executes action
         * @param event the API event create by the trigger
         * @param errorState can contain any error on execution
         * @return true on success
         */
        bool onExecute(const APIEventPtr& event, utility::ErrorState &errorState) override;
    };

    //////////////////////////////////////////////////////////////////////////
    // SequenceSetPlaybackSpeedAction
    //////////////////////////////////////////////////////////////////////////

    /**
     * Sets SequencePlayer playbackspeed when triggered, time is given to the action by an APIArgument coming from the trigger.
     * Trigger must have an float argument with name as property set by 'mFloatArgName'
     */
    class NAPAPI SequenceSetPlaybackSpeedAction : public TriggerAction
    {
    RTTI_ENABLE(TriggerAction)
    public:
        ResourcePtr<SequencePlayer> mPlayer = nullptr; ///< Property: "Player" required ResourcePtr to SequencePlayer
        std::string mFloatArgName = "PlaybackSpeed"; ///< Property: "FloatArgName" the APIValue name to try to extract
    protected:
        /**
         * Executes action
         * @param event the API event create by the trigger
         * @param errorState can contain any error on execution
         * @return true on success
         */
        bool onExecute(const APIEventPtr& event, utility::ErrorState &errorState) override;
    };

    //////////////////////////////////////////////////////////////////////////
    // SequenceLoadAction
    //////////////////////////////////////////////////////////////////////////

    /**
     * Loads sequence with value found in API argument with name that corresponds with 'mStringArgName'
     */
    class NAPAPI SequenceLoadAction : public TriggerAction
    {
    RTTI_ENABLE(TriggerAction)
    public:
        ResourcePtr<SequencePlayer> mPlayer = nullptr; ///< Property: "Player" required ResourcePtr to SequencePlayer
        std::string mArgumentName = "Sequence"; ///< Property: "ArgumentName" the argument name of the file to load
    protected:
        /**
         * Executes action
         * @param event the API event create by the trigger
         * @param errorState can contain any error on execution
         * @return true on success
         */
        bool onExecute(const APIEventPtr& event, utility::ErrorState &errorState) override;
    };

}