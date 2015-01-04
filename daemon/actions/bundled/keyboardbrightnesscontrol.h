/***************************************************************************
 *   Copyright (C) 2012 by Michael Zanetti <mzanetti@kde.org>              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/


#ifndef POWERDEVIL_BUNDLEDACTIONS_KEYBOARDBRIGHTNESSCONTROL_H
#define POWERDEVIL_BUNDLEDACTIONS_KEYBOARDBRIGHTNESSCONTROL_H

#include <powerdevilaction.h>
#include <powerdevilbackendinterface.h>

namespace PowerDevil {
namespace BundledActions {

class KeyboardBrightnessControl : public PowerDevil::Action
{
    Q_OBJECT
    Q_DISABLE_COPY(KeyboardBrightnessControl)
    Q_CLASSINFO("D-Bus Interface", "org.kde.Solid.PowerManagement.Actions.KeyboardBrightnessControl")

public:
    explicit KeyboardBrightnessControl(QObject* parent);
    virtual ~KeyboardBrightnessControl();

protected:
    virtual void onProfileUnload();
    virtual void onWakeupFromIdle();
    virtual void onIdleTimeout(int msec);
    virtual void onProfileLoad();
    virtual void triggerImpl(const QVariantMap& args);
    virtual bool isSupported();

public:
    virtual bool loadAction(const KConfigGroup& config);

public Q_SLOTS:
    void onBrightnessChangedFromBackend(const BrightnessLogic::BrightnessInfo &brightnessInfo, BackendInterface::BrightnessControlType type);

    // DBus export
    void increaseKeyboardBrightness();
    void decreaseKeyboardBrightness();
    void toggleKeyboardBacklight();

    int keyboardBrightness() const;
    void setKeyboardBrightness(int percent);
    void setKeyboardBrightnessSilent(int percent);

    int keyboardBrightnessValue() const;
    int keyboardBrightnessValueMax() const;
    void setKeyboardBrightnessValue(int value);
    void setKeyboardBrightnessValueSilent(int value);

    int keyboardBrightnessStep() const;
    int keyboardBrightnessStepMax() const;
    void setKeyboardBrightnessStep(int step);

Q_SIGNALS:
    void keyboardBrightnessChanged(int percent);
    void keyboardBrightnessValueChanged(int value);
    void keyboardBrightnessStepChanged(int step);

private:
    int m_defaultValue;
    QString m_lastProfile;
    QString m_currentProfile;
};

}

}

#endif // POWERDEVIL_BUNDLEDACTIONS_KEYBOARDBRIGHTNESSCONTROL_H
