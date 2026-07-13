// SPDX-License-Identifier: GPL-3.0-only
/*
 *  PixoLauncher - Minecraft Launcher
 *  Copyright (C) 2026 PixoLauncher Contributors
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ClientCard : public QWidget
{
    Q_OBJECT

public:
    enum ClientType {
        Vanilla,
        Fabric,
        Forge,
        NeoForge,
        LabyMod
    };

    explicit ClientCard(ClientType type, QWidget* parent = nullptr);
    
    void setTitle(const QString& title);
    void setDescription(const QString& description);
    void setLogo(const QString& logoPath);
    void setStatus(const QString& status);
    void setInstalled(bool installed);

signals:
    void installClicked();
    void updateClicked();
    void launchClicked();

private:
    void setupUI();
    void updateButtons();

    ClientType m_type;
    QString m_title;
    QString m_description;
    QString m_logoPath;
    QString m_status;
    bool m_installed = false;

    QLabel* m_logoLabel;
    QLabel* m_titleLabel;
    QLabel* m_descriptionLabel;
    QLabel* m_statusLabel;
    QPushButton* m_installButton;
    QPushButton* m_updateButton;
    QPushButton* m_launchButton;
};