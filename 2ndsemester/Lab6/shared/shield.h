#ifndef SHIELD_H
#define SHIELD_H

#include <QString>
#include "inc.h"

struct Shield
{
    QString title;
    QString description;
    double defense = 0.0;
    QString type;

    bool isValid() const
    {
        if (title.trimmed().isEmpty()) {
            return false;
        }

        if (description.trimmed().isEmpty()) {
            return false;
        }

        if (type.trimmed().isEmpty()) {
            return false;
        }

        if (defense <= 0) {
            return false;
        }

        return true;
    }

    json to_json() const
    {
        return {
            {"name", title.toStdString()},
            {"desc", description.toStdString()},
            {"coef", defense},
            {"type", type.toStdString()}
        };
    }

    static Shield from_json(const json& object)
    {
        Shield shield;

        if (!object.is_object()) {
            return shield;
        }

        if (object.contains("name") &&
            object["name"].is_string()) {
            shield.title = QString::fromStdString(
                object["name"].get<std::string>()
            );
        }

        if (object.contains("desc") &&
            object["desc"].is_string()) {
            shield.description = QString::fromStdString(
                object["desc"].get<std::string>()
            );
        }

        if (object.contains("coef") &&
            object["coef"].is_number()) {
            shield.defense =
                object["coef"].get<double>();
        }

        if (object.contains("type") &&
            object["type"].is_string()) {
            shield.type = QString::fromStdString(
                object["type"].get<std::string>()
            );
        }

        return shield;
    }
};

#endif // SHIELD_H