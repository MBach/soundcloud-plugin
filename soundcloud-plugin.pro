QT      += sql widgets multimedia script webkit webkitwidgets

TARGET   = $$qtLibraryTarget(soundcloud-plugin)
TEMPLATE = lib

DEFINES += MIAM_PLUGIN

CONFIG  += c++11
# TODO: how to minimize hardcoded paths?
win32 {
    MiamPlayerBuildDirectory = C:\dev\Miam-Player-build\qt5.5.1\MiamPlayer
    CONFIG(debug, debug|release) {
	target.path = $$MiamPlayerBuildDirectory\debug\plugins
	LIBS += -Ldebug -lMiamCore
    }

    CONFIG(release, debug|release) {
	target.path = $$MiamPlayerBuildDirectory\release\plugins
	LIBS += -Lrelease -lMiamCore
    }
}
unix {
    MiamPlayerBuildDirectory = /home/mbach/Miam-Player-release
    target.path = $$MiamPlayerBuildDirectory/MiamPlayer/plugins
    LIBS += -L$$MiamPlayerBuildDirectory/MiamCore -lmiam-core
}

INSTALLS += target

HEADERS += abstractsearchdialog.h \
    autosaver.h \
    cookiejar.h \
    filehelper.h \
    miamcore_global.h \
    networkaccessmanager.h \
    settings.h \
    soundcloudplugin.h \
    webview.h \
    interfaces/basicplugin.h \
    interfaces/remotemediaplayerplugin.h \
    mediaplaylist.h \
    model/albumdao.h \
    model/artistdao.h \
    model/genericdao.h \
    model/playlistdao.h \
    model/selectedtracksmodel.h \
    model/sqldatabase.h \
    model/trackdao.h \
    model/yeardao.h \
    imediaplayer.h \
    soundcloudwebplayer.h \
    mediaplayer.h

SOURCES += webview.cpp \
    autosaver.cpp \
    networkaccessmanager.cpp \
    soundcloudplugin.cpp \
    cookiejar.cpp \
    soundcloudwebplayer.cpp

RESOURCES += resources.qrc

FORMS += config.ui

TRANSLATIONS += translations/SoundCloud-Plugin_en.ts \
    translations/SoundCloud-Plugin_fr.ts
