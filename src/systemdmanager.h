#ifndef SYSTEMDMANAGER_H
#define SYSTEMDMANAGER_H

#include <QObject>
#include <QStringList>
#include <QProcess>
#include <QVariantList>
#include <QMap>
#include <QRegularExpression>

class SystemdManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList serviceNames READ serviceNames NOTIFY servicesChanged)

public:
    explicit SystemdManager(QObject *parent = nullptr) : QObject(parent) {}

    QStringList serviceNames() {
        QStringList services;
        QProcess process;
        process.start("/usr/bin/systemctl", {"list-units", "--type=service", "--all", "--no-legend"});
        process.waitForFinished();
        
        QString output = process.readAllStandardOutput();
        QStringList lines = output.split("\n", Qt::SkipEmptyParts);
        
        for (const QString& line : lines) {
            QString trimmedLine = line.trimmed();
            QString name = trimmedLine.split(QRegularExpression("\\s+")).first();
            if (!name.isEmpty() && name.endsWith(".service")) {
                services << name;
            }
        }
        return services;
    }

    Q_INVOKABLE QVariantList getCategorizedServices() {
        QVariantList categories;
        QStringList all = serviceNames();

        QMap<QString, QStringList> mapping;
        mapping["Ağ ve Bağlantılar"] = {"network", "vpn", "proton", "warp", "bluetooth", "avahi", "wpa_supplicant"};
        mapping["Sistem Çekirdeği"] = {"tty", "udev", "dbus", "logind", "systemd-", "kernel", "mount"};
        mapping["Kullanıcı & Arayüz"] = {"user@", "sddm", "plasma", "polkit", "rtkit"};
        mapping["Donanım & Güç"] = {"upower", "thermald", "cpupower", "acpid", "nvidia"};

        for (auto it = mapping.begin(); it != mapping.end(); ++it) {
            QVariantMap category;
            category["title"] = it.key();
            QVariantList services;

            for (const QString& s : all) {
                bool belongs = false;
                for (const QString& key : it.value()) {
                    if (s.contains(key, Qt::CaseInsensitive)) { belongs = true; break; }
                }

                if (belongs) {
                    QVariantMap item;
                    item["rawName"] = s;
                    
                    QString pretty = s;
                    pretty.remove(".service").replace("-", " ").replace("@", " ");
                    if (!pretty.isEmpty()) pretty[0] = pretty[0].toUpper();
                    item["prettyName"] = pretty;

                    QProcess check;
                    check.start("systemctl", {"is-active", s});
                    check.waitForFinished();
                    item["isActive"] = (check.readAll().trimmed() == "active");

                    services << item;
                }
            }
            
            if (!services.isEmpty()) {
                category["services"] = services;
                categories << category;
            }
        }
        return categories;
    }

    Q_INVOKABLE void toggleService(QString name, bool start) {
        QString action = start ? "start" : "stop";
        QProcess::startDetached("systemctl", {action, name});
        emit servicesChanged();
    }

signals:
    void servicesChanged();
};

#endif
