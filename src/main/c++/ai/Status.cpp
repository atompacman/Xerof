#include "Status.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Status::Status(BasicAction basicAction, Action action,
	Activity activity, Intention intention)
{
	this->basicAction = basicAction;
	this->action = action;
	this->activity = activity;
	this->intention = intention;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//              LIST POSSIBILITIES             //
//- - - - - - - - - - - - - - - - - - - - - - -//

std::set<Activity> possibleActivitiesFor(Intention intention)
{
	std::set<Activity> possibleActivities = std::set<Activity>();

	switch (intention) {
	case FEED_ITSELF:
		possibleActivities.insert(GATHER_FOOD);
		break;
	}

	return possibleActivities;
}

std::set<Action> possibleActionsFor(Activity activity)
{
	std::set<Action> possibleActions = std::set<Action>();

	switch (activity) {
	case GATHER_FOOD:
		possibleActions.insert(MOVING);
		break;
	}

	return possibleActions;
}

std::set<BasicAction> possibleBasicActionsFor(Action action)
{
	std::set<BasicAction> possibleBasicActions = std::set<BasicAction>();

	switch (action) {
	case GATHER_FOOD:
		possibleBasicActions.insert(WALKING);
		possibleBasicActions.insert(RUNNING);
		break;
	}

	return possibleBasicActions;
}