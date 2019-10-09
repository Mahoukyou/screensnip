#include "snipwidget.h"

#include <QGuiApplication>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QClipboard>
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

#include "utility.h"
#include "settings.h"

void SelectionWidget::setSelectionRect(const QRect& selection_rect)
{
	clip_region_ += QRect{0, 0, size().width(), size().height()};
	clip_region_ -= selection_rect;
}

void SelectionWidget::paintEvent(QPaintEvent* const event)
{
	QPainter painter{ this };
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(124, 124, 124, 124)));
	painter.setClipRegion(clip_region_);
	painter.drawRect(0, 0, size().width(), size().height());
}

SnipWidget* SnipWidget::instance_ = nullptr;

SnipWidget::SnipWidget() :
	background_{ new QLabel{this} },
	selection_widget_{ new SelectionWidget{this} }
{
	setCentralWidget(new QWidget{this});
	background_->setParent(centralWidget());
	selection_widget_->setParent(centralWidget());
		
	grabCurrentScreen();
	
	setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
	setFixedSize(QGuiApplication::primaryScreen()->size());
	move(0, 0);

	selection_widget_->setFixedSize(size());
	selection_widget_->setSelectionRect({});
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

void SnipWidget::cancelSnip()
{
	instance_ = nullptr;

	setVisible(false);
	deleteLater();
}

SnipWidget* SnipWidget::create_snip_widget()
{
	if (instance_)
	{
		// TODO[3], reset the current snipwidget instead of re-instancing<?>
		instance_->cancelSnip();
	}

	instance_ = new SnipWidget{};
	return instance_;
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

void SnipWidget::mousePressEvent(QMouseEvent* const event)
{
	switch(event->button())
	{
	case Qt::MouseButton::LeftButton:
		beginSelection(event->screenPos().toPoint());
		break;

	case Qt::MouseButton::RightButton:
		cancelSelection();
		break;

	default:;
	}
}

void SnipWidget::mouseReleaseEvent(QMouseEvent* const event)
{
	if (event->button() == Qt::MouseButton::LeftButton && is_selecting_)
	{
		is_selecting_ = false;

		// copy to clipboard even if multiple snips modifier is on (user might cancel the last snip)
		createPixmapFromSelection();
		copyPixmapToClipboard();
		utility::savePixmapToDisk(selected_pixmap_);

		Settings& settings = Settings::instance();
		if (QApplication::keyboardModifiers() == settings.multipleSnipsModifier())
		{
			cancelSelection();
		}
		else
		{
			cancelSnip();
		}
	}
}

void SnipWidget::mouseMoveEvent(QMouseEvent* const event)
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

void SnipWidget::copyPixmapToClipboard() const
{
	QApplication::clipboard()->setPixmap(selected_pixmap_);
}

void SnipWidget::createPixmapFromSelection()
{
	selected_pixmap_ = original_pixmap_.copy(selection_rect_);
}

void SnipWidget::beginSelection(const QPoint& position)
{
	selection_begin_ = position;
	is_selecting_ = true;
}

void SnipWidget::cancelSelection()
{
	is_selecting_ = false;
	selection_begin_ = {};
	selection_rect_ = {};

	updateSelectionWidget();
}

void SnipWidget::updateSelectionWidget() const
{
	selection_widget_->setSelectionRect(selection_rect_);
	selection_widget_->update();
}
