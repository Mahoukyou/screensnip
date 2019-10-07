#include "snipwidget.h"

#include <QGuiApplication>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QClipboard>
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

void SelectionDrawer::setSelectionRect(const QRect selection_rect)
{
	selection_rect_ = selection_rect;
}

void SelectionDrawer::paintEvent(QPaintEvent* event)
{
	QPainter painter{ this };
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(124, 124, 124, 124)));
	painter.drawRect(0, 0, size().width(), size().height());
	painter.eraseRect(selection_rect_); // todo doesn't work -- erases everything
	// either reverse the mask or draw 4 rects
}

SnipWidget::SnipWidget() :
	background_{ new QLabel{this} },
	selection_widget_{ new SelectionDrawer{this} }
{
	setCentralWidget(new QWidget{this});
	background_->setParent(centralWidget());
	selection_widget_->setParent(centralWidget());
		
	grabCurrentScreen();
	
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(QGuiApplication::primaryScreen()->size());
	move(0, 0);

	selection_widget_->setFixedSize(size());
}

bool SnipWidget::event(QEvent* const event)
{
	if (event->type() == QEvent::ActivationChange)
	{
		// Focus lost
		if (!isActiveWindow())
		{
			cancelSnip();
			return true;
		}
	}

	return QMainWindow::event(event);
}

void SnipWidget::keyPressEvent(QKeyEvent* const event)
{
	if(event->key() == Qt::Key_Escape)
	{
		cancelSnip();
		event->accept();
	}

	event->ignore();
}

void SnipWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		selection_rect_ = QRect{
			static_cast<int>(event->screenPos().x()),
			static_cast<int>(event->screenPos().y()), 0, 0 };

		is_selecting_ = true;
	}
}

void SnipWidget::mouseReleaseEvent(QMouseEvent* event)
{
	// todo, snip pixmap to the rect
}

void SnipWidget::mouseMoveEvent(QMouseEvent* event)
{
	if(is_selecting_)
	{
		// todo, reverse pos with size if result of subtraction is negative
		selection_rect_.setWidth(std::abs(selection_rect_.x() - event->screenPos().x()));
		selection_rect_.setHeight(std::abs(selection_rect_.y() - event->screenPos().y()));

		selection_widget_->setSelectionRect(selection_rect_);
		selection_widget_->update();
	}
}

void SnipWidget::cancelSnip()
{
	setVisible(false);
	deleteLater();
}

void SnipWidget::grabCurrentScreen()
{
	QScreen* const screen = QGuiApplication::primaryScreen();
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
