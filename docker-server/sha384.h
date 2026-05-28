#ifndef SHA384_H
#define SHA384_H

#include <QString>

/**
 * @brief Класс для вычисления хэш-сумм алгоритмом SHA-384.
 *
 * Реализует криптографическую хэш-функцию SHA-384 для строк.
 * Используется для безопасного хранения паролей в базе данных.
 *
 * @author CryptoApp Team
 * @version 1.0
 */
class SHA384
{
public:
    /**
     * @brief Вычисляет SHA-384 хэш входной строки.
     *
     * @param input Входная строка в кодировке UTF-8
     * @return QString Хэш-сумма в виде шестнадцатеричной строки (96 символов)
     *
     * @example
     * QString hash = SHA384::hash("mypassword");
     */
    static QString hash(const QString& input);
};

#endif // SHA384_H