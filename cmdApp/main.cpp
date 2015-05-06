#include <QCoreApplication>
#include <CTelegramCore.hpp>
#include <QCommandLineParser>
#include <QCommandLineOption>

QCommandLineOption registerOption(QStringList() << "r" << "register", "Register a new <phone_number>.", "phone_number");

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);
	QCoreApplication::setApplicationName("Telegram-Qt");
	QCoreApplication::setApplicationVersion("0.1");

	QCommandLineParser parser;
	parser.setApplicationDescription("Telegram-Qt for CommandLine");
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addOption(registerOption);
	parser.addPositionalArgument("secret_file", "Secret file to create/use.");
	parser.process(app);

	if (!parser.isSet("secret_file"))
	{
		parser.showHelp(EXIT_FAILURE);
	}

	CTelegramCore telegram;

	if (parser.isSet("register"))
	{
		QString phoneNumber = parser.value("register");
		telegram.requestPhoneCode(phoneNumber);
	}
}
