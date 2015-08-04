//
//  ScrollLabel.h
//  Test
//
//  Created by mzy1992 on 13-11-30.
//
//

#ifndef __Test__ScrollLabel__
#define __Test__ScrollLabel__

#include <iostream>
#include "cocos2d.h"
#include <stdlib.h>
USING_NS_CC;
class ScrollLabel :public Node{
    
public:
    virtual bool init();
    CREATE_FUNC(ScrollLabel);
    std::vector<Label *> labels;/* 用来保存label的数组 */
    Node * visibleNode;               /* 创建一个节点，将label添加到节点上，便于移动 */
    void setNumber(int var ,bool up);   /* 设置滚动到哪个数字的方法，参数var是滚动到的数字 */
    
    /*   -----  修改内容  ------- */
    /* 重载CCNode中的visit方法，此处不使用draw方法 */
    virtual void visit(Renderer* renderer, const kmMat4 &parentTransform, bool parentTransformUpdated);
    void onAfterVisitScissor();
    void onBeforeVisitScissor();
public:
    CustomCommand _beforeVisitCmdScissor;
    CustomCommand _afterVisitCmdScissor;
};
#endif /* defined(__Test__ScrollLabel__) */
