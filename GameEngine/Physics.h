#pragma once
#include <btBulletDynamicsCommon.h>
#include "Transform.h"

class RigidBody;

class Physics
{
private:
	static Physics* m_instance;
	btConstraintSolver* m_solver = new btSequentialImpulseConstraintSolver();
	btCollisionConfiguration* m_collisionConfig = new btDefaultCollisionConfiguration();
	btDispatcher* m_dispatcher = new btCollisionDispatcher(m_collisionConfig);
	btBroadphaseInterface* m_broadphase = new btDbvtBroadphase();
	btDynamicsWorld* m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfig);

	std::vector<std::shared_ptr<RigidBody>> m_rbodies;
	Physics();
	void Init();

	std::unordered_map<btRigidBody*, std::shared_ptr<RigidBody>> m_rbodiesMap;
	~Physics();

public:
	static Physics* GetInstance();
	inline btDynamicsWorld* GetWorld() {
		return GetInstance()->m_world;
	};

	static void PhysicsTickCallBack(btDynamicsWorld* world, btScalar timeStep);
	void AddRigidbody(std::shared_ptr<RigidBody> r);
	void PreUpdate();
	void Update(float deltaTime);
	void Quit();

	static btTransform ConvertTransformToBtTransform(Transform t);
};