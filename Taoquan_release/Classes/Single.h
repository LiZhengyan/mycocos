

#ifndef __SINGLE__
#define __SINGLE__
#include "cocos2d.h"
class Single:public cocos2d::Node
{
public:
	static Single*_instance;

	static Single*getInstance();
	void updateTime(float dt);
    void stop();
    
    void getLocalTime();
	Single();
	~Single();
    int get_minute(){
        
        return _minute;
    };
    
    int get_energy(){
        
        return _energy;
    };
    
    int get_second(){
        
        return _second;
    };
    int getLocalMinute(){
       
        return _localminute;
    };
    int getLocalHour(){
        return _localHour;
    };
    int getLocalMonth(){
        
        return _localMonth;
    };
    int getLocalDay(){
        return _localDay;
    };
private:
    int _energy;
	int _minute=10;//体力
	int _second=60;//时间
    int _localMonth;
    int _localDay;
    int _localHour;
    int _localminute;
    
};
#endif