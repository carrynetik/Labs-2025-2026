#ifndef SHIELD_H
#define SHIELD_H

#include <QString>
#include "inc.h"

struct Shield {
    QString title;        // Название
    QString description;  // Описание
    double defense;       // Коэффициент защиты
    QString type;         // Тип защиты

    // Проверка на "битость"
    bool isValid() const {
        if (title.isEmpty() || description.isEmpty() || type.isEmpty()) return false;
        if (defense <= 0) return false;
        return true;
    }

    // Перевод в JSON
    json to_json() const {
        return {
            {"name", title.toStdString()},
            {"desc", description.toStdString()},
            {"coef", defense},
            {"type", type.toStdString()}
        };
    }

    // Загрузка из JSON
    static Shield from_json(const json& j) {
        Shield s;
        if (j.contains("name")) s.title = QString::fromStdString(j["name"]);
        if (j.contains("desc")) s.description = QString::fromStdString(j["desc"]);
        if (j.contains("coef")) s.defense = j["coef"];
        if (j.contains("type")) s.type = QString::fromStdString(j["type"]);
        return s;
    }
};

#endif // SHIELD_H