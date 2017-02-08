#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T22:44:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Urho3d-IDE
TEMPLATE = app

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Urho3D-1.6/build/lib/ -lUrho3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Urho3D-1.6/build/lib/ -lUrho3d

#Then these guys, every single one of them seems to be needed on Windows
LIBS += -LC:/Qt/Qt5.7.0/Tools/mingw530_32/i686-w64-mingw32/lib/ -lkernel32
LIBS += -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
LIBS += -ldbghelp -limm32 -lversion -lwinmm -lws2_32 -lopengl32

INCLUDEPATH += $$PWD/../Urho3D-1.6/build/include
DEPENDPATH += $$PWD/../Urho3D-1.6/build/include

INCLUDEPATH += $$PWD/../Urho3D-1.6/build/include/Urho3D/ThirdParty
DEPENDPATH += $$PWD/../Urho3D-1.6/build/include/Urho3D/ThirdParty

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Urho3D-1.6/build/lib/libUrho3.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Urho3D-1.6/build/lib/libUrho3d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Urho3D-1.6/build/lib/Urho3.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Urho3D-1.6/build/lib/Urho3d.lib

QMAKE_CXXFLAGS += -DURHO3D_STATIC_DEFINE
QMAKE_CXXFLAGS += -DWIN32
QMAKE_CXXFLAGS += -msse4.1

URHO3D_EVENT


SOURCES += main.cpp\
    Windows/mainwindow.cpp \
    Windows/loadingdialog.cpp \
    Windows/editorwindow.cpp \
    Windows/hierarchy.cpp \
    Windows/resourcebrowser.cpp \
    Windows/console.cpp \
    TransformHandle/basehandle.cpp \
    TransformHandle/runtimehandles.cpp \
    TransformHandle/Infrastructure/runtimetools.cpp \
    TransformHandle/positionhandle.cpp \
    TransformHandle/rotationhandle.cpp \
    TransformHandle/scalehandle.cpp

HEADERS  += Windows/mainwindow.h \
    Windows/loadingdialog.h \
    Windows/editorwindow.h \
    Windows/hierarchy.h \
    Windows/resourcebrowser.h \
    Windows/console.h \
    TransformHandle/basehandle.h \
    TransformHandle/runtimehandles.h \
    TransformHandle/Infrastructure/runtimetools.h \
    TransformHandle/positionhandle.h \
    TransformHandle/rotationhandle.h \
    TransformHandle/scalehandle.h

FORMS    += mainwindow.ui \
    loadingdialog.ui \
    editorwindow.ui \
    hierarchy.ui \
    resourcebrowser.ui \
    console.ui
