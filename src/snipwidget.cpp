#include "snipwidget.h"

#include <QGuiApplication>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QClipboard>

SnipWidget::SnipWidget() :
	background_{ new QLabel{this} }
{
	setVisible(false);
	
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(QGuiApplication::primaryScreen()->size());
	move(0, 0);
	
	grabCurrentScreen();
	copyPixmapToClipboard();

	setVisible(true);
}

void SnipWidget::grabCurrentScreen()
{
	QScreen* screen = QGuiApplication::primaryScreen();
	if (!screen)
	{
		return;
	}
	
	original_pixmap_ = screen->grabWindow(0);
	background_->setPixmap(original_pixmap_);
}

void SnipWidget::copyPixmapToClipboard()
{
	QApplication::clipboard()->setPixmap(original_pixmap_);
}
