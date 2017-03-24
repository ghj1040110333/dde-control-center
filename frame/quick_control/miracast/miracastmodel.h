#ifndef MIRACASTMODEL_H
#define MIRACASTMODEL_H

#include "miracastworker.h"

#include <QObject>

class MiracastModel : public QObject
{
    Q_OBJECT

    friend class MiracastWorker;

public:
    enum EventType
    {
        LinkManaged = 1,
        LinkUnmanaged,
        PeerConnected,
        PeerConnectFailed,
    };

    explicit MiracastModel(QObject *parent = 0);

    const QList<LinkInfo> links() const { return m_links; }

signals:
    void linkAdded(const LinkInfo &link) const;
    void linkRemoved(const QDBusObjectPath &path) const;
    void peerAdded(const PeerInfo &peer) const;
    void peerRemoved(const PeerInfo &peer) const;
    void requestLinkScanning(const QDBusObjectPath &path, const bool scanning) const;

private:
    void addPeer(const PeerInfo &peer);
    void addLink(const LinkInfo &link);
    void removeLink(const QDBusObjectPath &path);
    void removePeer(const QString &peerInfo);
    void setLinks(const QList<LinkInfo> &links);
    void onPathAdded(const QDBusObjectPath &path, const QString &info);
    void onPathRemoved(const QDBusObjectPath &path, const QString &info);
    void onMiracastEvent(const uchar type, const QDBusObjectPath &path);

    LinkInfo &linkByPath(const QDBusObjectPath &path);

private:
    QList<LinkInfo> m_links;
};

#endif // MIRACASTMODEL_H
