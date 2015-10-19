#ifndef SOUNDCLOUDWEBPLAYER_H
#define SOUNDCLOUDWEBPLAYER_H

#include "imediaplayer.h"

class SoundCloudWebPlayer : public IMediaPlayer
{
	Q_OBJECT
public:
	SoundCloudWebPlayer(QObject *parent = nullptr);

	virtual QString host() const { return "https://soundclound.com"; }

	/** Current media length in ms. */
	virtual qint64 duration() const;

	/** The position in the current media being played. Percent-based. */
	virtual qreal position() const;

	virtual void setMute(bool b);

	/** Sets the current position in ms in the current media being played (useful for seeking). */
	virtual void setPosition(qint64 pos);

	/** Sets the total time in ms in the current media being played (useful for seeking). */
	virtual void setTime(qint64 t);
	virtual qint64 time() const;

	/** The current volume of this remote player. */
	virtual qreal volume() const;

public slots:
	/// Must be implemented in derived class
	virtual void pause();
	virtual void play(const QUrl &track);
	virtual void resume();
	virtual void seek(float pos);
	virtual void setVolume(qreal volume);
	virtual void stop();
};

#endif // SOUNDCLOUDWEBPLAYER_H
