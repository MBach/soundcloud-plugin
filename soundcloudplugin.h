#ifndef SOUNDCLOUDPLUGIN_H
#define SOUNDCLOUDPLUGIN_H

#include "miamcore_global.h"
#include "interfaces/remotemediaplayerplugin.h"
#include "abstractsearchdialog.h"
#include "mediaplayer.h"

#include <QNetworkReply>
#include <QXmlStreamReader>
#include "ui_config.h"

#include "soundcloudwebplayer.h"

class QWebView;

/**
 * \brief       SoundCloud plugin
 * \author      Matthieu Bachelier
 * \version     0.1
 * \copyright   GNU General Public License v3
 */
class SoundCloudPlugin : public QObject, public RemoteMediaPlayerPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID RemoteMediaPlayerPlugin_iid)
	Q_INTERFACES(RemoteMediaPlayerPlugin)

private:
	Ui::SoundCloudPluginConfigPage _config;

	AbstractSearchDialog* _searchDialog;
	QList<QWebView*> _pages;
	QListView *_artists;
	QListView *_albums;
	QListView *_tracks;
	QCheckBox *_checkBox;

	SoundCloudWebPlayer *_soundCloudWebPlayer;

public:
	explicit SoundCloudPlugin();

	virtual ~SoundCloudPlugin();

	/** Redefined from BasicPlugin. */
	virtual QWidget* configPage() override;

	/** Redefined from BasicPlugin. */
	inline virtual bool isConfigurable() const override { return true; }

	/** Redefined from BasicPlugin. */
	inline virtual QString name() const override { return "SoundCloud"; }

	/** Redefined from BasicPlugin. */
	inline virtual QString version() const override { return "0.1"; }

	/** Redefined from RemoteMediaPlayerPlugin. */
	virtual IMediaPlayer * player() const override;

	/** Redefined from RemoteMediaPlayerPlugin. */
	virtual void setSearchDialog(AbstractSearchDialog *w) override;

	/** Redefined from RemoteMediaPlayerPlugin. */
	virtual void sync(const QString &token) const override;

protected:
	/** Redefined from QObject. */
	virtual bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
	void login();
	void extractAlbum(QXmlStreamReader &xml);
	void searchRequestFinished(QXmlStreamReader &xml);
	void saveCredentials(bool enabled);
	void search(const QString &expr);

	void artistWasDoubleClicked(const QModelIndex &index);
	void albumWasDoubleClicked(const QModelIndex &index);
	void trackWasDoubleClicked(const QModelIndex &index);

signals:
	void searchComplete(AbstractSearchDialog::Request, QList<QStandardItem*> results);
	void aboutToProcessRemoteTracks(const std::list<TrackDAO> &tracks);
};

#endif // SOUNDCLOUDPLUGIN_H
