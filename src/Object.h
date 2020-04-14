#ifndef OBJECT_H
#define OBJECT_H

#include "Image.h"
#include <string>

enum ObjectType {weapon,armor,other};
class Object
{
public:
    std::string m_nameEquipment;
    ObjectType m_type;
    unsigned int m_index;
    Rectangle m_pos;
    Image m_image;
    bool m_isLooted;
    int m_value;
    bool m_destroyed;
    bool m_dropped;
};



#endif
