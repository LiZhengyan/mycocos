#include "Single.h"
#include "DataUtil.h"
USING_NS_CC;
Single* Single::_instance = nullptr;
Single* Single::getInstance()
{

	if (_instance==nullptr)
	{
		_instance = new Single();
	}
	return _instance;
    
}
Single::Single()
{

    Director::getInstance()->getScheduler()->schedule(schedule_selector(Single::updateTime), this, 1.0, false);
    
}

Single::~Single()
{
    unschedule(schedule_selector(Single::updateTime));
}

static int timeMin=2;
static int timeSec=60;

void Single::updateTime(float dt)
{
    timeSec--;
    if (timeSec==59) {
        timeMin--;
    }

    _minute=timeMin;
    _second=timeSec;
    
    if (timeMin==0&&timeSec==0) {
        //倒计时为0时，精力数加一
        char getUserSql[100];
        sprintf(getUserSql, "select * from Prop ");
        Value avm=DataUtil::getRow(getUserSql);
        int energyNumber=avm.asValueMap()["energy"].asInt();
        if (energyNumber==6) {
            DataUtil::updatePropData("energy", 6);
        }else{
            DataUtil::updatePropData("energy", energyNumber+1);
           
        }
        timeMin=2;
    }
    if (timeSec==0) {
        timeSec=60;
    }
}

void Single::getLocalTime()
{
    //通过时间戳获取本地时间
    time_t timep;
    struct timeval now;
    gettimeofday(&now, NULL);

    timep=now.tv_sec;
    
    struct tm * tm;
    tm=localtime(&timep);
    
    //int year=tm->tm_year+1900;
    _localMonth = tm->tm_mon + 1;
    _localDay = tm->tm_mday;
    _localHour=tm->tm_hour;
    _localminute=tm->tm_min;
    //int second=tm->tm_sec;

}

void Single::stop() {
    CC_SAFE_DELETE(_instance );
}