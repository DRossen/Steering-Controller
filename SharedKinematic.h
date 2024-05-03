#pragma once


/*
	[Description]
	| SharedKinematicData is used in the editor to modify movement properties for entity types. 
	| In this way we don't have to modify each individual entity's movement properties, we only modify entity types.
	| - For example, a small agile enemy-type may have a higher max speed than an large enemy type.
*/

struct SharedKinematicData
{
	float maxRotation = 5.0f;
	float maxAcceleration = 15.0f;
	float maxAngularForce = 25.0f;
	float maxSpeed = 5.0f;
};