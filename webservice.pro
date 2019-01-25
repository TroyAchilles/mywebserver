TEMPLATE = app
#CONFIG += console c++11
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = webservice

QMAKE_CXXFLAGS += --std=c++11
target.path = /usr/local/iDM
INSTALLS = target

SOURCES += \
    base/Image.cpp \
    base/Socket.cpp \
    base/ImageIO.cpp \
    base/FBDevice.cpp \
    base/ImageIOhandler.cpp \
    base/IBmpHandler.cpp \
    base/IXpmHandler.cpp \
    request/GETRequest.cpp \
    request/Request.cpp \
    response/Response.cpp \
    response/ResponseOperator.cpp \
    response/ResponseOptDynamic.cpp \
    response/ResponseOptStatic.cpp \
    main.cpp \
    websrc/webservice.cpp

HEADERS += \
    base/Socket.h \
    base/Image.h \
    base/Debug.h \
    base/ImageIO.h \
    base/FBDevice.h \
    base/Imagedefine.h \
    base/factory.h \
    base/ImageIOhandler.h \
    base/IBmpHandler.h \
    base/IXpmHandler.h \
    base/Debug.h \
    base/factory.h \
    request/GETRequest.h \
    request/Request.h \
    base/Debug.h \
    base/factory.h \
    response/Response.h \
    response/ResponseOperator.h \
    response/ResponseOptDynamic.h \
    response/ResponseOptStatic.h \
    base/Exception.h \
    websrc/webservice.h

INCLUDEPATH += 							\
    base 							\
    response 							\
    request 							\
    websrc 							\
