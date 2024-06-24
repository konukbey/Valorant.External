#pragma once
#include <cstdint>

class Team
{
public:
    short m_sTeam;
};

class Entity
{
public:
    Team* team;
};

class EntityList
{
public:
    int maxEntities;
};

class GameManager
{
public:
    EntitiesList* entitiesList;
    float gameTime;
};
