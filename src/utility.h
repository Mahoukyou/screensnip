#pragma once

#include <QPixmap>

namespace utility
{
	bool savePixmapToDisk(const QPixmap& pixmap);
	QString getAvailableFilepath(const QString& path, const QString& base_filename);
	bool itemExists(const QString& filepath);
	bool makeDirectoryPathIfNotExists(const QString& path);

	void takeEntireScreenScreenshot();
}