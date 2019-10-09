#include "hotkeymanager.h"
#include "snipwidget.h"
#include "utility.h"

HotkeyManager::HotkeyManager() :
	global_hotkeys_{ std::make_unique<UGlobalHotkeys>() }
{
	connect(global_hotkeys_.get(), &UGlobalHotkeys::activated, this, &HotkeyManager::activated);
}

HotkeyManager& HotkeyManager::instance()
{
	static HotkeyManager hotkey_manager{};

	return hotkey_manager;
}

// TODO[2] Due to limitations of the global hotkeys library we are unable to check if registration was successful
// todo, might change that later
void HotkeyManager::setupHotkey(const QString& hotkey, const EHotkey hotkey_type)
{
	global_hotkeys_->registerHotkey(hotkey, static_cast<size_t>(hotkey_type));
}

void HotkeyManager::cancelHotkey(const EHotkey hotkey_type)
{
	global_hotkeys_->unregisterHotkey(static_cast<size_t>(hotkey_type));
}

void HotkeyManager::activated(const size_t id) const
{
	if (id >= static_cast<size_t>(EHotkey::Max))
	{
		return;
	}
	
	switch(static_cast<EHotkey>(id))
	{
	case EHotkey::SnipWidget:
	{
		auto snip_widget = SnipWidget::create_snip_widget();
		snip_widget->show();
		snip_widget->raise();
		snip_widget->activateWindow();
		break;
	}

	case EHotkey::EntireScreenshot:
		utility::takeEntireScreenScreenshot();
		break;

	case EHotkey::Max:
		[[fallthrough]] ;
	default:;
	}
}
