#pragma once
#include "Kinematic.h"

/*
	[Description]
	| The Arrive behavior generates linear steering (velocity) towards a target position. 
	| As the character gets closer to the goal destination, it will also slow down, making the arrival smooth.
*/

class Arrive
{

public:
	Arrive(Kinematic& aCharacter) : character(aCharacter) {}
	~Arrive() {}
	inline SteeringOutput GetSteering()
	{
		SteeringOutput result;

		Vector3f characterPos = character.transform.GetPosition();
		Vector3f direction = (target - characterPos).GetNormalized();
		characterPos.y = 0.0f;

		float distance = (characterPos - finalTarget).Length();
		float targetSpeed = distance > slowRadius ? character.maxSpeed : character.maxSpeed * (distance / slowRadius);
		Vector3f targetVelocity = direction * targetSpeed;

		result.linear = targetVelocity - character.velocity;
		result.linear /= timeToTarget;

		if (result.linear.Length() > character.maxAcceleration) {
			result.linear.Normalize();
			result.linear *= character.maxAcceleration;
		}

		result.angular = 0;
		return result;
	}

	inline void SetFinalTarget(Vector2f& aTarget) { finalTarget = { aTarget.x, 0.0f, aTarget.y }; }
	inline void SetTarget(Vector2f& aTarget) { target = { aTarget.x, 0.0f, aTarget.y }; }
	inline void SetTarget(Vector3f& aTarget) { target = { aTarget.x, 0.0f, aTarget.z }; }

private:
	Kinematic& character;
	Vector3f target;
	Vector3f finalTarget;
	float targetRadius = 2.45f;
	float slowRadius = 1.8f;
	float timeToTarget = 0.15f;
};