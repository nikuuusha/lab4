#include <iostream>
#include <string>
using namespace std;

int main() {
    setlocale(0, "");
    std::string input;
    std::cout << "Введите последовательность слов: ";
    std::getline(std::cin, input);

    // Удаляем лишние пробелы
    std::string cleanedInput;
    for (char c : input) {
        if (!std::isspace(c) || (cleanedInput.empty() || !std::isspace(cleanedInput.back()))) {
            cleanedInput += c;
        }
    }

    // Удаляем лишние знаки препинания
    std::string punctuation = ".,;:-!?";
    std::string punctuationFreeInput;
    for (char c : cleanedInput) {
        if (!std::ispunct(c) || punctuationFreeInput.empty() || punctuation.find(punctuationFreeInput.back()) == std::string::npos) {
            punctuationFreeInput += c;
        }
    }

    // Исправляем регистр букв
    std::string correctedInput;
    for (char c : punctuationFreeInput) {
        if (std::isalpha(c)) {
            correctedInput += std::tolower(c);
        }
        else {
            correctedInput += c;
        }
    }

    // Выводим слова последовательности, не содержащие цифр
    std::string word;
    std::cout << "Слова без цифр: ";
    for (char c : correctedInput) {
        if (std::isalnum(c)) {
            word += c;
        }
        else {
            if (!word.empty() && word.find_first_of("0123456789") == std::string::npos) {
                std::cout << word << " ";
            }
            word.clear();
        }
    }
    if (!word.empty() && word.find_first_of("0123456789") == std::string::npos) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    // Удаляем из всех слов заданный набор букв и цифр
    std::string charsToRemove = "aeiou12345";
    std::string cleanedWords;
    word.clear();
    for (char c : correctedInput) {
        if (std::isalnum(c)) {
            if (charsToRemove.find(c) == std::string::npos) {
                word += c;
            }
        }
        else {
            if (!word.empty()) {
                cleanedWords += word + " ";
            }
            word.clear();
        }
    }
    if (!word.empty()) {
        cleanedWords += word + " ";
    }
    std::cout << "Слова после удаления символов: " << cleanedWords << std::endl;

    // Находим все подстроки
    std::string substring;
    std::cout << "Введите подстроку для поиска: ";
    std::cin >> substring;

    // Линейный поиск
    std::cout << "Результат линейного поиска: ";
    size_t pos = correctedInput.find(substring);
    while (pos != std::string::npos) {
        std::cout << "Найдено на позиции " << pos << std::endl;
        pos = correctedInput.find(substring, pos + 1);
    }

    // Бойера-Мура
    std::cout << "Результат поиска Бойера-Мура: ";
    int last[256] = {};
    for (size_t i = 0; i < substring.length() - 1; i++) {
        last[substring[i]] = i;
    }
    size_t index = 0;
    while (index <= correctedInput.length() - substring.length()) {
        int j = substring.length() - 1;
        while (j >= 0 && substring[j] == correctedInput[index + j]) {
            j--;
        }
        if (j < 0) {
            std::cout << "Найдено на позиции " << index << std::endl;
            index++;
        }
        else {
            index += std::max(1, int(j - last[correctedInput[index + j]]));
        }
    }

    return 0;
}
