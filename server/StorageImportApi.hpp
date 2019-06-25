#ifndef TELEGRAM_QT_SERVER_STORAGE_IMPORT_API_HPP
#define TELEGRAM_QT_SERVER_STORAGE_IMPORT_API_HPP

#include <QtGlobal>

class MessageData;

namespace Telegram {

namespace Server {

class Storage;

class StorageImportApi
{
public:
    explicit StorageImportApi(Storage *storage);

    void insertMessage(const MessageData &messageData);
    void setLastGlobalId(quint64 id);

protected:
    Storage *m_storage = nullptr;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_QT_SERVER_STORAGE_IMPORT_API_HPP
