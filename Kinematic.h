#pragma once
#include "Engine/Source/Math/Transform.h"
#include "Engine/Source/Math/Vector2.h"
#include "Project/Source/Steering/SteeringOutput.h"
#include "SharedKinematic.h"

namespace KE_EDITOR
{
	class AIMovement;
}

/*
	[Description]
	| The Kinematic class is responsible to update the position and orientation of an object.
	| This class owns the movement properties of the object which are set thru the editor, for example max acceleration, speed, rotation, etc.
	| These properties are used by the steering behaviors in some degree to constrain the forces they can generate.
*/

class Kinematic
{
	// Steering behaviors are friend classed to keep their own interfaces more clean and avoid the need of getters and setters.
	friend class SteeringController;
	friend class Separation;
	friend class Seek;
	friend class Align;
	friend class Face;
	friend class Arrive;
	friend class KE_EDITOR::AIMovement;

public:
	Kinematic(Transform& aTransform, SharedKinematicData& aData) :
		transform(aTransform),
		maxRotation(aData.maxRotation),
		maxAcceleration(aData.maxAcceleration),
		maxAngularForce(aData.maxAngularForce),
		maxSpeed(aData.maxSpeed)
	{
		orientation = atan2f(transform.GetForward().x, transform.GetForward().z);
	}

	inline void Update(SteeringOutput& aSteering, float aTimeDelta)
	{
		// Apply our forces to the object's position and orientation.
		Vector3f& position = transform.GetPositionRef();
		position.x += velocity.x * aTimeDelta;
		position.z += velocity.z * aTimeDelta;
		orientation += rotation * aTimeDelta;
		transform.SetRotation(orientation);

		// Update our forces of movement.
		velocity.x += aSteering.linear.x * aTimeDelta;
		velocity.z += aSteering.linear.z * aTimeDelta;
		rotation += aSteering.angular * aTimeDelta;

		// Make sure our forces don't exceed max values.
		if (velocity.Length() > maxSpeed)
		{
			velocity.Normalize();
			velocity *= maxSpeed;
		}
	}

private:
	Transform& transform;
	Vector3f velocity = {};

	float& maxRotation;
	float& maxAcceleration;
	float& maxAngularForce;
	float& maxSpeed;

	float rotation = 0;
	float orientation = 0;
};