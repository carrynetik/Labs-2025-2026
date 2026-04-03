#pragma once
#include <QApplication>
#include <vector>
#include <fstream>

class book{
private:
    QString m_author;
    QString m_name;
    QString m_code;
    QString m_contents;
    QString m_type;
    std::vector<QString> m_genres;
public:
    book(QString& author, QString& name, QString& code, QString& contents, QString& type, std::vector<QString>& genres);
    void write_to_file();
};
