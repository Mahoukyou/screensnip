#include "vld.h"

#include <QApplication>
#include "mainwindow.h"

#include "uglobalhotkeys.h"
#include <QDebug>


int main(int argc, char *argv[])
{
	int result{};
	{
		QApplication a(argc, argv);

		// teest
		UGlobalHotkeys* hotkeyManager = new UGlobalHotkeys();
		hotkeyManager->registerHotkey("Ctrl+Shift+F11 ");
		QObject::connect(hotkeyManager, &UGlobalHotkeys::activated, [=](size_t id)
		{
			qDebug() << "Activated: " << QString::number(id);
		});

		
		MainWindow window;
		window.show();

		result = a.exec();
	}

	return result;
}
