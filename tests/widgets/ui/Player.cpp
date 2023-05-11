/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "core/Audio.h"
#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#include "Player.h"
#include "ui_Player.h"

Player::Player(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Player)
{
    ui->setupUi(this);

    if (!VlcInstance::globalInstance()->status())
        return;

    _player = new VlcMediaPlayer(this);
    _player->setVideoWidget(ui->video);

    ui->video->setMediaPlayer(_player);
    ui->volume->setMediaPlayer(_player);
    ui->volume->setVolume(50);
    ui->seek->setMediaPlayer(_player);

    connect(ui->pause, SIGNAL(toggled(bool)), _player, SLOT(togglePause()));
    connect(ui->stop, SIGNAL(clicked()), _player, SLOT(stop()));

    _media = new VlcMedia("f:/Home.Coming.2022.WEB-DL.4K.DoVi.H.265.10bit.DDP.5.1-CTRLTV.mp4", true, this);
    _player->open(_media);
}

Player::~Player()
{
    if (VlcInstance::globalInstance()->status()) {
        _player->stop();

        delete _media;
        delete _player;
    }
    delete ui;
}
