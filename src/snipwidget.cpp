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
	// todo. ,s witch
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		selection_begin_ = event->screenPos().toPoint();

		is_selecting_ = true;
	}

	if (event->button() == Qt::MouseButton::RightButton && is_selecting_)
	{
		is_selecting_ = false;
		selection_begin_ = {};
		selection_rect_ = {};

		updateSelectionWidget();
	}
}

void SnipWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton && is_selecting_)
	{
		is_selecting_ = false;
		// todo
	}
}

void SnipWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (is_selecting_)
	{
		const QPoint current_pos = event->screenPos().toPoint();
		const int width = current_pos.x() - selection_begin_.x();
		const int height = current_pos.y() - selection_begin_.y();

		selection_rect_ = QRect{
			width < 0 ? current_pos.x() : selection_begin_.x(),
			height < 0 ? current_pos.y() : selection_begin_.y(),
			std::abs(width),
			std::abs(height) };

		updateSelectionWidget();
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

void SnipWidget::updateSelectionWidget()
{
	selection_widget_->setSelectionRect(selection_rect_);
	selection_widget_->update();
}