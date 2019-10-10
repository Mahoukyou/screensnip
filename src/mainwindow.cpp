#include "mainwindow.h"
#include "uimainwindow.h"

#include <QCloseEvent>
#include <QMenu>
#include <QCoreApplication>

#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget* const parent) :
	QMainWindow{ parent },
	ui_{ std::make_unique<UIMainWindow>() }
{
	ui_->setupUI(this);

	createTrayIcon();
	createTrayIconActions();

	connect(ui_->snipButton(), &QPushButton::clicked, this, &MainWindow::onSnipButtonClicked);
}

MainWindow::~MainWindow()
{

}

void MainWindow::quit()
{
	QCoreApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent* const event)
{
	event->ignore();
	if (tray_icon_ && tray_icon_->isVisible())
	{
		hide();
	}
	else
	{
		quit();
	}
}


void MainWindow::createTrayIcon()
{
	tray_icon_ = new QSystemTrayIcon{ this };
	tray_icon_->setIcon(QIcon(R"(K:\Development\ScreenSnip\resources\icon.png)")); // todo
	tray_icon_->show();

	connect(tray_icon_, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);
}

void MainWindow::createTrayIconActions()
{
	const auto tray_icon_menu = new QMenu{ this };

	const auto quit_action = new QAction{ tr("Quit"), tray_icon_menu };
	connect(quit_action, &QAction::triggered, this, &MainWindow::quit);
	tray_icon_menu->addAction(quit_action);

	tray_icon_->setContextMenu(tray_icon_menu);
}

void MainWindow::onTrayIconActivated(const QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::DoubleClick:
		setVisible(!isVisible()); // for now lets just hide/show
		// todo -- close the window entirely? so it won't consume resources while hidden
		break;

	default:;
	}
}

void MainWindow::onSnipButtonClicked()
{

}
