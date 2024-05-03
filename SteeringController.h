#pragma once
#include <Engine/Source/Utility/Global.h>
#include <Engine/Source/Navigation/Pathfinder.h>
#include "Kinematic.h"
#include "Face.h"
#include "Separation.h"
#include "Arrive.h"

namespace KE_EDITOR
{
	class AIMovement;
}

/*
	[Description]
	| SteeringController handles the Movement of an entity thru steering behaviors and with help of the Pathfinder class to naviate thru the world.
	| It encapsulates all the movement calculations and a Enemy class for example can simply assign targets to this controller and it will handle the rest.
	| friend class AIMovement is used to allow the editor to access the kinematic data of the entity, for example max acceleration or rotation speed.
*/

class SteeringController
{
	friend class KE_EDITOR::AIMovement;

public:
	SteeringController(Transform& aTransform, SharedKinematicData& aData) : 
		myKinematic(aTransform, aData),
		myFace(this->myKinematic), 
		myArrive(this->myKinematic)
	{
	
	}

	inline const Vector3f& GetVelocity() const { return myKinematic.velocity; }
	inline void AssignPathfinder(KE::Pathfinder* aPathfinder) { myPathfinder = aPathfinder; }
	inline void ApplySteering(const float aTimeDelta);
	inline void UpdateSteering(const float aTimeDelta);
	inline void MoveTowards(const Vector3f& aTarget);
	inline void FaceTowards(const Vector3f& aTarget);
	inline void ContrainToGround(const bool aContrain) { myContrainToGround = aContrain; }
	inline void ClearLinearSteering() 
	{ 
		mySteeringOutput.linear = {}; 
		myKinematic.velocity = {}; 
	}

private:
	KE::Pathfinder* myPathfinder = nullptr;
	std::vector<Vector2f> myPath;
	SteeringOutput mySteeringOutput;
	Kinematic myKinematic;
	Arrive myArrive;
	Face myFace;
	bool myContrainToGround = true;
};

inline void SteeringController::UpdateSteering(const float aTimeDelta)
{
	SteeringOutput result;
	result += myArrive.GetSteering();
	result += myFace.GetSteering(aTimeDelta);

	mySteeringOutput = result;
}
inline void SteeringController::ApplySteering(const float aTimeDelta)
{
	myKinematic.Update(mySteeringOutput, aTimeDelta);

	// Set unit height position based on Navmesh triangle height.
	if (myContrainToGround)
	{
		Vector3f position = myKinematic.transform.GetPosition();
		position.y = myPathfinder->GetHeightByPos(position);
		myKinematic.transform.SetPosition(position);
	}
}

inline void SteeringController::MoveTowards(const Vector3f& aTarget)
{
	Vector3f position = myKinematic.transform.GetPosition();
	myPath = myPathfinder->FindPath_2D(position, aTarget);

	if (myPath.size() > 0) 
	{
		Vector2f nextWaypoint = myPath.back();
		Vector2f goalDestination = myPath.front();

		myFace.SetTarget(nextWaypoint);
		myArrive.SetTarget(nextWaypoint);
		myArrive.SetFinalTarget(goalDestination);
	}
}
inline void SteeringController::FaceTowards(const Vector3f& aTarget)
{
	myFace.SetTarget(aTarget);
}