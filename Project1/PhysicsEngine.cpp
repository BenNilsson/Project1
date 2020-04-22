#include "PhysicsEngine.h"
#include "SphereCollider.h"

#include "RigidBody.h"

#include <iostream>

PhysicsEngine* PhysicsEngine::instance = 0;

void PhysicsEngine::AddRigidbody(RigidBody* rigidbody)
{
	mRigidbodies.push_back(rigidbody);
}

void PhysicsEngine::Simulate(float deltaTime)
{
	for (unsigned int i = 0; i < mRigidbodies.size(); i++)
	{
		mRigidbodies[i]->Integrate(deltaTime);
	}
}

void PhysicsEngine::HandleCollisions()
{
	for (unsigned int i = 0; i < mRigidbodies.size(); i++)
	{
		for (unsigned int j = i + 1; j < mRigidbodies.size(); j++)
		{
			if (mRigidbodies[i]->mCollider == nullptr) return;
			// Check whether stuff collides, then handle responses
			IntersectData intersectData = mRigidbodies[i]->GetCollider().Intersect(mRigidbodies[j]->GetCollider());

			if (intersectData.GetDoesIntersect())
			{
				glm::vec3 dir = glm::normalize(intersectData.GetDirection());
				glm::vec3 otherDir = glm::normalize(glm::reflect(mRigidbodies[i]->GetVelocity(), dir));

				mRigidbodies[i]->mVelocity = glm::reflect(mRigidbodies[i]->mVelocity, otherDir);
				mRigidbodies[j]->mVelocity = glm::reflect(mRigidbodies[j]->mVelocity, dir);
			}
		}
	}
}