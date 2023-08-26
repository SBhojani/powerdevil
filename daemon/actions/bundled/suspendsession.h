/*
 *   SPDX-FileCopyrightText: 2010 Dario Freddi <drf@kde.org>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <powerdevilaction.h>
#include <powerdevilenums.h>

#include <QScopedPointer>

namespace PowerDevil
{
class KWinKScreenHelperEffect;

namespace BundledActions
{
class SuspendSession : public PowerDevil::Action
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.Solid.PowerManagement.Actions.SuspendSession")

public:
    explicit SuspendSession(QObject *parent);
    ~SuspendSession() override;

    bool loadAction(const KConfigGroup &config) override;

protected:
    void onProfileUnload() override;
    void onWakeupFromIdle() override;
    void onIdleTimeout(int msec) override;
    void onProfileLoad(const QString &previousProfile, const QString &newProfile) override;
    void triggerImpl(const QVariantMap &args) override;

public Q_SLOTS:
    void suspendToRam();
    void suspendToDisk();
    void suspendHybrid();

Q_SIGNALS:
    void aboutToSuspend();
    void resumingFromSuspend();

private Q_SLOTS:
    void triggerSuspendSession(PowerDevil::PowerButtonAction action);

private:
    bool m_suspendThenHibernateEnabled = false;
    int m_idleTime = 0;
    uint m_autoType;
    QVariantMap m_savedArgs;
    QScopedPointer<PowerDevil::KWinKScreenHelperEffect> m_fadeEffect;
};

}

}
