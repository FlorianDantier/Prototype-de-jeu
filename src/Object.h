#ifndef OBJECT_H
#define OBJECT_H

#include "Image.h"
#include <string.h>

enum Rarity {common,rare,epic,unique};

class Object
{
    private:
    Image m_imObject;
    Rarity m_rarity;
    string m_name;
    bool m_looted;
    bool m_selected;

    public:
    Object();
    Object(const & Image imObject, Rarity rarity, const & string name);
    void setLooted(bool isLooted);
    void setSelected(bool isSelected);


}

#endif