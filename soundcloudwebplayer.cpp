#include "soundcloudwebplayer.h"

#include <QtDebug>

SoundCloudWebPlayer::SoundCloudWebPlayer(QObject *parent)
	: IMediaPlayer(parent)
{

}

qint64 SoundCloudWebPlayer::duration() const
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
	return 0;
}

qreal SoundCloudWebPlayer::position() const
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
	return 0.0;
}

void SoundCloudWebPlayer::setMute(bool)
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
}

void SoundCloudWebPlayer::setPosition(qint64)
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
}

void SoundCloudWebPlayer::setTime(qint64)
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
}

qint64 SoundCloudWebPlayer::time() const
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
	return 0;
}

qreal SoundCloudWebPlayer::volume() const
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
	return 0.0;
}


void SoundCloudWebPlayer::pause()
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
}

void SoundCloudWebPlayer::play(const QUrl &)
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
}

void SoundCloudWebPlayer::resume()
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
}

void SoundCloudWebPlayer::seek(float)
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
}

void SoundCloudWebPlayer::setVolume(qreal)
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
}

void SoundCloudWebPlayer::stop()
{
	qDebug() << Q_FUNC_INFO << "not yet implemented";
}
