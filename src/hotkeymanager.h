#pragma once

#include <QString>
#include <memory>
#include "uglobalhotkeys.h"

class HotkeyManager : public QObject
{
public:
	enum class EHotkey
	{
		SnipWidget,
		EntireScreenshot,
		Max
	};

private:
	HotkeyManager();

public:
	HotkeyManager(const HotkeyManager&) = delete;
	HotkeyManager(HotkeyManager&&) = delete;

	HotkeyManager& operator=(const HotkeyManager&) = delete;
	HotkeyManager& operator=(HotkeyManager&&) = delete;

	static HotkeyManager& instance();
	
	void setupHotkey(const QString& hotkey, EHotkey hotkey_type);
	void cancelHotkey(EHotkey hotkey_type);

private:
	void activated(size_t id) const;

	std::unique_ptr<UGlobalHotkeys> global_hotkeys_;
};