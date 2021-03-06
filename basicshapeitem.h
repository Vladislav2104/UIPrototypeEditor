#ifndef RECTITEM_H
#define RECTITEM_H

#include "baseitem.h"

class BasicShapesItem : public BaseItem
{

public:
    enum ItemType {ITEM_RECTANGLE,ITEM_TOOL};
    BasicShapesItem(qreal x, qreal y, qreal w, qreal h,ItemType type,QGraphicsScene *scene, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setType();
    void setPixmap(QString path);
private:
    QPixmap mPixmap;
    ItemType mType;
};

#endif // RECTITEM_H
