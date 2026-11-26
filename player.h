#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QStringList>

class Widget;

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(Widget *p = nullptr);
    ~Player();

    void setVideoWidget(QObject* pv);

    void onAdd(const QStringList&);
    void onDel(int row);

    void onPlay(int = 0);
    void onStop();
    void onFF(int = 0);
    void onPrev(int = 0);
    void onVolume(int v);

    void setPosition(int);
    inline void setPause() {player.pause();}

private:
    Widget* pw;
    QMediaPlayer player;
    QAudioOutput ao;
    QStringList* plist;

signals:
    void dc_signal(int);
    void pc_signal(int);

private slots:
    void onDC(int);
    void onPC(int);
};

#endif // PLAYER_H
