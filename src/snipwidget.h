#pragma once

#include <QMainWindow>
#include <QWindow>
class QLabel;

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
};