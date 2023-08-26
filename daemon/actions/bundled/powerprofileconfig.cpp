/*
 * SPDX-FileCopyrightText: 2020 Kai Uwe Broulik <kde@broulik.de>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#include "powerprofileconfig.h"

#include "powerdevilpowermanagement.h"

#include <QComboBox>
#include <QDBusConnection>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>

#include <KConfig>
#include <KLocalizedString>
#include <KPluginFactory>
#include <KSharedConfig>

K_PLUGIN_CLASS(PowerDevil::BundledActions::PowerProfileConfig)

using namespace PowerDevil::BundledActions;

PowerProfileConfig::PowerProfileConfig(QObject *parent)
    : ActionConfig(parent)
{
}

void PowerProfileConfig::save()
{
    const QString profile = m_profileCombo->currentData().toString();
    configGroup().writeEntry("profile", profile);

    configGroup().sync();
}

void PowerProfileConfig::load()
{
    configGroup().config()->reparseConfiguration();

    const QString profile = configGroup().readEntry("profile", QString());
    if (m_profileCombo) {
        m_profileCombo->setCurrentIndex(qMax(0, m_profileCombo->findData(profile)));
    }
}

QList<QPair<QString, QWidget *>> PowerProfileConfig::buildUi()
{
    m_profileCombo = new QComboBox;
    // Uniform ComboBox width throughout all action config modules
    m_profileCombo->setMinimumWidth(300);
    m_profileCombo->setMaximumWidth(300);
    connect(m_profileCombo, QOverload<int>::of(&QComboBox::activated), this, &PowerProfileConfig::setChanged);

    QDBusMessage msg = QDBusMessage::createMethodCall(QStringLiteral("org.kde.Solid.PowerManagement"),
                                                      QStringLiteral("/org/kde/Solid/PowerManagement/Actions/PowerProfile"),
                                                      QStringLiteral("org.kde.Solid.PowerManagement.Actions.PowerProfile"),
                                                      QStringLiteral("profileChoices"));

    auto *watcher = new QDBusPendingCallWatcher(QDBusConnection::sessionBus().asyncCall(msg), m_profileCombo);
    QObject::connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<QStringList> reply = *watcher;
        watcher->deleteLater();

        m_profileCombo->clear();
        m_profileCombo->addItem(i18n("Leave unchanged"));

        if (reply.isError()) {
            qWarning() << "Failed to query platform profile choices" << reply.error().message();
            return;
        }

        const QHash<QString, QString> profileNames = {
            {QStringLiteral("power-saver"), i18n("Power Save")},
            {QStringLiteral("balanced"), i18n("Balanced")},
            {QStringLiteral("performance"), i18n("Performance")},
        };

        const QStringList choices = reply.value();
        for (const QString &choice : choices) {
            m_profileCombo->addItem(profileNames.value(choice, choice), choice);
        }

        if (configGroup().isValid()) {
            const QString profile = configGroup().readEntry("profile", QString());
            m_profileCombo->setCurrentIndex(qMax(0, m_profileCombo->findData(profile)));
        }
    });

    return {qMakePair<QString, QWidget *>(i18nc("Switch to power management profile", "Switch to:"), m_profileCombo)};
}

#include "powerprofileconfig.moc"

#include "moc_powerprofileconfig.cpp"
