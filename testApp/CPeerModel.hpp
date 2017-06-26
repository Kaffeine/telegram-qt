#ifndef CPEERMODEL_HPP
#define CPEERMODEL_HPP

#include <QObject>
#include <QAbstractTableModel>
#include <QPixmap>

#include "TelegramNamespace.hpp"

class CPeerModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CPeerModel(QObject *parent = nullptr);

    virtual bool hasPeer(const Telegram::Peer peer) const = 0;
    virtual QString getName(const Telegram::Peer peer) const = 0;
    virtual QPixmap getPicture(const Telegram::Peer peer, const Telegram::PeerPictureSize size) const = 0;

signals:
    void nameChanged(const Telegram::Peer peer);
    void pictureChanged(const Telegram::Peer peer);

};

#endif // CPEERMODEL_HPP
