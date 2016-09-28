/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c DBusLastoreUpdater -p dbuslastoreupdater com.deepin.lastore.Updater.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUSLASTOREUPDATER_H_1446193836
#define DBUSLASTOREUPDATER_H_1446193836

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

#include "dbus/mirrorinfo.h"
#include "dbus/appupdateinfo.h"

/*
 * Proxy class for interface com.deepin.lastore.Updater
 */
class DBusLastoreUpdater: public QDBusAbstractInterface
{
    Q_OBJECT

    Q_SLOT void __propertyChanged__(const QDBusMessage &msg)
    {
        QList<QVariant> arguments = msg.arguments();
        if (3 != arguments.count()) {
            return;
        }
        QString interfaceName = msg.arguments().at(0).toString();
        if (interfaceName != "com.deepin.lastore.Updater") {
            return;
        }
        QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
        QStringList keys = changedProps.keys();
        foreach(const QString & prop, keys) {
            const QMetaObject *self = metaObject();
            for (int i = self->propertyOffset(); i < self->propertyCount(); ++i) {
                QMetaProperty p = self->property(i);
                if (p.name() == prop) {
                    Q_EMIT p.notifySignal().invoke(this);
                }
            }
        }
    }
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.lastore.Updater"; }

public:
    DBusLastoreUpdater(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~DBusLastoreUpdater();

    Q_PROPERTY(bool AutoCheckUpdates READ autoCheckUpdates NOTIFY AutoCheckUpdatesChanged)
    inline bool autoCheckUpdates() const
    { return qvariant_cast< bool >(property("AutoCheckUpdates")); }

    Q_PROPERTY(QString MirrorSource READ mirrorSource NOTIFY MirrorSourceChanged)
    inline QString mirrorSource() const
    { return qvariant_cast< QString >(property("MirrorSource")); }

    Q_PROPERTY(QString OfficialSource READ officialSource NOTIFY OfficialSourceChanged)
    inline QString officialSource() const
    { return qvariant_cast< QString >(property("OfficialSource")); }

    Q_PROPERTY(QStringList UpdatableApps READ updatableApps NOTIFY UpdatableAppsChanged)
    inline QStringList updatableApps() const
    { return qvariant_cast< QStringList >(property("UpdatableApps")); }

    Q_PROPERTY(QStringList UpdatablePackages READ updatablePackages NOTIFY UpdatablePackagesChanged)
    inline QStringList updatablePackages() const
    { return qvariant_cast< QStringList >(property("UpdatablePackages")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<AppUpdateInfoList> ApplicationUpdateInfos(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("ApplicationUpdateInfos"), argumentList);
    }

    inline QDBusPendingReply<QList<MirrorInfo>> ListMirrorSources(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("ListMirrorSources"), argumentList);
    }

    inline QDBusPendingReply<> SetAutoCheckUpdates(bool in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("SetAutoCheckUpdates"), argumentList);
    }

    inline QDBusPendingReply<> SetMirrorSource(const QString &in0)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(in0);
        return asyncCallWithArgumentList(QStringLiteral("SetMirrorSource"), argumentList);
    }

Q_SIGNALS: // SIGNALS
// begin property changed signals
    void AutoCheckUpdatesChanged();
    void MirrorSourceChanged();
    void OfficialSourceChanged();
    void UpdatableAppsChanged();
    void UpdatablePackagesChanged();
};

namespace org
{
namespace deepin
{
namespace lastore
{
typedef ::DBusLastoreUpdater Updater;
}
}
}
#endif