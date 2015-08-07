LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/AppDelegate.h \
../../Classes/DataUtil.cpp \
../../Classes/DataUtil.h \
../../Classes/FailedShadeLayer.cpp \
../../Classes/FailedShadeLayer.cpp~ \
../../Classes/FailedShadeLayer.h \
../../Classes/GameScene.cpp \
../../Classes/GameScene.cpp~ \
../../Classes/GameScene.h \
../../Classes/HelloWorldScene.cpp \
../../Classes/HelloWorldScene.h \
../../Classes/LevelData.cpp \
../../Classes/LevelData.h \
../../Classes/PauseLayer.cpp \
../../Classes/PauseLayer.h \
../../Classes/ResolvePicture.cpp \
../../Classes/ResolvePicture.h \
../../Classes/SelectLevel.cpp \
../../Classes/SelectLevel.h \
../../Classes/ShadeLayer.cpp \
../../Classes/ShadeLayer.h \
../../Classes/SmartRes.h \
../../Classes/sqlite3.c \
../../Classes/sqlite3.h \
../../Classes/sqlite3ext.h \
../../Classes/AlertLayer.cpp \
../../Classes/AlertLayer.h \
../../Classes/LogoScene.cpp \
../../Classes/LogoScene.h \
../../Classes/ShoppingMall.cpp \
../../classes/ShoppingMall.h \
../../Classes/RemindLayer.cpp \
../../classes/Single.cpp \
../../classes/LoadScene.cpp \
../../Classes/SmartRes.cpp \
../../Classes/SmartRes.h



LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
