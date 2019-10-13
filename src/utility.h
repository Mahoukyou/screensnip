#pragma once

#include <QPixmap>
#include <QDir>

namespace utility
{
	bool savePixmapToDisk(const QPixmap& pixmap);
	[[nodiscard]] QString getAvailableFilepath(const QDir& path, const QString& base_filename);
	[[nodiscard]] bool itemExists(const QString& filepath);
	bool makeDirectoryPathIfNotExists(const QString& path);

	void takeEntireScreenScreenshot();
}