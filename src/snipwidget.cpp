#include "snipwidget.h"

#include <QGuiApplication>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QClipboard>
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

void SelectionDrawer::paintEvent(QPaintEvent* event)
{
	QPainter painter{ this };
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(124, 124, 124, 124)));
	painter.drawRect(0, 0, 1920, 1080);
}

SnipWidget::SnipWidget() :
	background_{ new QLabel{this} },
	selectionWidget_{ new SelectionDrawer{this} }
{
	setCentralWidget(new QWidget{this});
	background_->setParent(centralWidget());
	selectionWidget_->setParent(centralWidget());
		
	grabCurrentScreen();
	
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(QGuiApplication::primaryScreen()->size());
	move(0, 0);

	selectionWidget_->setFixedSize(size());
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
