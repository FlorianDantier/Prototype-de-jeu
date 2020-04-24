#include "Map.h"
#include <cassert>

Map::Map() : m_decorTab(nullptr), m_nbDecor(0)
{}

Map::Map(unsigned int nbDecor) : m_decorTab(nullptr)
{
    m_decorTab = new Rectangle[nbDecor];
    assert(m_decorTab != nullptr);
}

Map::~Map()
{
    delete[] m_decorTab;
    m_decorTab = nullptr;
}

void Map::setDecor(const unsigned int indice, const Rectangle &r)
{
    assert(indice >= 0 && indice < m_nbDecor);
    m_decorTab[indice] = r;
}

Rectangle &Map::getDecor(const unsigned int indice) const
{
    assert(indice >= 0 && indice < m_nbDecor);
    return m_decorTab[indice];
}
