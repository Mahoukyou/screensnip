#pragma once

class QWidget;
class MainChart;
class DetailTreeView;
class QPushButton;
class QLineEdit;

// Custom UI class that holds all the widgets for a window (so we won't add additional mess to the window)
class UISettingsWindow
{
public:
	void setupUI(QWidget* settings_widget);

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
	QLineEdit* save_path_edit_{ nullptr };
	QPushButton* save_path_button_{ nullptr };
	QPushButton* save_changes_button_{ nullptr };
	QPushButton* cancel_changes_button_{ nullptr };
};