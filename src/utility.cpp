#include "utility.h"

#include <QFile>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>

bool utility::savePixmapToDisk(const QPixmap& pixmap)
{
	// todo cleanup  a litile
	const QString directory_path = R"(K:\Snips\)"; // todo, allow user to set path
	if (!makeDirectoryPathIfNotExists(directory_path))
	{
		return false;
	}
	
	const QDateTime now = QDateTime::currentDateTime();
	const QString base_filename = "Snip " + now.toString("yyyy-MM-d h-mm-ss");
	const QString filepath = getAvailableFilepath(directory_path, base_filename);
	
	QFile file(filepath);
	if (!file.open(QIODevice::WriteOnly))
	{
		return false;
	}

	return pixmap.save(&file, "PNG");
}

QString utility::getAvailableFilepath(const QString& path, const QString& base_filename)
{
	// todo, multiple extension types<?>
	const QString base_filepath = path + base_filename;
	if (const auto filepath = base_filepath + ".png";
		!itemExists(filepath))
	{
		return filepath;
	}

	for (unsigned long long i = 1; i < std::numeric_limits<unsigned long long>::max(); ++i)
	{
		const QString filepath = base_filepath + " (" + QString::number(i) + ").png"; // todo dynamic extgension
		if (!itemExists(filepath))
		{
			return filepath;
		}
	}

	throw std::runtime_error{ "Couldn't find valid filepath" };
}

bool utility::itemExists(const QString& filepath)
{
	const QFileInfo file_info{ filepath };

	return file_info.exists();
}

bool utility::makeDirectoryPathIfNotExists(const QString& path)
{
	const QDir dir{ path };
	if (!dir.exists())
	{
		return dir.mkpath(".");
	}

	return true;
}
