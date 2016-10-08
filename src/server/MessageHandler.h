/* GComprisServer - MessageHandler.h
 *
 * Copyright (C) 2016 Johnny Jazeix <jazeix@gmail.com>
 *
 * Authors:
 *   Johnny Jazeix <jazeix@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "Messages.h"
#include "ClientData.h"
#include "GroupData.h"
#include "UserData.h"
#include <QObject>
#include <QtQml>

class MessageHandler: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> clients MEMBER m_clients NOTIFY newClients)
    Q_PROPERTY(QList<QObject*> groups MEMBER m_groups NOTIFY newGroups)
    Q_PROPERTY(QList<QObject*> users MEMBER m_users NOTIFY newUsers)

private:
    MessageHandler();  // prohibit external creation, we are a singleton!
    static MessageHandler* _instance;  // singleton instance
    
public:
    /**
     * Registers MessageHandler singleton in the QML engine.
     */
    static void init();
    static QObject *systeminfoProvider(QQmlEngine *engine,
            QJSEngine *scriptEngine);
    static MessageHandler* getInstance();

    Q_INVOKABLE GroupData *createGroup(const QString &groupName, const QStringList &users = QStringList());
    Q_INVOKABLE GroupData *updateGroup(const QString &oldGroupName, const QString &newGroupName, const QStringList &users = QStringList());
    Q_INVOKABLE void deleteGroup(const QString &groupName);

    Q_INVOKABLE UserData *createUser(const QString &userName, const QString &avatar = QString(), const QStringList &groups = QStringList());
    Q_INVOKABLE UserData *updateUser(const QString &oldUser, const QString &newUser, const QString &avatar = QString(), const QStringList &groups = QStringList());
    Q_INVOKABLE void deleteUser(const QString &userName);

    UserData *getUser(const QString &userName);
    GroupData *getGroup(const QString &groupName);

public slots:
    void onLoginReceived(const ClientData &who, const Login &data);
    void onActivityDataReceived(const ClientData &who, const ActivityRawData &act);
    void onNewClientReceived(const ClientData &client);
    void onClientDisconnected(const ClientData &client);

signals:
    void newClients();
    void newGroups();
    void newUsers();

private:
    ClientData *getClientData(const ClientData &cd);

    void removeUserFromAllGroups(UserData *user);

    // ClientData*
    QList<QObject*> m_clients;
    // GroupData*
    QList<QObject*> m_groups;
    // UserData*
    QList<QObject*> m_users;

};

#endif