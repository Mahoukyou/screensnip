#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "uimainwindow.h"

class QSystemTrayIcon;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	std::unique_ptr<UIMainWindow> ui_;

	void quit();
	void closeEvent(QCloseEvent* event) override;

private:
	void createTrayIcon();
	void createTrayIconActions();
	void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

	QSystemTrayIcon *tray_icon_{ nullptr };
};

#endif // MAINWINDOW_H
