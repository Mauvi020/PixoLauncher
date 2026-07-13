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

#include <QObject>
#include <QProcess>
#include <QString>

class LabyModInstaller : public QObject
{
    Q_OBJECT

public:
    explicit LabyModInstaller(QObject* parent = nullptr);
    
    void launchInstaller();
    void setInstallerPath(const QString& path);
    QString getInstallerPath() const;
    
    bool isInstallerAvailable() const;

signals:
    void installerStarted();
    void installerFinished(int exitCode);
    void installerError(const QString& error);

private:
    QString m_installerPath;
    QProcess* m_process;
    
    void initializeProcess();
};