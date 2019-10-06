#pragma once

#include <QMainWindow>
#include <QWindow>
class QLabel;

class SelectionDrawer : public QWidget
{
public:
	using QWidget::QWidget;

	void setSelectionRect(QRect selectionRect);

protected:
	void paintEvent(QPaintEvent* event) override;

};

class SnipWidget : public QMainWindow
{
public:
	SnipWidget();
	bool event(QEvent* event) override;
	
protected:
	void keyPressEvent(QKeyEvent* event) override;

private:
	void cancelSnip();
	void grabCurrentScreen();
	void copyPixmapToClipboard();

private:
	QPixmap original_pixmap_;
	QLabel* background_{ nullptr };
	SelectionDrawer* selectionWidget_{ nullptr };
};