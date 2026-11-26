#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget), player(this)
{
    ui->setupUi(this);
    setWindowTitle("Ocean Coding School");
    player.setVideoWidget(ui->view);

    ui->dial->setRange(0, 100);
    ui->dial->setValue(50);

    connect(ui->pb_add, &QPushButton::clicked, this, &Widget::onAdd);
    connect(ui->pb_del, &QPushButton::clicked, this, &Widget::onDel);    

    connect(ui->pb_play, &QPushButton::clicked, this, &Widget::onPlay);
    connect(ui->pb_stop, &QPushButton::clicked, this, &Widget::onStop);
    connect(ui->pb_ff, &QPushButton::clicked, this, &Widget::onFF);
    connect(ui->pb_prev, &QPushButton::clicked, this, &Widget::onPrev);

    connect(ui->dial, &QDial::valueChanged, this, &Widget::onVolume);
    connect(ui->hs, &QSlider::sliderPressed, this, &Widget::onSP);
    connect(ui->hs, &QSlider::sliderMoved, this, &Widget::onSM);

    connect(ui->lw, &QListWidget::itemDoubleClicked, this, &Widget::onDBClick);

    ui->pb_play->setCheckable(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onDBClick(QListWidgetItem * pitem)
{
    player.onStop();
    //ui->pb_play->setChecked(false);

    int row = ui->lw->currentRow();
    player.onPlay(row);
    ui->pb_play->setChecked(true);
    ui->pb_play->setText("▶");
}

void Widget::onSP()
{
    int v = ui->hs->value();
    player.setPosition(v);
}

void Widget::onSM(int v)
{
    player.setPosition(v);
}

QString Widget::secToHMS(int s)
{
    int n = s/1000;
    int h = n/3600;
    int m = (n%3600)/60;
    int sec = (n%3600)%60;

    QString time = QString::asprintf("%02d:%02d:%02d", h, m, sec);
    return time;
}

void Widget::onPC(int v)
{
    ui->hs->setValue(v);
    auto s = secToHMS(v);
    ui->pc->setText(s);
}

void Widget::onDC(int v)
{
    ui->hs->setRange(0, v);
    auto s = secToHMS(v);
    ui->dc->setText(QString("/ ")+s);
}

void Widget::onVolume(int v)
{
    //qDebug() << v;
    player.onVolume(v);
}

void Widget::onAdd()
{
    QStringList lst = QFileDialog::getOpenFileNames(this, "", "E:\\", QString("media files(*.mp3 *.mp4)"));
    if(!lst.empty())
    {
        list += lst;
        int crow = ui->lw->currentRow();
        ui->lw->clear();

        for(int i=0; i<list.count(); i++)
        {
            QString s = list[i];
            QStringList sl = s.split("/");
            int n = sl.count();
            ui->lw->addItem(sl[n-1]);
        }

        ui->lw->setCurrentRow(crow);
        player.onAdd(list);
    }
}

void Widget::onDel()
{
    int n = ui->lw->currentRow();
    if(n>=0)
    {
        ui->lw->takeItem(n);
        player.onDel(n);

        list.removeAt(n);
    }
}

void Widget::onPlay()
{
    if(ui->pb_play->isChecked())
    {
        ui->pb_play->setText("▶");

        int n = ui->lw->currentRow();
        if (n>=0)
            player.onPlay(n);
        else
        {
            ui->lw->setCurrentRow(0);
            player.onPlay(0);
        }
    }
    else
    {
        //일시정지
        player.setPause();
        ui->pb_play->setText("▮▮");
    }
}

void Widget::onStop()
{
    player.onStop();
    ui->pb_play->setChecked(false);
    ui->pb_play->setText("▶");
}

void Widget::onFF()
{
    player.onStop();
    //ui->pb_play->setChecked(false);

    int n = ui->lw->count();
    int row = ui->lw->currentRow();

    if(row==n-1)
        row = -1;

    player.onFF(row+1);
    ui->lw->setCurrentRow(row+1);
    ui->pb_play->setChecked(true);
    ui->pb_play->setText("▶");
}

void Widget::onPrev()
{
    player.onStop();
    //ui->pb_play->setChecked(false);

    int n = ui->lw->count();
    int row = ui->lw->currentRow();

    if(row==0)
        row = n;

    player.onPrev(row-1);
    ui->lw->setCurrentRow(row-1);
    ui->pb_play->setChecked(true);
    ui->pb_play->setText("▶");
}













