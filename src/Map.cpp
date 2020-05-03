#include "Map.h"
#include <cassert>

Map::Map() : m_decorTab(nullptr), m_nbDecor(0)
{}

Map::Map(unsigned int nbDecor, unsigned int nbOutZone ,unsigned int map)
    : m_decorTab(nullptr)
{
    assert(nbDecor > 0);
    assert(nbOutZone > 0);
    m_nbDecor = nbDecor;
    m_decorTab = new Rectangle[nbDecor];
    m_nbOutZone = nbOutZone;
    m_tabOutZones = new Rectangle[nbOutZone];
    assert(m_decorTab != nullptr);
    if(map == 0)
    {
        initMap1();
    }
    else if (map == 1)
    {
        initMap2();
    }
    else if (map == 2)
    {
        initInstance1();
    }

}
Map::~Map()
{
    delete[] m_decorTab;
    m_decorTab = nullptr;

    delete[] m_tabOutZones;
    m_tabOutZones = nullptr;
}

void Map::initMap1()
{
    Rectangle statue1 = Rectangle(504, 552, 48, 48);
    Rectangle statue2 = Rectangle(655, 550, 48, 48);

    Rectangle temple[3];
    temple[0] = Rectangle(553, 276, 99, 110);
    temple[1] = Rectangle(554, 276, 24, 224);
    temple[2] = Rectangle(628, 276, 24, 224);


    Rectangle mur[10];
    mur[0] = Rectangle(0, 758, 256, 27);
    mur[1] = Rectangle(300, 707, 136, 27);
    mur[2] = Rectangle(476, 657, 178, 27);
    mur[3] = Rectangle(723, 732, 77, 28);
    mur[4] = Rectangle(120, 550, 26, 83);
    mur[5] = Rectangle(105, 197, 40, 157);
    mur[6] = Rectangle(225, 0, 21, 103);
    mur[7] = Rectangle(0, 482, 78, 26);
    mur[8] = Rectangle(0, 434, 52, 15);
    mur[9] = Rectangle(0, 717, 52, 10);

    setDecor(3, statue1);
    setDecor(4, statue2);
    for(int i = 0; i < 3; i++)
    {
        setDecor(i, temple[i]);
    }
    for(int i = 0; i < 10; i++)
    {
        setDecor(i + 5, mur[i]);
    }

    Rectangle stone[2];
    stone[0] = Rectangle(727, 52, 73, 20);
    stone[1] = Rectangle(707, 0, 21, 51);


    setDecor(15, stone[0]);
    setDecor(16, stone[1]);
    setDecorDiago(17, Rectangle(52, 631, 96, 95), TopLeft);
    setDecorDiago(25, Rectangle(253, 706, 54, 50), BottomRight);
    setDecorDiago(33, Rectangle(425, 655, 57, 54), BottomRight);
    setDecorDiago(41, Rectangle(653, 655, 74, 75), BottomLeft);
    setDecorDiago(49, Rectangle(74, 479, 72, 69), BottomLeft);
    setDecorDiago(57, Rectangle(46, 351, 102, 100), TopLeft);
    setDecorDiago(65, Rectangle(142, 97, 107, 106), TopLeft);

    m_tabOutZones = new Rectangle[1];
    // On alloue un tableau car on peut avoir plusieur "zone de sortie" sur une map et donc on détruit l'objet comme un tableau
    m_tabOutZones[0] = Rectangle(588, 370, 32, 25);
}

void Map::initMap2()
{
    setDecor(0, Rectangle(108, 344, 84, 48));
    setDecor(1, Rectangle(0, 0, 72, 72));
    setDecor(2, Rectangle(301, 100, 48, 48));
    setDecor(3, Rectangle(351, 123, 48, 48));
    setDecor(4, Rectangle(401, 98, 48, 48));
    setDecor(5, Rectangle(53, 503, 44, 44));
    setDecor(6, Rectangle(0, 730, 211, 28));
    setDecor(7, Rectangle(119, 331, 61, 13));
    setDecor(8, Rectangle(236, 195, 80, 57));
    setDecor(9, Rectangle(236, 252, 41, 38));
    setDecor(10, Rectangle(277, 252, 19, 20));
    setDecor(11, Rectangle(246, 183, 68, 12));
    setDecor(12, Rectangle(104, 594, 17, 63));
    setDecor(13, Rectangle(246, 755, 112, 23));
    setDecor(14, Rectangle(402, 706, 176, 23));
    setDecor(15, Rectangle(591, 731, 209, 25));
    setDecor(16, Rectangle(727, 545, 73, 50));
    setDecor(17, Rectangle(683, 331, 27, 224));
    setDecor(18, Rectangle(631, 249, 23, 52));
    setDecor(19, Rectangle(502, 167, 97, 53));
    setDecor(20, Rectangle(388, 292, 31, 132));
    setDecor(21, Rectangle(328, 416, 47, 56));
    setDecor(22, Rectangle(656, 98, 20, 52));
    setDecor(23, Rectangle(706, 0, 20, 50));
    setDecorDiago(24, Rectangle(100, 656, 76, 71), TopRight);
    setDecorDiago(32, Rectangle(148, 650, 100, 100), BottomLeft);
    setDecorDiago(40, Rectangle(352, 702, 48, 50), BottomRight);
    setDecorDiago(48, Rectangle(575, 701, 22, 25), BottomLeft);
    setDecorDiago(56, Rectangle(677, 552, 47, 47), TopRight);
    setDecorDiago(64, Rectangle(625, 297, 62, 59), TopRight);
    setDecorDiago(72, Rectangle(593, 216, 45, 42), TopRight);
    setDecorDiago(80, Rectangle(421, 224, 79, 77), TopLeft);
    setDecorDiago(88, Rectangle(295, 406, 31, 68), TopRight);
    setDecorDiago(96, Rectangle(655, 49, 49, 47), BottomLeft);
}

void Map::initInstance1()
{
    setOutZone(0, Rectangle(382, 728, 37, 25));

    // Torches à l'entrée
    setDecor(0, Rectangle(318, 664, 27, 22));
    setDecor(1, Rectangle(318, 608, 27, 22));
    setDecor(2, Rectangle(318, 552, 27, 22));
    setDecor(3, Rectangle(457, 664, 27, 22));
    setDecor(4, Rectangle(457, 608, 27, 22));
    setDecor(5, Rectangle(457, 552, 27, 22));
    setDecor(58, Rectangle(318, 497, 27, 22));
    setDecor(59, Rectangle(457, 497, 27, 22));

    // Mur en contour en bas des escaliers
    setDecor(6, Rectangle(198, 527, 63, 222));
    setDecor(7, Rectangle(121, 527, 77, 51));
    setDecor(8, Rectangle(24, 253, 44, 216));
    setDecor(9, Rectangle(24, 206, 72, 58));
    setDecor(10, Rectangle(151, 218, 57, 47));
    setDecor(11, Rectangle(151, 81, 56, 36));
    setDecor(12, Rectangle(206, 81, 165, 58));
    setDecor(13, Rectangle(428, 81, 223, 56));
    setDecor(14, Rectangle(594, 137, 57, 127));
    setDecor(15, Rectangle(706, 206, 69, 56));
    setDecor(16, Rectangle(734, 262, 41, 220));
    setDecor(17, Rectangle(540, 526, 139, 76));
    setDecor(18, Rectangle(540, 602, 77, 172));
    setDecor(19, Rectangle(420, 720, 120, 19));
    setDecor(20, Rectangle(261, 720, 120, 19));

    // Mur en contour en haut des escaliers
    setDecor(21, Rectangle(0, 116, 27, 89));
    setDecor(22, Rectangle(108, 0, 266, 43));
    setDecor(23, Rectangle(428, 0, 266, 43));
    setDecor(24, Rectangle(774, 123, 27, 89));






    // Mur en diagonale
    setDecorDiago(25, Rectangle(65, 467, 58, 64), BottomLeft);
    setDecorDiago(33, Rectangle(24, 41, 98, 97), TopLeft);
    setDecorDiago(41, Rectangle(677, 41, 100, 97), TopRight);
    setDecorDiago(49, Rectangle(675, 470, 61, 58), BottomRight);

    // Porte qui s'ouvrira une fois le boss vaincu
    setDecor(57, Rectangle(372, 0, 59, 43));
    setOutZone(1, Rectangle(382, 12, 38, 23));
}

void Map::setDecor(const unsigned int indice, const Rectangle &r)
{
    assert(indice >= 0 && indice < m_nbDecor);
    m_decorTab[indice] = r;
}

void Map::setDecorDiago(const unsigned int start, const Rectangle & diago, const Decal & d)
{
    int decal = 10;
    Rectangle* diagoTab = nullptr;
    if(d == TopLeft || d == BottomRight)
    {
        diagoTab = diago.cutHeight();
        if(d == TopLeft)
        {
            for(unsigned int i = 0; i < 8; i++)
            {
                diagoTab[i].m_position += Vec2<int>(-decal, -decal);
            }
        }
        else if(d == BottomRight)
        {
            for(unsigned int i = 0; i < 8; i++)
            {
                diagoTab[i].m_position += Vec2<int>(decal, decal);
            }
        }

    }
    else if(d == TopRight || d == BottomLeft)
    {
        diagoTab = diago.cutHeightBis();
        if(d == TopRight)
        {
            for(unsigned int i = 0; i < 8; i++)
            {
                diagoTab[i].m_position += Vec2<int>(decal, -decal);
            }
        }
        else if(d == BottomLeft)
        {
            for(unsigned int i = 0; i < 8; i++)
            {
                diagoTab[i].m_position += Vec2<int>(-decal, decal);
            }
        }
    }

    for(unsigned int i = start; i < start + 8; i++)
    {
        setDecor(i, diagoTab[i - start]);
    }
    delete [] diagoTab;
}

Rectangle &Map::getDecor(const unsigned int indice) const
{
    assert(indice >= 0 && indice < m_nbDecor);
    return m_decorTab[indice];
}

Rectangle *Map::getAllDecor() const
{
    return m_decorTab;
}

void Map::setOutZone(const unsigned int indice, const Rectangle &r)
{
    assert(indice >= 0 && indice < m_nbOutZone && "Erreur dans setOutZone");
    m_tabOutZones[indice] = r;
}

Rectangle &Map::getOutZone(unsigned int indice) const
{
    assert(indice >= 0 && indice < m_nbOutZone && "Erreur dans setOutZone");
    return m_tabOutZones[indice];
}

bool Map::isInOutZone(const Rectangle &r, unsigned int indice)
{
    assert(indice >= 0 && indice < m_nbOutZone
           && "Indice trop grand/petit dans isOutZone de Map");
    return r.in(m_tabOutZones[indice]);
}

unsigned int Map::getNbDecor() const
{
    return m_nbDecor;
}
