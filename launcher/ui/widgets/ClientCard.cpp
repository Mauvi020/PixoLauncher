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

#include "ClientCard.h"

#include <QPixmap>
#include <QSizePolicy>
#include <QStyle>
#include <QWidget>

ClientCard::ClientCard(ClientType type, QWidget* parent)
    : QWidget(parent), m_type(type)
{
    setupUI();
    
    // Set default values based on client type
    switch (type) {
        case Vanilla:
            setTitle("Vanilla");
            setDescription("The original Minecraft experience");
            setStatus("Not Installed");
            break;
        case Fabric:
            setTitle("Fabric");
            setDescription("Lightweight modding framework");
            setStatus("Not Installed");
            break;
        case Forge:
            setTitle("Forge");
            setDescription("Most popular modding platform");
            setStatus("Not Installed");
            break;
        case NeoForge:
            setTitle("NeoForge");
            setDescription("Next-generation Forge fork");
            setStatus("Not Installed");
            break;
        case LabyMod:
            setTitle("LabyMod");
            setDescription("Enhanced multiplayer experience");
            setStatus("Not Installed");
            break;
    }
}

void ClientCard::setupUI()
{
    setStyleSheet(R"(
        ClientCard {
            background-color: #2b2b2b;
            border-radius: 12px;
            padding: 16px;
        }
        ClientCard:hover {
            background-color: #3a3a3a;
        }
    )");
    
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(200);
    
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(12);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    
    // Logo and title row
    auto* headerLayout = new QHBoxLayout();
    
    m_logoLabel = new QLabel();
    m_logoLabel->setFixedSize(64, 64);
    m_logoLabel->setStyleSheet("background-color: #1e1e1e; border-radius: 8px;");
    m_logoLabel->setAlignment(Qt::AlignCenter);
    
    auto* textLayout = new QVBoxLayout();
    textLayout->setSpacing(4);
    
    m_titleLabel = new QLabel();
    m_titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #ffffff;");
    
    m_statusLabel = new QLabel();
    m_statusLabel->setStyleSheet("font-size: 12px; color: #888888;");
    
    textLayout->addWidget(m_titleLabel);
    textLayout->addWidget(m_statusLabel);
    
    headerLayout->addWidget(m_logoLabel);
    headerLayout->addLayout(textLayout);
    headerLayout->addStretch();
    
    mainLayout->addLayout(headerLayout);
    
    // Description
    m_descriptionLabel = new QLabel();
    m_descriptionLabel->setStyleSheet("font-size: 14px; color: #cccccc;");
    m_descriptionLabel->setWordWrap(true);
    mainLayout->addWidget(m_descriptionLabel);
    
    // Buttons
    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(8);
    
    m_installButton = new QPushButton("Install");
    m_installButton->setStyleSheet(R"(
        QPushButton {
            background-color: #4a90e2;
            color: #ffffff;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #357abd;
        }
        QPushButton:pressed {
            background-color: #2a5a8c;
        }
    )");
    
    m_updateButton = new QPushButton("Update");
    m_updateButton->setStyleSheet(R"(
        QPushButton {
            background-color: #f39c12;
            color: #ffffff;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #d68910;
        }
        QPushButton:pressed {
            background-color: #b97a0e;
        }
    )");
    m_updateButton->hide();
    
    m_launchButton = new QPushButton("Launch");
    m_launchButton->setStyleSheet(R"(
        QPushButton {
            background-color: #27ae60;
            color: #ffffff;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #219150;
        }
        QPushButton:pressed {
            background-color: #1e8449;
        }
    )");
    m_launchButton->hide();
    
    buttonLayout->addWidget(m_installButton);
    buttonLayout->addWidget(m_updateButton);
    buttonLayout->addWidget(m_launchButton);
    buttonLayout->addStretch();
    
    mainLayout->addLayout(buttonLayout);
    
    // Connect signals
    connect(m_installButton, &QPushButton::clicked, this, &ClientCard::installClicked);
    connect(m_updateButton, &QPushButton::clicked, this, &ClientCard::updateClicked);
    connect(m_launchButton, &QPushButton::clicked, this, &ClientCard::launchClicked);
    
    updateButtons();
}

void ClientCard::setTitle(const QString& title)
{
    m_title = title;
    m_titleLabel->setText(title);
}

void ClientCard::setDescription(const QString& description)
{
    m_description = description;
    m_descriptionLabel->setText(description);
}

void ClientCard::setLogo(const QString& logoPath)
{
    m_logoPath = logoPath;
    if (m_logoLabel) {
        QPixmap pixmap(logoPath);
        if (!pixmap.isNull()) {
            m_logoLabel->setPixmap(pixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            m_logoLabel->setText("?");
            m_logoLabel->setStyleSheet("background-color: #1e1e1e; border-radius: 8px; color: #ffffff; font-size: 24px;");
        }
    }
}

void ClientCard::setStatus(const QString& status)
{
    m_status = status;
    m_statusLabel->setText(status);
}

void ClientCard::setInstalled(bool installed)
{
    m_installed = installed;
    setStatus(installed ? "Installed" : "Not Installed");
    updateButtons();
}

void ClientCard::updateButtons()
{
    if (m_installed) {
        m_installButton->hide();
        m_updateButton->show();
        m_launchButton->show();
    } else {
        m_installButton->show();
        m_updateButton->hide();
        m_launchButton->hide();
    }
}