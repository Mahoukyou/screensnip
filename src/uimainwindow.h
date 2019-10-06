#pragma once
#include <array>
#include <cassert>

class QMainWindow;
class QWidget;
class MainChart;
class DetailTreeView;
class QPushButton;

// Custom UI class that holds all the widgets for main window (so we won't add additional mess to mw)
class UIMainWindow
{
public:
	void setupUI(QMainWindow* main_window);

	QWidget* centralWidget() const noexcept
	{
		return central_widget_;
	}

	QPushButton* snipButton() const noexcept
	{
		return snip_button_;
	}
	

private:
	QWidget* central_widget_{ nullptr };
	QPushButton* snip_button_{ nullptr };
};