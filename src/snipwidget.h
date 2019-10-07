#pragma once

#include <QMainWindow>
#include <QWindow>

class QLabel;

class SelectionWidget : public QWidget
{
public:
	using QWidget::QWidget;
	
	void setSelectionRect(QRect selection_rect);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QRegion clip_region_;
};

class SnipWidget : public QMainWindow
{
public:
	SnipWidget();
	bool event(QEvent* event) override;
	
protected:
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	
private:
	void cancelSnip();
	void grabCurrentScreen();
	void copyPixmapToClipboard();

	void createPixmapFromSelection();

	void updateSelectionWidget();

private:
	QPixmap original_pixmap_;
	QPixmap selected_pixmap_;
	QLabel* background_{ nullptr };
	SelectionWidget* selection_widget_{ nullptr };

	QPoint selection_begin_;
	QRect selection_rect_;
	bool is_selecting_{ false };
};