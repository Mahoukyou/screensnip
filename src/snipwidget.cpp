#include "snipwidget.h"

#include <QGuiApplication>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QClipboard>
#include <QDebug>
#include <QKeyEvent>

SnipWidget::SnipWidget() :
	background_{ new QLabel{this} }
{
	setCentralWidget(background_);
		
	grabCurrentScreen();
//	copyPixmapToClipboard();
	
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(QGuiApplication::primaryScreen()->size());
	move(0, 0);
}

bool SnipWidget::event(QEvent* event)
{
	if (event->type() == QEvent::ActivationChange)
	{
		// Focus lost
		if (!this->isActiveWindow())
		{
			cancelSnip();
			return true;
		}
	}

	return QMainWindow::event(event);
}

void SnipWidget::keyPressEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Escape)
	{
		cancelSnip();
		event->accept();
	}

	event->ignore();
}


void SnipWidget::cancelSnip()
{
	setVisible(false);
	deleteLater();
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
