# Steering-Controller
C++ implementation of a Kinematic Steering controller using Arrive and Facing behavior as an example.

# Goal
The goal of this implementation is to simplify movement for entities thru an interface where 
users only have to set a move or facing target and the controller then handles all the necesarry movement to achiev that.

# Information
- Each header contains a short description.
- SharedKinematic is not necesarry but something I tend to use to modify movement variables for all entities of a certain type.
- This implementation does not cover flying movement.

# Example videos 
Unit using the steering controller with it's target set towards the chair outside the Navmesh. <br />
![](https://i.imgur.com/2sHe8FQ.gif)

Unit with it's height contrained to Navmesh showcasing how we follow the height of the terrain. <br />
![](https://i.imgur.com/jcVIVeq.gif)

