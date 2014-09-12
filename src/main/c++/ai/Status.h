#pragma once
#include <set>

enum BasicAction 
{
	WALKING, RUNNING
};

enum Action
{
	MOVING
};

enum Activity
{
	GATHER_FOOD
};

enum Intention
{
	FEED_ITSELF
};


//= = = = = = = = = = = = = = = = = = = = = = =//
//              LIST POSSIBILITIES             //
//- - - - - - - - - - - - - - - - - - - - - - -//

std::set<Activity> possibleActivitiesFor(Intention intention);
std::set<Action> possibleActionsFor(Activity activity);
std::set<BasicAction> possibleBasicActionsFor(Action action);


class Status
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	static Status* makeStatus(BasicAction basicAction, Action action,
		Activity activity, Intention intention)
	{
		std::set<Activity> activities = possibleActivitiesFor(intention);
		if (activities.find(activity) == activities.end()) {
			return nullptr;
		}

		std::set<Action> actions = possibleActionsFor(activity);
		if (actions.find(action) == actions.end()) {
			return nullptr;
		}

		std::set<BasicAction> basicActions = possibleBasicActionsFor(action);
		if (basicActions.find(basicAction) == basicActions.end()) {
			return nullptr;
		}

		return &Status(basicAction, action, activity, intention);
	}

	BasicAction basicAction;
	Action action;
	Activity activity;
	Intention intention;
private:
	// CONSTRUCTOR/DESCTRUCTOR
	Status(BasicAction, Action, Activity, Intention);
};