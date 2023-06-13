TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        AssetMan.cpp \
        Game.cpp \
        GameOver.cpp \
        GameOverDuo.cpp \
        GamePlay.cpp \
        GamePlayDuo.cpp \
        MainMenu.cpp \
        Snake.cpp \
        Snake2.cpp \
        SoloDuo.cpp \
        main.cpp \
        stateman.cpp
INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
        CONFIG(debug, debug|release){
            LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
        } else {
            LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
        }
HEADERS += \
    AssetMan.h \
    Game.h \
    GameOver.h \
    GameOverDuo.h \
    GamePlay.h \
    GamePlayDuo.h \
    MainMenu.h \
    Snake.h \
    Snake2.h \
    SoloDuo.h \
    State.h \
    stateman.h
