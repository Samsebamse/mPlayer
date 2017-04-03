#ifndef MPLAYER_H
#define MPLAYER_H

#include <QMainWindow>
#include <QDebug>
#include <QFileSystemModel>
#include <Qstring>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSlider>
#include <Qtime>

namespace Ui {
class mPlayer;
}

class mPlayer : public QMainWindow{
    Q_OBJECT


private:
    Ui::mPlayer *ui;
    QFileSystemModel *filemanager;
    QMediaPlayer *player;
    QModelIndex *index;


public:
    explicit mPlayer(QWidget *parent = 0);
    ~mPlayer();

    bool playing = false;

    qint64 position;
    QString currentpath;
    QString songinfo;
    QTime durationTime;
    QTime currentTime;


private slots:

    void on_treeView_clicked(QModelIndex index);

    void on_buttonPlay_toggled(bool playing);

    void loadSong(qint64 position);

    void currentValue(qint64 position);

    void on_sliderVolume_sliderMoved(int position);

    void on_sliderProgress_sliderMoved(int position);

};

#endif // MPLAYER_H
