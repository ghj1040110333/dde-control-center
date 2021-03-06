
include(../../interfaces/interfaces.pri)

PLUGIN_NAME 	= notify

QT              += widgets dbus
TEMPLATE         = lib
CONFIG          += plugin c++11 link_pkgconfig
PKGCONFIG += dtkwidget dframeworkdbus
TARGET          = $$qtLibraryTarget($$PLUGIN_NAME)
DESTDIR          = $$_PRO_FILE_PWD_/../
DISTFILES       += $$PLUGIN_NAME.json

HEADERS += \
    notifyplugin.h \
    notifymanager.h \
    notifyviewer.h \
    notifybody.h \
    notifymodel.h \
    notifyview.h \
    notifydelegate.h \
    notifywidget.h

SOURCES += \
    notifyplugin.cpp \
    notifymanager.cpp \
    notifyviewer.cpp \
    notifybody.cpp \
    notifymodel.cpp \
    notifyview.cpp \
    notifydelegate.cpp \
    notifywidget.cpp

target.path = $${PREFIX}/lib/dde-control-center/plugins/

utils.path = $${PREFIX}/lib/dde-control-center/plugins/bin/
utils.files = notify-monitor

INSTALLS += target utils

RESOURCES += \
    images.qrc
