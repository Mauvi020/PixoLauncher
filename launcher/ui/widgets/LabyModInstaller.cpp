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

#include "LabyModInstaller.h"
#include <QFileInfo>
#include <QDir>
#include <QStandardPaths>
#include "Application.h"
#include <FileSystem.h>

LabyModInstaller::LabyModInstaller(QObject* parent)
    : QObject(parent)
{
    initializeProcess();
    
    // Set default installer path
    QString defaultPath = FS::PathCombine(QCoreApplication::applicationDirPath(), "PIXOLAUNCHER", "labymod4-installer.jar");
    if (!QFileInfo::exists(defaultPath)) {
        // Try alternative paths
        defaultPath = FS::PathCombine(QCoreApplication::applicationDirPath(), "labymod4-installer.jar");
    }
    setInstallerPath(defaultPath);
}

void LabyModInstaller::initializeProcess()
{
    m_process = new QProcess(this);
    
    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
                Q_UNUSED(exitStatus);
                emit installerFinished(exitCode);
            });
    
    connect(m_process, &QProcess::errorOccurred,
            this, [this](QProcess::ProcessError error) {
                Q_UNUSED(error);
                emit installerError(m_process->errorString());
            });
}

void LabyModInstaller::launchInstaller()
{
    if (!isInstallerAvailable()) {
        emit installerError("LabyMod installer JAR file not found");
        return;
    }
    
    // Get Java path from settings
    QString javaPath = APPLICATION->settings()->get("JavaPath").toString();
    if (javaPath.isEmpty()) {
        emit installerError("Java path not configured");
        return;
    }
    
    QStringList arguments;
    arguments << "-jar" << m_installerPath;
    
    m_process->start(javaPath, arguments);
    
    if (m_process->waitForStarted()) {
        emit installerStarted();
    } else {
        emit installerError("Failed to start LabyMod installer");
    }
}

void LabyModInstaller::setInstallerPath(const QString& path)
{
    m_installerPath = path;
}

QString LabyModInstaller::getInstallerPath() const
{
    return m_installerPath;
}

bool LabyModInstaller::isInstallerAvailable() const
{
    return QFileInfo::exists(m_installerPath);
}