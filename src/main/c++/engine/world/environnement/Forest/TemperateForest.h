#pragma once
#include "Forest.h"

class TemperateForest : public Forest
{
public:
	virtual char character() const
	{
		return 'f';
	}
};