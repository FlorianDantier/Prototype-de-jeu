#ifndef MAP_H
#define MAP_H

#include "Rectangle.h"

enum Decal
{
    TopRight = 0,
    TopLeft,
    BottomRight,
    BottomLeft
};

/**
 * @brief      This class describes a map.
 */
class Map
{
private:
    Rectangle* m_decorTab;
    unsigned int m_nbDecor;

    Rectangle *m_tabOutZones;
    unsigned int m_nbOutZone;

    void initMap1();
    void initMap2();
    void initInstance1();

public:
    /**
     * @brief      Constructs a new instance of map
     */
    Map();

    /**
     * @brief      Constructs a new instance of map
     *
     * @param[in]  nbDecor    The number of decor
     * @param[in]  nbOutZone  The number of out zone
     * @param[in]  map        The map
     */
    Map(const unsigned int nbDecor, unsigned int nbOutZone, unsigned int map);

    /**
     * @brief      Destroys the object.
     */
    ~Map();

    /**
     * @brief      Sets the decor.
     *
     * @param[in]  indice  The indice
     * @param[in]  r       The new value
     */
    void setDecor(const unsigned int indice, const Rectangle &r);

    /**
     * @brief      Sets the decor diago.
     *
     * @param[in]  start  The start
     * @param[in]  diago  The diago
     * @param[in]  d      The new value
     */
    void setDecorDiago(const unsigned int start, const Rectangle &diago,
                       const Decal & d);

    /**
     * @brief      Gets the decor.
     *
     * @param[in]  indice  The indice
     *
     * @return    the decor which is a reference to a rectangle
     */
    Rectangle &getDecor(const unsigned int indice) const;

    /**
     * @brief      Gets all decor.
     *
     * @return     All decor.
     */
    Rectangle *getAllDecor() const;

    /**
     * @brief      Sets the out zone.
     *
     * @param[in]  indice  The indice
     * @param[in]  r       The new value
     */
    void setOutZone(const unsigned int indice, const Rectangle & r);

    /**
     * @brief      Gets the out zone.
     *
     * @param[in]  indice  The indice
     *
     * @return     The out zone.
     */
    Rectangle& getOutZone(unsigned int indice) const;


    /**
     * @brief      Determines if in out zone.
     *
     * @param[in]  r       { parameter_description }
     * @param[in]  indice  The indice
     *
     * @return     True if in out zone, False otherwise.
     */
    bool isInOutZone(const Rectangle & r, unsigned int indice);

    /**
     * @brief      Gets the number of decor.
     *
     * @return     The number of decor.
     */
    unsigned int getNbDecor() const;

};

#endif // MAP_H
