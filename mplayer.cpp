#include "mplayer.h"
#include "ui_mplayer.h"


mPlayer::mPlayer(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::mPlayer){

    ui->setupUi(this);
    filemanager = new QFileSystemModel(this);
    filemanager->setRootPath("C:/");
    ui->treeView->setModel(filemanager);
    ui->labelSonginfo->setText("HELLO THIS IS MY APP");

    player = new QMediaPlayer(this);

    player->setVolume(30);
    ui->labelVolume->setText("Volume: " + QString::number(30));
    ui->sliderVolume->setValue(30);

    connect(player, &QMediaPlayer::positionChanged, this, &mPlayer::currentValue);
    connect(player, &QMediaPlayer::durationChanged, this, &mPlayer::loadSong);
    connect(ui->sliderVolume, &QSlider::valueChanged, this, &mPlayer::on_sliderVolume_sliderMoved);

}

mPlayer::~mPlayer(){
    delete ui;
}

void mPlayer::on_treeView_clicked(QModelIndex index){

    currentpath = filemanager->fileInfo(index).absoluteFilePath();
    songinfo = filemanager->fileInfo(index).fileName();
    ui->labelSonginfo->setText(songinfo);
    player->setMedia(QUrl::fromLocalFile(currentpath));

}

void mPlayer::on_buttonPlay_toggled(bool playing){

    if(playing){
        player->play();
        ui->buttonPlay->setText("Playing");

    }
    else{
        player->pause();
        ui->buttonPlay->setText("Paused");     
    }

}

void mPlayer::loadSong(qint64 position){

    ui->sliderProgress->setMaximum(position);
    durationTime.setHMS(0,0,0,0);
    durationTime = durationTime.addMSecs(position);
    ui->labelSonglength->setText(durationTime.toString("mm:ss"));

}

void mPlayer::currentValue(qint64 position){

    ui->sliderProgress->setValue(position);
    currentTime.setHMS(0,0,0,0);
    currentTime = currentTime.addMSecs(position);
    ui->labelProgress->setText(currentTime.toString("mm:ss") + "  /");

    if(currentTime == durationTime && ui->buttonRepeat->isChecked()){
        mPlayer::on_buttonPlay_toggled(true);
    }

}

void mPlayer::on_sliderVolume_sliderMoved(int position){
    player->setVolume(position);
    ui->labelVolume->setText("Volume: " + QString::number(position));

}

void mPlayer::on_sliderProgress_sliderMoved(int position){

    player->setPosition(position);

}
