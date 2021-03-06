#ifndef MIAMCORE_GLOBAL_H
#define MIAMCORE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QMessageBox>

#ifdef MIAM_PLUGIN
# define MIAMCORE_LIBRARY Q_DECL_EXPORT
#else
# define MIAMCORE_LIBRARY Q_DECL_IMPORT
#endif

#include <QMetaType>
#include <QObject>

class MIAMCORE_LIBRARY Miam : public QObject
{
	Q_OBJECT
private:
	Q_ENUMS(ItemType)
	Q_ENUMS(DataField)

public:
	enum ItemType : int
	{
		IT_Artist		= QMetaType::User + 1,
		IT_Album		= QMetaType::User + 2,
		IT_ArtistAlbum	= QMetaType::User + 3,
		IT_Disc			= QMetaType::User + 4,
		IT_Separator	= QMetaType::User + 5,
		IT_Track		= QMetaType::User + 6,
		IT_Year			= QMetaType::User + 7,
		IT_Playlist		= QMetaType::User + 8,
		IT_UnknownType	= QMetaType::User + 9,
		IT_Cover		= QMetaType::User + 10
	};

	// User defined data types (item->setData(QVariant, Field);)
	enum DataField : int
	{
		DF_URI					= Qt::UserRole + 1,
		DF_CoverPath			= Qt::UserRole + 2,
		DF_TrackNumber			= Qt::UserRole + 3,
		DF_DiscNumber			= Qt::UserRole + 4,
		DF_NormalizedString		= Qt::UserRole + 5,
		DF_Year					= Qt::UserRole + 6,
		DF_Highlighted			= Qt::UserRole + 7,
		DF_IsRemote				= Qt::UserRole + 8,
		DF_IconPath				= Qt::UserRole + 9,
		DF_Rating				= Qt::UserRole + 10,
		DF_CustomDisplayText	= Qt::UserRole + 11,
		DF_NormArtist			= Qt::UserRole + 12,
		DF_NormAlbum			= Qt::UserRole + 13,
		DF_Disc					= Qt::UserRole + 14,
		DF_TrackLength			= Qt::UserRole + 15,
		DF_CurrentPosition		= Qt::UserRole + 16
	};

	enum TagEditorColumns : int
	{
		COL_Filename	= 0,
		COL_Path		= 1,
		COL_Title		= 2,
		COL_Artist		= 3,
		COL_ArtistAlbum	= 4,
		COL_Album		= 5,
		COL_Track		= 6,
		COL_Disc		= 7,
		COL_Year		= 8,
		COL_Genre		= 9,
		COL_Comment		= 10
	};

	inline static QMessageBox::StandardButton showWarning(const QString &target, int count)
	{
		QMessageBox::StandardButton ret = QMessageBox::Ok;
		/// XXX: extract magic number (to where?)
		if (count > 300) {
			QMessageBox msgBox;
			QString totalFiles = tr("There are more than 300 files to add to the %1 (%2 to add).");
			msgBox.setText(totalFiles.arg(target).arg(count));
			msgBox.setInformativeText(tr("Are you sure you want to continue? This might take some time."));
			msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Ok);
			ret = (QMessageBox::StandardButton) msgBox.exec();
		}
		return ret;
	}
};

#endif // MIAMCORE_GLOBAL_H
