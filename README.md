# naptriggeraction

## Summary

The `naptriggeraction` module is designed to make NAP apps easily customizable and respond to different inputs and/or interfaces. 

For Example: A common scenario in a NAP app is that a sequence needs to be played/stopped/loaded using an OperationalCalendar, WebClient interface or using certain UDP commands. In turn, the sequencer can contain certain events that trigger other actions in time with the sequence being played.

To make sure these different configurations can be supported without touching the application code, the `naptriggeraction` module is useful. 

The aim of this module is to let the user or sysadmin of the application configure their own set of triggers and actions and tune the application to meet the conditions of the context the application is running in. 

Furthermore, the module is designed to be lightweight and it is encouraged to implement your own Triggers and Actions for specific needs of your module or project.

## Description
The `naptriggeraction` module is used to trigger actions based on a trigger. Triggers are resources that describe the conditions of the Trigger being hit. The TriggerHandlerComponent can handle one trigger and execute multiple actions when triggered.

Triggers can be given a list `TriggerValues` that will be used to create an `APIEvent` when the trigger is hit. This makes it possible for Triggers to pass on APIValues to actions.

The `Trigger` is than instantiated by a `TriggerHandlerComponent` that executes the actions set in the `TriggerHandlerComponent`.

Extend on `Trigger` and `TriggerInstance` to create your own triggers. Extend on `TriggerAction` to create your own actions.

Actions will always be triggered from the `TriggerHandlerComponent` during update on the main thread. Triggers can trigger from any thread, the `TriggerHandlerComponent` will make sure the actions will be executed from the main thread.

The module comes with some simple Triggers and TriggerActions out-of-the-box that you can use as examples. See the supplied demo application for their implementations.

### Triggers:
- ParameterButtonTrigger: A trigger that is triggered when a ParameterButton is pressed.
- ParameterDropDownTrigger: A trigger that is triggered when a ParameterDropDown is changed. Passes on selection and selected index in the create APIEvent.
- ConditionalTrigger: A templated trigger that is triggered when set condition is met. Links to a Parameter.
- UDPTrigger: A trigger that is triggered when a UDP message is received. 
- SequenceEventTrigger: A trigger that is triggered when a sequence event is received. Links to a SequencePlayer.
- CalendarEventTrigger: A trigger that is triggered when OperationalCalender when operational or not. Links to a OperationalCalender.

### TriggerActions:
- SetParameterAction: A trigger action that sets a parameter to a value. Links to a Parameter, extracts argument name from APIEvent passed by the trigger and sets parameter to the value.
- TriggerLogAction: A trigger that logs message to console.
- SequenceAction: A trigger action that executes an action to the SequencePlayer. Links to a SequencePlayer.
