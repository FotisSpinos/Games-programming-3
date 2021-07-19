#include "pch.h"
#include "Physics.h"
#include "Richedit.h"
#include "RigidBody.h"


Physics* Physics::m_instance = nullptr;


Physics::Physics()
{
	Init();
}

void Physics::Init()
{
	m_world->setGravity(btVector3(0, -9.8, 0));
}

Physics::~Physics()
{
	delete m_instance;
}

void Physics::PhysicsTickCallBack(btDynamicsWorld* world, btScalar timeStep)
{
	btDispatcher* dispatcher = world->getDispatcher();
	for (int i = 0; i < dispatcher->getNumManifolds(); i++)
	{
		// Get the two Collided objects
		btPersistentManifold* contactManifold = dispatcher->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();

		// Cast btCollisionObject* to btRigidBody*
		btRigidBody* rb1 = (btRigidBody*)obA;
		btRigidBody* rb2 = (btRigidBody*)obB;

		// Call OnCollision Enter for the two collided rigid bodies
		GetInstance()->m_rbodiesMap[rb1]->CollisionOccured(GetInstance()->m_rbodiesMap[rb2]);
		GetInstance()->m_rbodiesMap[rb2]->CollisionOccured(GetInstance()->m_rbodiesMap[rb1]);
	}
}

void Physics::AddRigidbody(std::shared_ptr<RigidBody> r)
{
	m_rbodies.push_back(r);
	m_world->addRigidBody(r->Get());

	m_rbodiesMap[r->Get()] = r;
}

void Physics::PreUpdate()
{
	for (auto r : m_rbodies)
	{
		r->UpdateRigidBody();
	}
}
void Physics::Update(float deltaTime)
{
	PreUpdate();
	m_world->stepSimulation(deltaTime, 2);
	for (auto r : m_rbodies)
	{
		r->UpdateParent();
	}
}
void Physics::Quit()
{
	delete m_world;
	delete m_solver;
	delete m_broadphase;
	delete m_dispatcher;
	delete m_collisionConfig;
}

btTransform Physics::ConvertTransformToBtTransform(Transform t)
{
	glm::quat rot = t.GetRotation();
	glm::vec3 pos = t.GetPosition();

	return btTransform(btQuaternion(rot.x, rot.y, rot.z, rot.w),
		btVector3(pos.x, pos.y, pos.z));
}

Physics* Physics::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Physics();
	}
	return m_instance;
}