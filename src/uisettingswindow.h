#pragma once

class QMainWindow;
class QWidget;
class MainChart;
class DetailTreeView;
class QPushButton;
class QLineEdit;

// Custom UI class that holds all the widgets for a window (so we won't add additional mess to the window)
class UISettingsWindow
{
public:
	void setupUI(QMainWindow* settings_window);

	[[nodiscard]] QWidget* centralWidget() const noexcept
	{
		return central_widget_;
	}

	[[nodiscard]] QLineEdit* savePathEdit() const noexcept
	{
		return save_path_edit_;
	}

	[[nodiscard]] QPushButton* savePathButton() const noexcept
	{
		return save_path_button_;
	}

	[[nodiscard]] QPushButton* saveChangesButton() const noexcept
	{
		return save_changes_button_;
	}

	[[nodiscard]] QPushButton* cancelChangesButton() const noexcept
	{
		return cancel_changes_button_;
	}


private:
	QWidget* central_widget_{ nullptr };
	QLineEdit* save_path_edit_{ nullptr };
	QPushButton* save_path_button_{ nullptr };
	QPushButton* save_changes_button_{ nullptr };
	QPushButton* cancel_changes_button_{ nullptr };
};