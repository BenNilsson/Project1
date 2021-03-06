#pragma once

#include "Collider.h"
#include "SphereCollider.h"
#include "PhysicsEngine.h"

class GameObject;

class RigidBody : GameComponent
{
public:
	RigidBody(const glm::vec3& velocity) :
		mVelocity(velocity) 
	{
		
	}

	~RigidBody();

	RigidBody(const RigidBody& other);
	
	void Update(float deltaTime);

	void Integrate(float deltaTime);

	void OnCollision(RigidBody& other);

	inline const glm::vec3 GetPosition() const { return mPosition; }
	inline const glm::vec3 GetOldPos() const { return mOldPosition; }
	inline const glm::vec3 GetRotation() const { return mRotation; }
	inline const glm::vec3 GetVelocity() const { return mVelocity; }

	inline const Collider& GetCollider()
	{
		glm::vec3 difference = mPosition - mOldPosition;
		mOldPosition = mPosition;
		mCollider->Transform(difference);
		return *mCollider;
	}

	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mVelocity;
	float mMass = 1.0f;
	bool mEnableGravity = true;

	mutable Collider* mCollider;
private:
	GameObject* mParent;
	glm::vec3 mOldPosition;
};