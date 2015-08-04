//
//  ScrollLabel.cpp
//  Test
//
//  Created by mzy1992 on 13-11-30.
//
//

#include "ScrollLabel.h"

bool ScrollLabel::init(){
    
    visibleNode=Node::create();
    this->addChild(visibleNode);
    /*创建十个标签，数字0-9 */
    for(int i=0;i<10;i++){
        char str[2];
        str[0]='0'+i;
        str[1]='\0';

        Label * single=Label::create();
        single->setSystemFontSize(20.0);
        single->setColor(Color3B(0,0,0));//设置标签字体颜色
        single->setTag(i);
        single->setString(str);
        single->setAnchorPoint(Point(0, 0));//将锚点设为0，0便于设置坐标
        single->setPosition(Point(0, 20 *i));
        visibleNode->addChild(single);
        labels.push_back(single);      //将标签存入数组中
    }
    return true;
}

void ScrollLabel::setNumber(int var,bool up =true){
    
    this->stopAllActions();
    /*获取到要移动到的label的坐标*/
    Label * label=labels[var];
    Point moveToPosition =Point(visibleNode->getPositionX(),-(label->getPositionY()));
    /*创建一个动作，移动到该label的位置*/
    MoveTo * moveAction =MoveTo::create(5, moveToPosition);
    
    visibleNode->runAction(moveAction);
}

void ScrollLabel::visit(Renderer* renderer, const kmMat4 &parentTransform, bool parentTransformUpdated){
    
    
    _beforeVisitCmdScissor.init(_globalZOrder);
    _beforeVisitCmdScissor.func = CC_CALLBACK_0(ScrollLabel::onBeforeVisitScissor, this);
    renderer->addCommand(&_beforeVisitCmdScissor);
    
    Node::visit(renderer, parentTransform, parentTransformUpdated);
    
    _afterVisitCmdScissor.init(_globalZOrder);
    _afterVisitCmdScissor.func = CC_CALLBACK_0(ScrollLabel::onAfterVisitScissor, this);
    renderer->addCommand(&_afterVisitCmdScissor);
}

void ScrollLabel::onBeforeVisitScissor()
{
    Point  pos=Point(0, 0);
    pos=visibleNode->getParent()->convertToWorldSpace(pos);
    Rect clippingRect =Rect(pos.x, pos.y, 20, 20);
    glEnable(GL_SCISSOR_TEST);
    auto glview = Director::getInstance()->getOpenGLView();
    glview->setScissorInPoints(clippingRect.origin.x, clippingRect.origin.y, clippingRect.size.width, clippingRect.size.height);
}

void ScrollLabel::onAfterVisitScissor()
{
    glDisable(GL_SCISSOR_TEST);
}

