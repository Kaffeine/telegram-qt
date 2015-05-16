#include <QFile>
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
			qFatal("Failed to open file %s", secretFile);
		qApp->quit();
		break;
	}
	case TelegramNamespace::ConnectionStateDisconnected:
		qApp->quit();
		break;
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
			else if (parser.isSet(sendMessageOption) 
				&& parser.positionalArguments().size() >= 2)
			{
				const auto phoneNumber = parser.value(sendMessageOption);
				const auto message = parser.positionalArguments().at(1);
				SendMessage(telegram, phoneNumber, message);
			}
		}
	}
	int result = app.exec();
	if (readThread.joinable())
		readThread.join();
	return result;
}
