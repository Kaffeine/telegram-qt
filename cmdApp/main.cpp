#include <QFile>
#include <QTimer>
#include <chrono>
#include <thread>
#include <QDebug>
#include <iostream>
#include <functional>
#include <QTextStream>
#include <QCoreApplication>
#include <CTelegramCore.hpp>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <CAppInformation.hpp>


QTextStream cout(stdout);
QTextStream cin(stdin);
static const auto timeout = std::chrono::microseconds(0);
std::thread readThread;
bool verboseEnabled = false;

QCommandLineOption verboseOption(QStringList() << "v" << "verbose", "Set verbose option");
QCommandLineOption registerOption(QStringList() << "r" << "register", "Register a new <phone_number>.", "phone_number");
QCommandLineOption displayContactListOption(QStringList() << "l" << "list", "Display contact list");
QCommandLineOption sendMessageOption(QStringList() << "m" << "message", "Send a message to a phone number", "contact_phone_number");
QCommandLineOption displayChatListOption(QStringList() << "c" << "chat-list", "Display chat list");
QCommandLineOption sendGroupByIdOption(QStringList() << "g" << "group-message-by-id", "Send a message to a group", "group_id");
QCommandLineOption sendGroupByNameOption(QStringList() << "n" << "group-message-by-name", "Send a message to a group", "group_name");

void MessageOutput(QtMsgType type, const QMessageLogContext &context, 
	const QString &msg)
{
	QByteArray localMsg = msg.toLocal8Bit();
	switch (type) {
	case QtDebugMsg:
		if (verboseEnabled)
		{
			fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(),
				context.file, context.line, context.function);
		}
		break;
	case QtWarningMsg:
		fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), 
			context.file, context.line, context.function);
		break;
	case QtCriticalMsg:
		fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), 
			context.file, context.line, context.function);
		break;
	case QtFatalMsg:
		fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), 
			context.file, context.line, context.function);
		abort();
    default:
        break;
	}
}

void RequestPhoneCode(CTelegramCore& core, const QString& phoneNumber)
{
	core.requestPhoneCode(phoneNumber);
	readThread = std::thread([&,phoneNumber]()
	{
		QString code;
		cout << "Enter the received code: " << endl;
		cin >> code;
		core.metaObject()->invokeMethod(&core, "signIn", 
			Q_ARG(QString, phoneNumber), Q_ARG(QString, code));
	});
}

void Register(CTelegramCore& core, TelegramNamespace::ConnectionState state, 
	const QString& phoneNumber, const QString& secretFile)
{
	switch (state)
	{
	case TelegramNamespace::ConnectionStateConnected:
		core.requestPhoneStatus(phoneNumber);
		core.requestPhoneCode(phoneNumber);
		break;
	case TelegramNamespace::ConnectionStateAuthRequired:
	{
		RequestPhoneCode(core, phoneNumber);
		break;
	}
	case TelegramNamespace::ConnectionStateAuthenticated:
	{
		cout << "Saving secret file..." << endl;
		QFile file(secretFile);
		if (file.open(QIODevice::WriteOnly))
		{
			file.write(core.connectionSecretInfo());
			cout << "File " << secretFile << " saved" << endl;
		}
		else
            qFatal("Failed to open file %s", qPrintable(secretFile));
		qApp->quit();
		break;
	}
	case TelegramNamespace::ConnectionStateDisconnected:
		qApp->quit();
		break;
    default:;
	}
}

void DisplayContactList(CTelegramCore& core)
{
	core.connect(&core, &CTelegramCore::contactListChanged, [&]()
	{
		auto list = core.contactList();
		for (const auto& contact : list)
		{
			cout << core.contactFirstName(contact) << " " 
				<< core.contactLastName(contact) << endl;
		}
		qApp->quit();
	});
	core.connect(&core, &CTelegramCore::connectionStateChanged, [&](
		TelegramNamespace::ConnectionState state)
	{
		if (state == TelegramNamespace::ConnectionStateDisconnected)
			qApp->exit(EXIT_FAILURE);
	});
}

void DisplayChatList(CTelegramCore& core)
{
	auto timer = new QTimer(qApp);
	timer->setInterval(3000);
	QObject::connect(timer, &QTimer::timeout, qApp, &QCoreApplication::quit);
	core.connect(&core, &CTelegramCore::chatAdded, [&,timer](quint32 id)
	{
		cout << id << ": " << core.chatTitle(id) << endl;
		timer->start();
	});
	core.connect(&core, &CTelegramCore::connectionStateChanged, [&,timer](
		TelegramNamespace::ConnectionState state)
	{
		if (state == TelegramNamespace::ConnectionStateConnected)
			timer->start();
		if (state == TelegramNamespace::ConnectionStateDisconnected)
			qApp->exit(EXIT_FAILURE);
	});
}

QMap<quint32, QString> GetGroupChats(CTelegramCore& core)
{
    decltype(GetGroupChats(core)) ret;
    auto timer = new QTimer(qApp);
    timer->setInterval(3000);
    QObject::connect(timer, &QTimer::timeout, qApp, &QCoreApplication::quit);
    core.connect(&core, &CTelegramCore::chatAdded, [&,timer](quint32 id)
    {
        ret.insert(id, core.chatTitle(id));
        timer->start();
    });
    core.connect(&core, &CTelegramCore::connectionStateChanged, [&,timer](
        TelegramNamespace::ConnectionState state)
    {
        if (state == TelegramNamespace::ConnectionStateConnected)
            timer->start();
        if (state == TelegramNamespace::ConnectionStateDisconnected)
            qApp->exit(EXIT_FAILURE);
    });
    return ret;
}

void SendMessage(CTelegramCore& core, const QString& phoneNumber,
	const QString& message)
{
	core.connect(&core, &CTelegramCore::sentMessageStatusChanged, [](
		const QString &contact, quint64, 
		TelegramNamespace::MessageDeliveryStatus status)
	{
		if (status == TelegramNamespace::MessageDeliveryStatusSent)
		{
			cout << "Message sent to " << contact << endl;
			qApp->exit(EXIT_SUCCESS);
		}
	});
	core.connect(&core, &CTelegramCore::connectionStateChanged, 
		[&, phoneNumber, message](TelegramNamespace::ConnectionState state)
	{
		if (state == TelegramNamespace::ConnectionStateDisconnected)
			qApp->exit(EXIT_FAILURE);
		else if (state == TelegramNamespace::ConnectionStateReady)
		{
			cout << "Sending " << message << " to " << phoneNumber << endl;
			core.sendMessage(phoneNumber, message);
		}
	});
}

void SendMessageToGroup(CTelegramCore& core, quint32 chatId,
	const QString& message)
{
	core.connect(&core, &CTelegramCore::sentMessageStatusChanged, [&,chatId](
		const QString&, quint64,
		TelegramNamespace::MessageDeliveryStatus status)
	{
		if (status == TelegramNamespace::MessageDeliveryStatusSent)
		{
			cout << "Message sent to " << core.chatTitle(chatId) << endl;
			qApp->exit(EXIT_SUCCESS);
		}
	});
	core.connect(&core, &CTelegramCore::connectionStateChanged,
		[&, chatId, message](TelegramNamespace::ConnectionState state)
	{
		if (state == TelegramNamespace::ConnectionStateDisconnected)
			qApp->exit(EXIT_FAILURE);
		else if (state == TelegramNamespace::ConnectionStateReady)
		{
			cout << "Sending " << message << " to " << core.chatTitle(chatId) 
				<< endl;
			core.sendChatMessage(chatId, message);
		}
	});
}

int main(int argc, char** argv)
{
	qInstallMessageHandler(MessageOutput);
	QCoreApplication app(argc, argv);
	QCoreApplication::setApplicationName("Telegram-Qt");
	QCoreApplication::setApplicationVersion("0.1");
	QString secretFile = "secret";
	QString serverIp = "149.154.175.50";
	QString message;
	quint32 serverPort = 443;
	QCommandLineParser parser;
	parser.setApplicationDescription("Telegram-Qt for CommandLine");
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addOption(verboseOption);
	parser.addOption(registerOption);
	parser.addOption(displayContactListOption);
	parser.addOption(sendMessageOption);
	parser.addOption(displayChatListOption);
    parser.addOption(sendGroupByIdOption);
    parser.addOption(sendGroupByNameOption);
	parser.addPositionalArgument("secret_file", "Secret file to create/use.");
	parser.addPositionalArgument("message...", "Message text to send to a contact");
	parser.process(app);

	if (parser.positionalArguments().size() >= 1)
		secretFile = parser.positionalArguments().first();
	else
		parser.showHelp(EXIT_FAILURE);
	if (parser.positionalArguments().size() == 2)
		message = parser.positionalArguments()[1];

	CTelegramCore telegram;
	CAppInformation appInfo;
	appInfo.setAppId(14617);
	appInfo.setAppHash(QLatin1String("e17ac360fd072f83d5d08db45ce9a121"));
	appInfo.setAppVersion(QLatin1String("0.1"));
	appInfo.setDeviceInfo(QLatin1String("pc"));
	appInfo.setOsInfo(QLatin1String("GNU/Linux"));
	appInfo.setLanguageCode(QLatin1String("en"));
	telegram.setAppInformation(&appInfo);

	if (telegram.initConnection(serverIp, serverPort))
	{
		if (parser.isSet(registerOption))
		{
			const QString phoneNumber = parser.value("register");
			auto bind = std::bind(&Register, std::ref(telegram), 
				std::placeholders::_1, phoneNumber, secretFile);
			telegram.connect(&telegram, &CTelegramCore::connectionStateChanged,
				bind);
			cout << "Registering " << qPrintable(phoneNumber) << "..." << endl;
		}
		else
		{
			QFile secret(secretFile);
			if (!secret.open(QIODevice::ReadOnly))
			{
				qFatal("Failed to open secret file");
				return EXIT_FAILURE;
			}
			else if (!telegram.restoreConnection(secret.readAll()))
			{
				qFatal("Failed to restore connection");
				return EXIT_FAILURE;
			}
			if (parser.isSet(displayContactListOption))
				DisplayContactList(telegram);
			else if (parser.isSet(displayChatListOption))
				DisplayChatList(telegram);
			else if (parser.isSet(sendMessageOption) 
				&& parser.positionalArguments().size() >= 2)
			{
				const auto phoneNumber = parser.value(sendMessageOption);
				const auto message = parser.positionalArguments().at(1);
				SendMessage(telegram, phoneNumber, message);
			}
            else if (parser.isSet(sendGroupByIdOption)
				&& parser.positionalArguments().size() >= 2)
			{
				bool ok;
                const auto chatId = parser.value(sendGroupByIdOption).toUInt(&ok);
				const auto message = parser.positionalArguments().at(1);
				if (!ok)
				{
					qFatal("Invalid chat id");
					return EXIT_FAILURE;
				}
                SendMessageToGroup(telegram, chatId, message);
			}
            else if (parser.isSet(parser.value(sendGroupByNameOption))) {
                const auto message = parser.positionalArguments().at(1);
                const auto chatName = parser.value(sendGroupByIdOption);
                const auto chats = GetGroupChats(telegram);
                bool found = false;
                for (auto it = chats.end(), end = chats.end(); it != end; ++it) {
                    if (it.value() == chatName) {
                        SendMessageToGroup(telegram, it.key(), message);
                        found = true;
                    }
                }
                if (!found) {
                    qFatal("Group name %s not found", qPrintable(chatName));
                    return EXIT_FAILURE;
                }
            }
		}
	}
	int result = app.exec();
	if (readThread.joinable())
		readThread.join();
	return result;
}
