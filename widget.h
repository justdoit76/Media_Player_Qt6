#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class QListWidgetItem;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private:
    Ui::Widget *ui;
    Player player;
    QString secToHMS(int);
    QStringList list;

// signal이 발생시 호출되는 함수 slot
private slots:
    void onAdd();
    void onDel();

    void onPlay();
    void onStop();
    void onFF();
    void onPrev();

    void onVolume(int);
    void onSP();
    void onSM(int);

    void onDBClick(QListWidgetItem*);

public slots:
    void onDC(int);
    void onPC(int);

};
#endif // WIDGET_H
