#include "player.h"
#include "widget.h"

Player::Player(Widget* p) : QObject{p}, pw(p), plist(nullptr)
{
    player.setAudioOutput(&ao);

    connect(&player, &QMediaPlayer::durationChanged, this, &Player::onDC);
    connect(&player, &QMediaPlayer::positionChanged, this, &Player::onPC);

    connect(this, &Player::dc_signal, p, &Widget::onDC);
    connect(this, &Player::pc_signal, p, &Widget::onPC);
}

Player::~Player()
{
    if (plist)
    {
        delete plist;
        plist = nullptr;
    }
}

void Player::setPosition(int v)
{
    player.setPosition(v);
}

void Player::onDC(int v)
{
    //qDebug() << v;
    emit dc_signal(v);
}

void Player::onPC(int v)
{
    emit pc_signal(v);
}


void Player::onVolume(int v)
{
    ao.setVolume(v/100.0);
}

void Player::setVideoWidget(QObject* pv)
{
    player.setVideoOutput(pv);
}

void Player::onAdd(const QStringList& lst)
{
    if(plist)
    {
        delete plist;
        plist = nullptr;
    }

    plist = new QStringList(lst);    
}

void Player::onDel(int row)
{
    if(plist)
    {
        plist->removeAt(row);
    }
}

void Player::onPlay(int idx)
{
    if(plist)
    {
        if(player.position()==0)
        {
            QUrl url = QUrl(plist->at(idx));
            player.setSource(url);
        }

        player.play();
    }
}

void Player::onStop()
{
    player.stop();
}

void Player::onFF(int idx)
{
    onPlay(idx);
}

void Player::onPrev(int idx)
{
    onPlay(idx);
}







