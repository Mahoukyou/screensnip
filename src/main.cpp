#include "vld.h"

#include <QApplication>
#include "mainwindow.h"

#include "uglobalhotkeys.h"
#include <QDebug>

#include "snipwidget.h"


int main(int argc, char *argv[])
{
	int result{};
	{
		QApplication a(argc, argv);

		// teest
		UGlobalHotkeys* hotkeyManager = new UGlobalHotkeys();
		hotkeyManager->registerHotkey("Alt+Shift+S");
		QObject::connect(hotkeyManager, &UGlobalHotkeys::activated, [](size_t id)
		{
			auto snip_widget = SnipWidget::create_snip_widget();
			snip_widget->show();
			snip_widget->raise();
			snip_widget->activateWindow();
		});

		
		MainWindow window;
		window.show();

		result = a.exec();
	}

	return result;
}
