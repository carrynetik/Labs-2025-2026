#include "book.h"
#include <string>

book::book(QString& author, QString& name, QString& code, QString& contents, QString& type, std::vector<QString>& genres) {
    m_author = author;
    m_name = name;
    m_code = code;
    m_contents = contents;
    m_type = type;
    m_genres = genres;
}

void book::write_to_file() {
    std::ofstream fileOut("result.txt");
    fileOut << "Автор: " << m_author.toStdString() << "\n"
            << "Название: " << m_name.toStdString() << "\n"
            << "Код: " << m_code.toStdString() << "\n"
            << "Наполнение: " << m_contents.toStdString() << "\n"
            << "Тип: " << m_type.toStdString() << "\n"
            << "Жанры: ";
    
    if (m_genres.empty()) {
        fileOut << "Нет";
        return;
    }
    
    for (size_t i = 0; i < m_genres.size(); ++i) {
        fileOut << m_genres[i].toStdString();
        if (i != m_genres.size() - 1) {
            fileOut << ", ";
        }
    }
}
