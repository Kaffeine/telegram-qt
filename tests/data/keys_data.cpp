#include "keys_data.hpp"

#include <QTemporaryFile>
#include <QDebug>

//openssl genpkey -algorithm RSA -out private_key.pem -pkeyopt rsa_keygen_bits:2048
//openssl rsa -pubout -in private_key.pem -out public_key.pem
//openssl rsa -inform PEM -text -in private_key.pem

const QByteArray TestKeyData::keyModulus = QByteArray::fromHex(
            QByteArrayLiteral(
                "b8aac38a12080a4991508009606bcd40"
                "09c58038cc287bf55c302cdf899f924e"
                "89fe4fa56b2a5bb3dbff82a1db6e2399"
                "60fc2b4f2182142162b4e900c4bb353f"
                "0034d0a627d0db4ea3aed4c1e49c62da"
                "6dfd492ad384463ac49743ac01b86389"
                "88446938824396940788c2ab879e8af0"
                "3f67109c5e4b02fc6e3b814735fc51d6"
                "a9e4dc459411ee945f506768f8728fdd"
                "7996b04814cdceb8a7a31651b84901f0"
                "ea3052070da76ff5f6c113170a13048c"
                "78a8a2524575976929d6689a13f7233f"
                "5e806adddafe6ca2a53a25968e3416ae"
                "e6277be6d80279395b79540a0dff9908"
                "0e09f8fee764709482a5ab812127dce2"
                "932eb57747b1874a0b92d440c46be54b"
                ));

const QByteArray TestKeyData::keyExponent = QByteArray::fromHex(
            QByteArrayLiteral("010001"));

const QByteArray TestKeyData::keySecretExponent = QByteArray::fromHex(
            QByteArrayLiteral(
                "2a182ae89f419beeb7242d7b75b23d20"
                "3ad9fd67750a496f5dab519f4704cbda"
                "0154aa1d1ff790ddc7e94f82cbbd287a"
                "3f045c6ef6496b834cb7c66139771f25"
                "144bf5bfda559e982771a3e7eacfc72c"
                "d963a23913ec1402336bf3ae12da503e"
                "3a84b5a37ef61f2df125b8925720c9b5"
                "080edb57799b09bc36f87378a312b828"
                "9e831f208a439017cb97c57cabdf2bbb"
                "cd8aa2d5b0d9e05c6a44643eb5df763d"
                "735cb8ecf05030ccdcbee8bc4690b47f"
                "091b551d94aba4614eadc9e202b9fa16"
                "1cc0fe91b51b12c417379af5a4fd819f"
                "e8d6f551f8942be46ffdaf152d75fbea"
                "6b0e78dfeea55d67679976462e4329ce"
                "bccb46125414f5801abe7d1cb13d4251"));

const quint64 TestKeyData::keyFingerprint = 0xf0f8c01a578dfee0ull;

static QTemporaryFile *s_publicKeyPkcs1File = nullptr;
static QTemporaryFile *s_publicKeyPkcs8File = nullptr;
static QTemporaryFile *s_privateKeyFile = nullptr;

bool TestKeyData::copyFile(const QString &sourceFileName, QIODevice *output)
{
    QFile inputFile(sourceFileName);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qWarning() << Q_FUNC_INFO << "Unable to open file" << sourceFileName;
        return false;
    }
    if (output->write(inputFile.readAll()) != inputFile.size()) {
        qWarning() << Q_FUNC_INFO << "Unable to write to file" << sourceFileName;
        return false;
    }
    return true;
}

bool TestKeyData::initKeyFiles()
{
    Q_INIT_RESOURCE(keys_data);

    struct Pair {
        Pair(QTemporaryFile *&ptr, const char *n) : file(ptr), name(n) {}
        QTemporaryFile *&file;
        const char *name;
    };

    for (Pair entry : {
         Pair(s_publicKeyPkcs1File, "public_key_PKCS1"),
         Pair(s_publicKeyPkcs8File, "public_key_PKCS8"),
         Pair(s_privateKeyFile, "private_key") })
    {
        entry.file = new QTemporaryFile();
        entry.file->setFileTemplate(entry.file->fileTemplate() + QStringLiteral(".pem"));
        if (!entry.file->open()) {
            qWarning() << Q_FUNC_INFO << "Unable to create a temprorary file";
            return false;
        }
        if (!copyFile(QStringLiteral(":/data/keys/%1.pem").arg(QString::fromLatin1(entry.name)), entry.file)) {
            qWarning() << Q_FUNC_INFO << "Unable to copy file" << entry.name;
            return false;
        }
        entry.file->close();
    }
    if (!s_publicKeyPkcs1File || !s_publicKeyPkcs8File || !s_privateKeyFile) {
        return false;
    }
    return true;
}

bool TestKeyData::cleanupKeyFiles()
{
    delete s_publicKeyPkcs1File;
    delete s_publicKeyPkcs8File;
    delete s_privateKeyFile;
    return true;
}

QString TestKeyData::privateKeyFileName()
{
    return s_privateKeyFile->fileName();
}

QString TestKeyData::publicKeyPkcs1FileName()
{
    return s_publicKeyPkcs1File->fileName();
}

QString TestKeyData::publicKeyPkcs8FileName()
{
    return s_publicKeyPkcs8File->fileName();
}
