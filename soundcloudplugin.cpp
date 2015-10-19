#include "soundcloudplugin.h"

#include "settings.h"
#include "webview.h"
#include "cookiejar.h"
#include "networkaccessmanager.h"
#include "abstractsearchdialog.h"

#include <QDesktopServices>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWebView>

#include <QtDebug>

SoundCloudPlugin::SoundCloudPlugin()
	: QObject()
	, _searchDialog(nullptr)
	, _artists(nullptr)
	, _albums(nullptr)
	, _tracks(nullptr)
	, _checkBox(nullptr)
	, _soundCloudWebPlayer(new SoundCloudWebPlayer(this))
{
	NetworkAccessManager *nam = NetworkAccessManager::getInstance();
	nam->setCookieJar(new CookieJar);

	// Dispatch replies: search for something, get artist info, get tracks from album, get track info
	connect(nam, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
		QNetworkRequest request = reply->request();
		// qDebug() << request.url();
		QByteArray ba = reply->readAll();
		QXmlStreamReader xml(ba);
		if (request.url().toDisplayString().startsWith("http://api.soundcloud.com/")) {
			this->extractAlbum(xml);
		} else {
			this->searchRequestFinished(xml);
		}
	});

	QWebSettings *s = QWebSettings::globalSettings();
	/// XXX
	s->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
	s->setAttribute(QWebSettings::PluginsEnabled, true);
	s->setAttribute(QWebSettings::JavascriptEnabled, true);
	s->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
	s->setAttribute(QWebSettings::JavascriptCanCloseWindows, true);
	s->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
	s->setAttribute(QWebSettings::LocalStorageEnabled, true);
	s->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
	s->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
	s->setThirdPartyCookiePolicy(QWebSettings::AlwaysAllowThirdPartyCookies);
}

SoundCloudPlugin::~SoundCloudPlugin()
{
	qDebug() << Q_FUNC_INFO;
	foreach (QWebView *view, _pages) {
		delete view;
		view = nullptr;
	}
	_pages.clear();
	delete _checkBox;
}

/** Redefined from BasicPlugin. */
QWidget* SoundCloudPlugin::configPage()
{
	QWidget *widget = new QWidget();
	_config.setupUi(widget);

	Settings *settings = Settings::instance();
	bool b = settings->value("SoundCloudPlugin/save").toBool();
	_config.saveCredentialsCheckBox->setChecked(b);
	if (b) {
		QByteArray lba = settings->value("SoundCloudPlugin/l").toByteArray();
		QByteArray pba = settings->value("SoundCloudPlugin/p").toByteArray();
		_config.loginLineEdit->setText(QByteArray::fromBase64(lba));
		_config.passwordLineEdit->setText(QByteArray::fromBase64(pba));
	}

	connect(_config.saveCredentialsCheckBox, &QCheckBox::toggled, this, &SoundCloudPlugin::saveCredentials);
	connect(_config.openConnectPopup, &QPushButton::clicked, this, &SoundCloudPlugin::login);
	_config.soundCloudLogo->installEventFilter(this);
	return widget;
}

IMediaPlayer* SoundCloudPlugin::player() const
{
	return nullptr;
}

/** Redefined from RemoteMediaPlayerPlugin. */
void SoundCloudPlugin::setSearchDialog(AbstractSearchDialog *w)
{
	_checkBox = new QCheckBox;
	_checkBox->setChecked(true);
	_checkBox->setText("SoundCloud");
	connect(w, &AbstractSearchDialog::aboutToSearch, this, &SoundCloudPlugin::search);
	connect(this, &SoundCloudPlugin::searchComplete, w, &AbstractSearchDialog::processResults);
	connect(this, &SoundCloudPlugin::aboutToProcessRemoteTracks, w, &AbstractSearchDialog::aboutToProcessRemoteTracks);

	_searchDialog = w;
	_searchDialog->addSource(_checkBox);
	_artists = w->artists();
	_albums = w->albums();
	_tracks = w->tracks();

	connect(_artists, &QListView::doubleClicked, this, &SoundCloudPlugin::artistWasDoubleClicked);
	connect(_albums, &QListView::doubleClicked, this, &SoundCloudPlugin::albumWasDoubleClicked);
	connect(_tracks, &QListView::doubleClicked, this, &SoundCloudPlugin::trackWasDoubleClicked);
}

/** Redefined from RemoteMediaPlayerPlugin. */
void SoundCloudPlugin::sync(const QString &token) const
{
	qDebug() << Q_FUNC_INFO << "not yet implemented" << token;
}

/** Redefined from QObject. */
bool SoundCloudPlugin::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == _config.soundCloudLogo && event->type() == QEvent::MouseButtonPress) {
		QDesktopServices::openUrl(QUrl("http://www.soundcloud.com"));
		return true;
	} else if (event->type() == QEvent::Show) {
		return true;
	} else {
		return QObject::eventFilter(obj, event);
	}
}

void SoundCloudPlugin::extractAlbum(QXmlStreamReader &)
{
	qDebug() << Q_FUNC_INFO << "not implemented";
}

void SoundCloudPlugin::searchRequestFinished(QXmlStreamReader &)
{
	qDebug() << Q_FUNC_INFO << "not implemented";
}

void SoundCloudPlugin::artistWasDoubleClicked(const QModelIndex &)
{
	qDebug() << Q_FUNC_INFO << "not implemented";
}

void SoundCloudPlugin::albumWasDoubleClicked(const QModelIndex &)
{
	qDebug() << Q_FUNC_INFO << "not implemented";
}

void SoundCloudPlugin::trackWasDoubleClicked(const QModelIndex &)
{
	qDebug() << Q_FUNC_INFO << "not implemented";
}

void SoundCloudPlugin::search(const QString &)
{
	qDebug() << Q_FUNC_INFO << "not implemented";
}

void SoundCloudPlugin::saveCredentials(bool enabled)
{
	Settings *settings = Settings::instance();
	if (enabled) {
		QByteArray lba(_config.loginLineEdit->text().toStdString().data());
		QByteArray pba(_config.passwordLineEdit->text().toStdString().data());
		settings->setValue("SoundCloudPlugin/l", lba.toBase64());
		settings->setValue("SoundCloudPlugin/p", pba.toBase64());
		settings->setValue("SoundCloudPlugin/save", enabled);
	} else {
		settings->remove("SoundCloudPlugin/l");
		settings->remove("SoundCloudPlugin/p");
		settings->remove("SoundCloudPlugin/save");
	}
}

void SoundCloudPlugin::login()
{
	qDebug() << Q_FUNC_INFO;
	WebView *webView = new WebView;
	webView->installEventFilter(this);
	webView->loadUrl(QUrl("https://soundcloud.com/connect?redirect_uri=http://www.miam-player.org/soundcloud-micro/callback.html"));
	webView->show();
	_pages.append(webView);
}
