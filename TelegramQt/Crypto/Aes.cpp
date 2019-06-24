#include "Aes.hpp"

#include <openssl/aes.h>

#include <QLoggingCategory>

namespace Telegram {

namespace Crypto {

QByteArray aesDecrypt(const QByteArray &data, const AesKey &key)
{
    if (data.length() % AES_BLOCK_SIZE) {
        qCritical() << __func__ << "Data is not padded (size %" << AES_BLOCK_SIZE << "!= 0)";
        return QByteArray();
    }
    QByteArray result = data;
    QByteArray initVector = key.iv;
    AES_KEY dec_key;
    AES_set_decrypt_key((const uchar *) key.key.constData(), key.key.length() * 8, &dec_key);
    AES_ige_encrypt((const uchar *) data.constData(), (uchar *) result.data(), data.length(),
                    &dec_key, (uchar *) initVector.data(), AES_DECRYPT);
    return result;
}

QByteArray aesEncrypt(const QByteArray &data, const AesKey &key)
{
    if (data.length() % AES_BLOCK_SIZE) {
        qCritical() << __func__ << "Data is not padded "
                                   "(the size %" << AES_BLOCK_SIZE << " is not zero)";
        return QByteArray();
    }
    QByteArray result = data;
    QByteArray initVector = key.iv;
    AES_KEY enc_key;
    AES_set_encrypt_key((const uchar *) key.key.constData(), key.key.length() * 8, &enc_key);
    AES_ige_encrypt((const uchar *) data.constData(), (uchar *) result.data(), data.length(),
                    &enc_key, (uchar *) initVector.data(), AES_ENCRYPT);
    return result;
}

} // Crypto

} // Telegram
