#include <QDebug>
#include <iostream>
#include <functional>
#include <QTextStream>
#include <QCoreApplication>
#include <CTelegramCore.hpp>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <CAppInformation.hpp>

QTextStream ios(stdout);

QCommandLineOption registerOption(QStringList() << "r" << "register", "Register a new <phone_number>.", "phone_number");

void Register(CTelegramCore& core, TelegramNamespace::ConnectionState state, 
	const QString& phoneNumber)
{
	switch (state)
	{
	case TelegramNamespace::ConnectionStateConnected:
		core.requestPhoneStatus(phoneNumber);
		core.requestPhoneCode(phoneNumber);
		break;
	case TelegramNamespace::ConnectionStateAuthRequired:
	{
		QString code;
		core.requestPhoneCode(phoneNumber);
		ios << "Enter the received code: " << endl;
		ios >> code;
		break;
	}
	}
}

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);
	QCoreApplication::setApplicationName("Telegram-Qt");
	QCoreApplication::setApplicationVersion("0.1");
	QString secretFile = "secret";
	QString serverIp = "149.154.175.50";
	quint32 serverPort = 443;
	QCommandLineParser parser;
	parser.setApplicationDescription("Telegram-Qt for CommandLine");
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addOption(registerOption);
	parser.addPositionalArgument("secret_file", "Secret file to create/use.");
	parser.process(app);

	if (parser.positionalArguments().size() == 1)
		secretFile = parser.positionalArguments().first();
	else
		parser.showHelp(EXIT_FAILURE);


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
		if (parser.isSet("register"))
		{
			const QString phoneNumber = parser.value("register");
			auto bind = std::bind(&Register, std::ref(telegram), 
				std::placeholders::_1, phoneNumber);
			telegram.connect(&telegram, &CTelegramCore::connectionStateChanged,
				bind);
			ios << "Registering " << qPrintable(phoneNumber) << "..." << endl;
		}
	}
	return app.exec();
}
