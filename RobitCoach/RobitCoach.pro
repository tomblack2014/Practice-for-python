#-------------------------------------------------
#
# Project created by QtCreator 2015-03-13T12:38:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RobitCoach
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    DataLayer/DataLayer.cpp \
    DataLayer/UDPDataHandling.cpp \
    DataLayer/UDPserver.cpp \
    WidgetsPlus/FieldMap.cpp \
    Ref/TCPRefClient.cpp \
    Stra/BehaviorTree/BehaviorTreeLoader.cpp \
    Stra/BehaviorTree/CustomData.cpp \
    Stra/BehaviorTree/NodeFactory.cpp \
    Stra/BehaviorTree/Nodes.cpp \
    Stra/Common/Calculation.cpp \
    Stra/Common/EventManager.cpp \
    Stra/Common/INIFile.cpp \
    Stra/Common/INIReader.cpp \
    Stra/Common/StateMachine.cpp \
    Stra/Common/Timer.cpp \
    Stra/tinyxml/tinystr.cpp \
    Stra/tinyxml/tinyxml.cpp \
    Stra/tinyxml/tinyxmlerror.cpp \
    Stra/tinyxml/tinyxmlparser.cpp

HEADERS  += MainWindow.h \
    DataLayer/DataLayer.h \
    DataLayer/UDPDataHandling.h \
    DataLayer/UDPserver.h \
    WidgetsPlus/FieldMap.h \
    Ref/TCPRefClient.h \
    Stra/BehaviorTree/CustomNodes/AntiStart.h \
    Stra/BehaviorTree/CustomNodes/Attack.h \
    Stra/BehaviorTree/CustomNodes/Auto.h \
    Stra/BehaviorTree/CustomNodes/Defend.h \
    Stra/BehaviorTree/CustomNodes/EvaluatorForKick.h \
    Stra/BehaviorTree/CustomNodes/Kick.h \
    Stra/BehaviorTree/CustomNodes/Pass.h \
    Stra/BehaviorTree/CustomNodes/StartPass.h \
    Stra/BehaviorTree/AnyDataRef.h \
    Stra/BehaviorTree/BehaviorTree.h \
    Stra/BehaviorTree/BehaviorTreeLoader.h \
    Stra/BehaviorTree/CustomData.h \
    Stra/BehaviorTree/CustomNodes.h \
    Stra/BehaviorTree/NodeFactory.h \
    Stra/BehaviorTree/Nodes.h \
    Stra/Common/AbsFactory.h \
    Stra/Common/Calculation.h \
    Stra/Common/Common.h \
    Stra/Common/DataCollector.h \
    Stra/Common/Event.h \
    Stra/Common/EventListener.h \
    Stra/Common/EventManager.h \
    Stra/Common/INIFile.h \
    Stra/Common/INIReader.h \
    Stra/Common/RandNumGenerator.h \
    Stra/Common/Singleton.h \
    Stra/Common/State.h \
    Stra/Common/StateMachine.h \
    Stra/Common/Timer.h \
    Stra/Common/Vec2D.h \
    Stra/tinyxml/tinystr.h \
    Stra/tinyxml/tinyxml.h \
    Stra/BehaviorTree/CustomNodes/Stop.h

FORMS    += MainWindow.ui

RESOURCES += \
    CoachResource.qrc

DISTFILES += \
    Stra/BehaviorTree/BehaviorTree.vcxproj \
    Stra/BehaviorTree/BehaviorTree.vcxproj.filters \
    Stra/Common/Common.vcxproj \
    Stra/Common/Common.vcxproj.filters \
    Stra/tinyxml/tinyxml.vcxproj \
    Stra/tinyxml/tinyxml.vcxproj.filters \
    Stra/tinyxml/tinyxmlSTL.vcxproj \
    Stra/tinyxml/tinyxmlSTL.vcxproj.filters



