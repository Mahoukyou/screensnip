#pragma once

#include <QWidget>

class QLabel;

class SnipWidget : public QWidget
{
public:
	SnipWidget();

private:
	void grabCurrentScreen();
	void copyPixmapToClipboard();

private:
	QPixmap original_pixmap_;
	QLabel* background_{ nullptr };
};