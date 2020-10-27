#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QSocketNotifier>
#include <QStandardPaths>

#include <TelegramQt/AccountStorage>
#include <TelegramQt/AppInformation>
#include <TelegramQt/AuthOperation>
#include <TelegramQt/Client>
#include <TelegramQt/ClientSettings>
#include <TelegramQt/ConnectionApi>
#include <TelegramQt/ContactList>
#include <TelegramQt/ContactsApi>
#include <TelegramQt/DataStorage>

#include "CompatibilityLayer.hpp"

#include <iostream>
#include <functional>

using namespace Telegram;
using namespace Telegram::Client;

class CliClient : public Telegram::Client::Client
{
    Q_OBJECT
public:
    CliClient();
    using InputHandler = std::function<void(const QString &)>;
    using LocalInputHandler = void (CliClient::*)(const QString &);

    void sendFile();
    void sendMessage();

    void startInteractiveMode();
    void showPrompt();
    void printStatus(const QString &input);
    void printHelp(const QString &input);
    PendingOperation *requestContactList();
    void printContactList();
    void quit(const QString &input);
    void connectToServer(const QString &input);
    void checkIn(const QString &input);
    void saveAccount(const QString &input);

    QString getServerAddress() const;
    void setServerAddress(const QString &address);

    void setRsaKeyFile(const QString &path);

    void addCommand(const char *command, InputHandler handler);
    void addCommand(const char *command, LocalInputHandler handler);

    void setAuthOperation(AuthOperation *authOperation);

private slots:
    void onStdinActivated();
    void onInteractiveInput(const QString &input);

    void onAuthPhoneRequired();
    void onAuthNameRequired();
    void onAuthCodeRequired();
    void onAuthPasswordRequired();
    void onAuthErrorOccurred(const QVariantHash &details);
    void onAuthFinished();

private:
    void print(const char *text);
    void print(const QString &text);
    void printLine(const char *text);
    void printLine(const QString &text);

    void enablePrompt();
    void disablePrompt();

    QTextStream &outputStream();
    QTextStream &inputStream();

    QVector<QString> m_commands;
    QHash<QString, InputHandler> m_commandsData;
    InputHandler m_defaultInputHandler = nullptr;
    InputHandler m_currentInputHandler = nullptr;
    QSocketNotifier *m_notifier = nullptr;
    AuthOperation *m_authOperation = nullptr;
    bool m_enablePrompt = false;
};

CliClient::CliClient()
    : Telegram::Client::Client()
{
    m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);

    connect(m_notifier, &QSocketNotifier::activated, this, &CliClient::onStdinActivated);

    addCommand("help", &CliClient::printHelp);
    addCommand("status", &CliClient::printStatus);
    addCommand("quit", &CliClient::quit);
    addCommand("connect", &CliClient::connectToServer);
    addCommand("check-in", &CliClient::checkIn);
    addCommand("save", &CliClient::saveAccount);
    addCommand("contact-list", [this](const QString &) {
        disablePrompt();
        requestContactList()->connectToFinished(this, &CliClient::showPrompt);
    });

    m_defaultInputHandler = [this](const QString &input) {
        onInteractiveInput(input);
    };
}

void CliClient::startInteractiveMode()
{
    printLine("Interactive mode is ON.");
    showPrompt();
}

void CliClient::showPrompt()
{
    enablePrompt();
    print("> ");

    m_currentInputHandler = m_defaultInputHandler;
}

QString connectionStatusToText(ConnectionApi::Status status)
{
    switch (status) {
    case ConnectionApi::StatusDisconnected:
        return QLatin1String("Disconnected");
    case ConnectionApi::StatusDisconnecting:
        return QLatin1String("Disconnecting");
    case ConnectionApi::StatusWaitForConnection:
        return QLatin1String("Waiting for connection");
    case ConnectionApi::StatusConnecting:
        return QLatin1String("Connecting");
    case ConnectionApi::StatusWaitForAuthentication:
        return QLatin1String("Waiting for authentication");
    case ConnectionApi::StatusConnected:
        return QLatin1String("Connected");
    case ConnectionApi::StatusReady:
        return QLatin1String("Ready");
    }
    return QLatin1Literal("Unknown");
}

void CliClient::printStatus(const QString &input)
{
    outputStream() << "Status: " << connectionStatusToText(connectionApi()->status()) << TELEGRAMQT_ENDL;
    outputStream() << "Server Configuration: " << getServerAddress() << TELEGRAMQT_ENDL;
    quint32 userId = dataStorage()->selfUserId();
    if (userId) {
        UserInfo userInfo;
        dataStorage()->getUserInfo(&userInfo, userId);
        outputStream() << "Self userId: " << userId << TELEGRAMQT_ENDL;
        outputStream() << "Phone number: " << userInfo.phone() << TELEGRAMQT_ENDL;
    } else {
        outputStream() << "Self userId: unknown" << TELEGRAMQT_ENDL;
    }
}

void CliClient::printHelp(const QString &input)
{
    printLine("Available commands:");
    for (const QString &command : m_commands) {
        outputStream() << command << TELEGRAMQT_ENDL;
    }
}

PendingOperation *CliClient::requestContactList()
{
    ContactList *list = contactsApi()->getContactList();
    PendingOperation *listReady = list->becomeReady();
    listReady->connectToFinished(this, &CliClient::printContactList);
    return listReady;
}

void CliClient::printContactList()
{
    ContactList *list = contactsApi()->getContactList();
    const QVector<quint32> contacts = list->list();
    UserInfo userInfo;
    for (const quint32 contactId : contacts) {
        if (!dataStorage()->getUserInfo(&userInfo, contactId)) {
            qWarning() << "Unable to get contact" << contactId;
            continue;
        }
        if (userInfo.phone().isEmpty()) {
            // Omit unknown contacts for now.
            continue;
        }
        outputStream() << userInfo.phone() << TELEGRAMQT_ENDL;
    }
}

void CliClient::quit(const QString &input)
{
    printLine("Good bye!");
    qApp->quit();
}

void CliClient::connectToServer(const QString &input)
{
    disablePrompt();
    QString address = input.section(QLatin1Char(' '), 1, 1);
    if (!address.isEmpty()) {
        setServerAddress(address);
    }

    outputStream() << "Connecting to " << getServerAddress() << TELEGRAMQT_ENDL;
    setAuthOperation(connectionApi()->startAuthentication());
}

void CliClient::checkIn(const QString &input)
{
    outputStream() << "Checking in..." << TELEGRAMQT_ENDL;
    setAuthOperation(connectionApi()->checkIn());
}

void CliClient::saveAccount(const QString &input)
{
    accountStorage()->saveData();
}

QString CliClient::getServerAddress() const
{
    const DcOption endpoint = accountStorage()->hasMinimalDataSet()
            ? accountStorage()->dcInfo()
            : settings()->serverConfiguration().constFirst();
    const QString address = QStringLiteral("%1:%2").arg(endpoint.address).arg(endpoint.port);
    return address;
}

void CliClient::setServerAddress(const QString &address)
{
    const QString addressPart = address.section(QLatin1Char(':'), 0, 0);
    const QString portPart = address.section(QLatin1Char(':'), 1, 1);
    settings()->setServerConfiguration({Telegram::DcOption(addressPart, portPart.toUShort())});

    setRsaKeyFile(QLatin1String("/tmp/TelegramTestServer.pem"));
}

void CliClient::setRsaKeyFile(const QString &path)
{
    const RsaKey key = RsaKey::fromFile(path);
    if (!key.isValid()) {
        qWarning() << "Ignored invalid key at" << path;
        return;
    }

    settings()->setServerRsaKey(key);
}

void CliClient::addCommand(const char *command, InputHandler handler)
{
    QString str = QString::fromLatin1(command);
    m_commands << str;
    m_commandsData.insert(str, handler);
}

void CliClient::addCommand(const char *command, LocalInputHandler handler)
{
    addCommand(command, [this, handler](const QString &input) {
        (this->*handler)(input);
    });
}

void CliClient::setAuthOperation(AuthOperation *authOperation)
{
    m_authOperation = authOperation;
    connect(m_authOperation, &AuthOperation::phoneNumberRequired,
            this, &CliClient::onAuthPhoneRequired);
    connect(m_authOperation, &AuthOperation::nameRequired,
            this, &CliClient::onAuthNameRequired);
    connect(m_authOperation, &AuthOperation::authCodeRequired,
            this, &CliClient::onAuthCodeRequired);
    connect(m_authOperation, &AuthOperation::passwordRequired,
            this, &CliClient::onAuthPasswordRequired);
    connect(m_authOperation, &AuthOperation::errorOccurred,
            this, &CliClient::onAuthErrorOccurred);
    connect(m_authOperation, &AuthOperation::finished,
            this, &CliClient::onAuthFinished);
}

void CliClient::onStdinActivated()
{
    QString inputLine = inputStream().readLine();
    if (inputStream().atEnd()) {
        printLine("Good bye!");
        qApp->quit();
    }

    if (!m_currentInputHandler) {
        printLine("Internal error: No input handler.");
        qApp->quit();
        return;
    }

    m_currentInputHandler(inputLine);
}

void CliClient::onInteractiveInput(const QString &input)
{
    if (!input.isEmpty()) {
        const QString command = input.section(QLatin1Char(' '), 0, 0);
        const InputHandler handler = m_commandsData.value(command, nullptr);
        if (handler == nullptr) {
            printLine("Unknown command");
        } else {
            handler(input);
        }
    }

    if (m_enablePrompt) {
        print("> ");
    }
}

void CliClient::onAuthPhoneRequired()
{
    printLine("Starting authorization...");
    print("Please enter the phone number: ");

    m_currentInputHandler = [this](const QString &input) {
        m_authOperation->submitPhoneNumber(input);
    };
}

void CliClient::onAuthNameRequired()
{
    print("Please enter first and last names: ");

    m_currentInputHandler = [this](const QString &input) {
        const QStringList names = input.split(QLatin1Char(' '));
        if (names.count() != 2) {
            printLine("The name must consist of two parts");
            print("Please enter first and last names: ");
            return;
        }
        m_authOperation->submitName(names.constFirst(), names.constLast());
    };
}

void CliClient::onAuthCodeRequired()
{
    if (m_authOperation->isRegistered()) {
        printLine("The phone number is already registered.");
    } else {
        printLine("The phone number is not registered.");
    }
    print("Please enter the auth code: ");

    m_currentInputHandler = [this](const QString &input) {
        m_authOperation->submitAuthCode(input);
    };
}

void CliClient::onAuthPasswordRequired()
{
    print("Please enter the account (cloud) password: ");

    m_currentInputHandler = [this](const QString &input) {
        m_authOperation->submitPassword(input);
    };
}

void CliClient::onAuthErrorOccurred(const QVariantHash &details)
{
    outputStream() << "Auth error details:" << TELEGRAMQT_ENDL;
    for (const QString &key : details.keys()) {
        outputStream() << "    " << key << ": " << details.value(key).toString() << TELEGRAMQT_ENDL;
    }
    outputStream() << TELEGRAMQT_ENDL;
}

void CliClient::onAuthFinished()
{
    if (m_authOperation->isSucceeded()) {
        printLine("Auth complete");
    } else {
        printLine("Auth failed");
    }

    showPrompt();

    m_authOperation->deleteLater();
    m_authOperation = nullptr;
}

void CliClient::print(const char *text)
{
    outputStream() << text << TELEGRAMQT_FLUSH;
}

void CliClient::print(const QString &text)
{
    outputStream() << text << TELEGRAMQT_FLUSH;
}

void CliClient::printLine(const char *text)
{
    outputStream() << text << TELEGRAMQT_ENDL;
}

void CliClient::printLine(const QString &text)
{
    outputStream() << text << TELEGRAMQT_ENDL;
}

void CliClient::enablePrompt()
{
    m_enablePrompt = true;
}

void CliClient::disablePrompt()
{
    m_enablePrompt = false;
}

QTextStream &CliClient::outputStream()
{
    static QTextStream stream(stdout);
    return stream;
}

QTextStream &CliClient::inputStream()
{
    static QTextStream stream(stdin);
    return stream;
}

void setupAppInfo(Client::AppInformation *appInfo)
{
    appInfo->setAppId(14617);
    appInfo->setAppHash(QLatin1String("e17ac360fd072f83d5d08db45ce9a121"));
    appInfo->setAppVersion(QLatin1String("0.1"));
    appInfo->setDeviceInfo(QLatin1String("pc"));
    appInfo->setOsInfo(QLatin1String("GNU/Linux"));
    appInfo->setLanguageCode(QLatin1String("en"));
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("TelegramQt-CLI");
    app.setApplicationVersion(QStringLiteral("0.1"));

    const QString defaultProfilesLocation =
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
            + QLatin1String("/profiles");

    QCommandLineParser parser;
    parser.addHelpOption();

    QCommandLineOption profilesLocationOption(QStringList({ QLatin1String("profiles-location") }));
    profilesLocationOption.setValueName(QLatin1String("location"));
    profilesLocationOption.setDefaultValue(defaultProfilesLocation);
    parser.addOption(profilesLocationOption);

    QCommandLineOption profileOption(QStringList({ QLatin1String("p"), QLatin1String("profile") }));
    profileOption.setValueName(QLatin1String("profile"));
    parser.addOption(profileOption);

    QCommandLineOption configAddressOption(QStringList({ QLatin1String("a"), QLatin1String("address") }));
    configAddressOption.setValueName(QLatin1String("ip:port"));
    parser.addOption(configAddressOption);

    QCommandLineOption verboseOption(QStringList({ QLatin1String("v"), QLatin1String("verbose") }));
    parser.addOption(verboseOption);

    QCommandLineOption interactiveModeOption(QStringList({ QLatin1String("i"), QLatin1String("interactive") }));
    parser.addOption(interactiveModeOption);

    QCommandLineOption contactListOption(QStringList({ QLatin1String("contact-list") }));
    parser.addOption(contactListOption);

    QCommandLineOption filePathOption(QStringList({ QLatin1String("file-path") }));
    configAddressOption.setValueName(QLatin1String("path"));
    parser.addOption(filePathOption);

    parser.process(app);

    CliClient client;

    const QString profilesDir = parser.value(profilesLocationOption);
    const QString profileName = parser.value(profileOption);
    Telegram::Client::FileAccountStorage *accountStorage = new Telegram::Client::FileAccountStorage(&client);
    accountStorage->setAccountIdentifier(profileName);
    accountStorage->setFileName(profilesDir + QLatin1Char('/') + profileName);
    accountStorage->loadData();

    if (parser.isSet(configAddressOption)) {
        client.setServerAddress(parser.value(configAddressOption));
    }

    setupAppInfo(client.appInformation());
    client.setAccountStorage(accountStorage);

    if (parser.isSet(interactiveModeOption)) {
        client.startInteractiveMode();
    } else {
        if (parser.isSet(contactListOption)) {
            PendingOperation *checkIn = client.connectionApi()->checkIn();
            QObject::connect(checkIn, &PendingOperation::succeeded,
                             [&client]() {
                PendingOperation *request = client.requestContactList();
                QObject::connect(request, &PendingOperation::finished, []() {
                    qApp->quit();
                });
            });
        }
    }

    return app.exec();
}

#include "main.moc"
