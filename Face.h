#pragma once
#include "Kinematic.h"
#include "Align.h"

/*
	[Description]
	| The Face behavior is a small extra layer to Align steering and is responsible to calculate a desired orientation towards a explicit target.
	| By modyfing the Align's targeted orientation, we can simply re-use the Align behavior to recieve rotation towards a target of choice.
*/

class Face : public Align
{

public:
	Face(Kinematic& aCharacter) : Align(aCharacter){}
	~Face() {}

	inline SteeringOutput GetSteering(float aTimeDelta)
	{
		SteeringOutput result;

		Vector3f direction = (faceTarget - character.transform.GetPosition());
		direction.y = 0.0f;
		direction.Normalize();

		if (direction.Length() == 0) {
			return result;
		}

		Align::targetOrientation = atan2f(direction.x, direction.z);

		return Align::GetSteering(aTimeDelta);
	}

	inline void SetTarget(const Vector3f& aTarget) { faceTarget = { aTarget.x, 0.0f, aTarget.z}; }
	inline void SetTarget(const Vector2f& aTarget) { faceTarget = { aTarget.x, 0.0f, aTarget.y}; }

protected:
	Vector3f faceTarget;
};