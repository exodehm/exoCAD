#include "cursor.h"

Cursor::Cursor()
{
    Horizontal = new QGraphicsLineItem;
    Vertical = new QGraphicsLineItem;
}
QGraphicsLineItem* Cursor::LeeCursorHorizontal()
{
    return Horizontal;
}

QGraphicsLineItem* Cursor::LeeCursorVertical()
{
    return Vertical;
}
