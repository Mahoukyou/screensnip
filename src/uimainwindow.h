#pragma once

class QMainWindow;
class QWidget;

// Custom UI class that holds all the widgets for main window (so we won't add additional mess to mw)
class UIMainWindow
{
public:
	void setupUI(QMainWindow* main_window);

	[[nodiscard]] QWidget* centralWidget() const noexcept
	{
		return central_widget_;
	}

private:
	QWidget* central_widget_{ nullptr };
};