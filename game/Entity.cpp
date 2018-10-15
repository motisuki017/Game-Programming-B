#include "Entity.h"

Entity::Entity()
{
    parent = nullptr;
    localTransform = glm::mat4(1.0f);
}

Entity::~Entity()
{
}

void Entity::SetOwner(const Game* game)
{
    owner = game;
}

Entity* Entity::Parent()
{
    return parent;
}

int Entity::NumChildren() const
{
    return static_cast<int>(children.size());
}

Entity* Entity::Child(int id)
{
    return children[id];
}

void Entity::AddChild(Entity* c)
{
    c->parent = this;
    children.push_back(c);
}

bool Entity::Init()
{
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        if (!(*it)->Init())
        {
            return false;
        }
    }
    return true;
}

void Entity::Update(const GameTime& time)
{
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        (*it)->Update(time);
    }
}

void Entity::Render()
{
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        (*it)->Render();
    }
}

void Entity::Release()
{
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        (*it)->Release();
    }
}

glm::mat4 Entity::LocalTransform() const
{
    return localTransform;
}

void Entity::SetLocalTransform(const glm::mat4& m)
{
    localTransform = m;
}

glm::mat4 Entity::WorldTransform() const
{
    if (parent == nullptr)
    {
        return localTransform;
    }
    return localTransform * parent->WorldTransform();
}
