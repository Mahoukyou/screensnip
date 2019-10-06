#include "vld.h"

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	int result{};
	{
		QApplication a(argc, argv);

		MainWindow window;
		window.show();

		result = a.exec();
	}

	return result;
}
