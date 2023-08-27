/*
 *   SPDX-FileCopyrightText: 2008-2011 Dario Freddi <drf@kde.org>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <PowerDevilProfileSettings.h>

#include <QWidget>

#include <KSharedConfig>

#include "powerdevilconfigcommonprivate_export.h"

namespace PowerDevil
{
class ActionConfig;
}

class QCheckBox;
class KConfigGroup;

class POWERDEVILCONFIGCOMMONPRIVATE_EXPORT ActionEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ActionEditWidget(const QString &configName, std::unique_ptr<PowerDevil::ProfileSettings> profileSettings, QWidget *parent = nullptr);
    ~ActionEditWidget() override;

    QString configName() const;

public Q_SLOTS:
    void load();
    void save();
    void setDefaults();

private Q_SLOTS:
    void onChanged();

Q_SIGNALS:
    void changed(bool changed);

private:
    KConfigGroup configGroup();

private:
    QString m_configName;
    std::unique_ptr<PowerDevil::ProfileSettings> m_profileSettings;
    QHash<QString, QCheckBox *> m_actionsHash;
    QHash<QString, PowerDevil::ActionConfig *> m_actionsConfigHash;
};
