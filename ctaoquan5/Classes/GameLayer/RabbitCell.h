//
//  RabbitCell.h
//  ctaoquan5
//
//  Created by lizhengyan on 15/7/1.
//
//

#ifndef __ctaoquan5__RabbitCell__
#define __ctaoquan5__RabbitCell__

#include <stdio.h>

USING_NS_CC;

class RabbitCell : public Node
{
public:
    virtual bool init();
    CREATE_FUNC(RabbitCell);
    
    void setRabbitAndSize(bool rabbit, float size);
    float getCellSize() { return m_cellSize; }
    
private:
    float m_cellSize;
    Sprite *m_rabbitNest;
    Label *m_rabbitLabel;
};

#endif /* defined(__ctaoquan5__RabbitCell__) */
