# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = tdlib-test

CONFIG += sailfishapp
QT += concurrent dbus
PKGCONFIG +=  nemonotifications-qt5
SOURCES += src/tdlib-test.cpp \
    TdClientWrapper.cpp \
    src/ReceiveObject.cpp \
    src/ParserObject.cpp
CONFIG += c++11
CONFIG (debug, debug|release) {
        OBJECTS_DIR = build/debug
} else {
        OBJECTS_DIR = build/release
}
MOC_DIR = build/mocs

INCLUDEPATH += ./td
LIBS += -L$$OUT_PWD/tdlib -ltdjson

DISTFILES += qml/tdlib-test.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/tdlib-test.changes.in \
    rpm/tdlib-test.changes.run.in \
    rpm/tdlib-test.spec \
    rpm/tdlib-test.yaml \
    translations/*.ts \
    tdlib-test.desktop \
    rpm/tdlib-test.spec

SAILFISHAPP_ICONS = 86x86 108x108 128x128

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n


# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/tdlib-test-de.ts

HEADERS += \
    TdClientWrapper.hpp \
    src/ReceiveObject.hpp \
    src/ParserObject.hpp


RESOURCES += \
    resources.qrc
