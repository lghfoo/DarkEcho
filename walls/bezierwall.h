#ifndef BEZIERWALL_H
#define BEZIERWALL_H
#include"wall.h"

class BezierWall :public Wall
{
public:
    virtual bool collideWith(const QPointF& p1, const QPointF& p2,
        QPointF& collidePoint);//ŒûWall.h
    virtual void tangentialEquation(const QPointF& point, double& A, double& B, double& C);//ŒûWall.h
    void setBezier(const QPointF& _p1, const QPointF& _p2, const QPointF& _p3);//³õÊŒ»¯±ŽÈû¶ûÇúÏß
private:
    QPointF p1;//ÆðÊŒµã
    QPointF p2;//ÖÐŒäµã
    QPointF p3;//œáÊøµã
/*œ«p1,p2,p3È·¶šµÄ±ŽÈû¶ûÇúÏß²ÎÊý·œ³Ì»¯ŒòÎªÈçÏÂÐÎÊœ£º
X=aX*t*t+bX*t+cX;
Y=aY*t*t+bY*t+cY;
ÒÔ±ãÓÚÅö×²Ê±µÄŒÆËã*/
    double aX;//²ÎÊý·œ³ÌÖÐŸö¶šXµÄtµÄ¶þŽÎÏîÏµÊý
    double bX;//²ÎÊý·œ³ÌÖÐŸö¶šXµÄtµÄÒ»ŽÎÏîÏµÊý
    double cX;//²ÎÊý·œ³ÌÖÐŸö¶šXµÄtµÄ³£ÊýÏîÏµÊý
    double aY;//²ÎÊý·œ³ÌÖÐŸö¶šYµÄtµÄ¶þŽÎÏîÏµÊý
    double bY;//²ÎÊý·œ³ÌÖÐŸö¶šYµÄtµÄÒ»ŽÎÏîÏµÊý
    double cY;//²ÎÊý·œ³ÌÖÐŸö¶šYµÄtµÄ³£ÊýÏîÏµÊý
    double getXVal(const double& _t);//œ«_tŽúÈë·œ³ÌµÃµœµÄX
    double getYVal(const double& _t);//œ«_tŽúÈë·œ³ÌµÃµœµÄY
};

#endif
