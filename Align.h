#pragma once
#include "Kinematic.h"

/*
	[Description]
	| The Align behavior is responsible for outputting rotation force towards our target orientation.
	| Ultimately, it is used to make the character face a direction based on target orientation.
*/

class Align
{

public:
	Align(Kinematic& aCharacter) : character(aCharacter)
	{
		targetOrientation = character.orientation;
	}
	~Align() {}
	inline SteeringOutput GetSteering(float aTimeDelta)
	{
		SteeringOutput result;

		float rotation = targetOrientation - character.orientation;
		rotation = MapToRange(rotation);

		float rotationSize = abs(rotation);
		if (rotationSize < targetRadius) 
		{
			character.rotation = 0.0f;
			return result;
		}

		float targetRotation = rotationSize > slowRadius ? character.maxRotation : character.maxRotation * (rotationSize / slowRadius);
		targetRotation *= rotation / rotationSize;

		result.angular = targetRotation - character.rotation;
		result.angular /= timeToTarget * aTimeDelta;

		float angularAcceleration = abs(result.angular);

		if (angularAcceleration > character.maxAngularForce)
		{
			result.angular /= angularAcceleration;
			result.angular *= character.maxAngularForce;
		}

		result.linear = { 0,0,0 };

		return result;
	}

	
	inline float MapToRange(float aRotation)
	{
		float PI = 3.14159265359f;

		while (aRotation <= PI) {
			aRotation += 2 * PI;
		}

		while (aRotation > PI) {
			aRotation -= 2 * PI;
		}

		return aRotation;
	}

protected:
	Kinematic& character;
	float targetOrientation = 0;
	float slowRadius = 0.8f; // Default ~45 degrees
	float targetRadius = 0.01745f; // Default 1 degree
	float timeToTarget = 0.1f;
};
