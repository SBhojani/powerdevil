/*
 *   SPDX-FileCopyrightText: 2010 Dario Freddi <drf@kde.org>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <powerdevilactionconfig.h>

class QSlider;
class QLabel;

namespace PowerDevil::BundledActions
{
class BrightnessControlConfig : public PowerDevil::ActionConfig
{
    Q_OBJECT
public:
    BrightnessControlConfig(QObject *);

    void save() override;
    void load() override;
    QList<QPair<QString, QWidget *>> buildUi() override;

private:
    QSlider *m_slider;
    QLabel *m_text;
};

}
