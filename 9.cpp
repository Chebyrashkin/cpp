/*
Определить комбинированный (структурный) тип для представления информации
по океаническим впадинам, состоящей из названия впадины, ее глубины, океане
местонахождения, типе впадины (разломная, хребет, желоб и др.). Ввести
информацию по 20 впадинам. Вывести минимальное и максимальное значение по
всем 20 впадинам. Затем вывести информацию по всем желобным впадинам,
отсортированную по убыванию глубины впадины (рационально переставлять все
поля структуры разом). Вывести сведения по океанам местонахождения 3-х
глубочайших впадин. Реализовать функцию изменения данных впадины по ее
глубине, а не по названию. В отдельный массив поместить все впадины одного
океана (океан вводить с клавиатуры). Реализовать вывод отфильтрованных данных
в виде оберточной функции.
*/




#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


enum TrenchType { RIFT, RIDGE, TRENCH, OTHERS };


struct Coordinates {
    double lat;
    double lon;
};


struct OceanTrench {
    string name;
    double depth;
    string ocean;
    TrenchType type;
    Coordinates coord;
};


void printTrench(const OceanTrench& t) {
    cout << t.name << ", глубина: " << t.depth << " м, океан: " << t.ocean << ", тип: ";
    switch(t.type) {
        case RIFT: cout << "разломная"; break;
        case RIDGE: cout << "хребет"; break;
        case TRENCH: cout << "желоб"; break;
        default: cout << "другой";
    }
    cout << ", координаты: (" << t.coord.lat << ", " << t.coord.lon << ")\n";
}


void findMinMaxDepth(const OceanTrench arr[], int size, double& minDepth, double& maxDepth) {
    minDepth = arr[0].depth;
    maxDepth = arr[0].depth;
    for (int i = 1; i < size; ++i) {
        if (arr[i].depth < minDepth) minDepth = arr[i].depth;
        if (arr[i].depth > maxDepth) maxDepth = arr[i].depth;
    }
}


void bubbleSortByDepth(OceanTrench arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j].depth < arr[j+1].depth) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


void printSortedTrenches(const OceanTrench arr[], int size) {
    OceanTrench trenches[20];
    int tCount = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i].type == TRENCH) {
            trenches[tCount++] = arr[i];
        }
    }
    if (tCount == 0) {
        cout << "Желобных впадин нет.\n";
        return;
    }
    bubbleSortByDepth(trenches, tCount);
    cout << "Желобные впадины (по убыванию глубины):\n";
    for (int i = 0; i < tCount; ++i) {
        printTrench(trenches[i]);
    }
}


void printOceansOfDeepest(const OceanTrench arr[], int size) {
    // Копируем массив, чтобы не портить оригинал
    OceanTrench copy[20];
    for (int i = 0; i < size; ++i) copy[i] = arr[i];
    bubbleSortByDepth(copy, size);
    cout << "Океаны трёх самых глубоких впадин:\n";
    for (int i = 0; i < min(3, size); ++i) {
        cout << i+1 << ". " << copy[i].ocean << " (" << copy[i].name << ", " << copy[i].depth << " м)\n";
    }
}


void changeTrenchByDepth(OceanTrench arr[], int size, double oldDepth, double newDepth) {
    for (int i = 0; i < size; ++i) {
        if (arr[i].depth == oldDepth) {
            arr[i].depth = newDepth;
            cout << "Впадина " << arr[i].name << " изменена: глубина была " << oldDepth << " м, стала " << newDepth << " м.\n";
            return;
        }
    }
    cout << "Впадина с глубиной " << oldDepth << " не найдена.\n";
}


void wrapperPrint(const OceanTrench arr[], int size, const string& title) {
    cout << title << ":\n";
    for (int i = 0; i < size; ++i) {
        printTrench(arr[i]);
    }
}


void filterByOcean(const OceanTrench arr[], int size) {
    string oceanName;
    cout << "Введите название океана для фильтрации: ";
    cin >> oceanName;
    OceanTrench filtered[20];
    int fCount = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i].ocean == oceanName) {
            filtered[fCount++] = arr[i];
        }
    }
    wrapperPrint(filtered, fCount, "Впадины в океане " + oceanName);
}

int main() {
    setlocale(LC_ALL, "Russian");

    OceanTrench trenches[20] = {
        {"Марианская", 11034, "Тихий", TRENCH, {11.35, 142.20}},
        {"Тонга", 10882, "Тихий", TRENCH, {-16.00, -172.00}},
        {"Курило-Камчатская", 10542, "Тихий", TRENCH, {50.00, 160.00}},
        {"Филиппинская", 10540, "Тихий", TRENCH, {10.00, 126.00}},
        {"Кермадек", 10047, "Тихий", TRENCH, {-29.00, -177.00}},
        {"Идзу-Бонин", 9810, "Тихий", TRENCH, {28.00, 142.00}},
        {"Пуэрто-Рико", 8800, "Атлантический", TRENCH, {19.00, -66.00}},
        {"Южно-Сандвичев", 8264, "Атлантический", TRENCH, {-56.00, -26.00}},
        {"Романш", 7760, "Атлантический", RIFT, {0.00, -20.00}},
        {"Средне-Атлантический хребет", 4000, "Атлантический", RIDGE, {10.00, -35.00}},
        {"Восточно-Тихоокеанское поднятие", 3500, "Тихий", RIDGE, {-20.00, -110.00}},
        {"Зондский желоб", 7729, "Индийский", TRENCH, {-10.00, 105.00}},
        {"Яванский желоб", 7725, "Индийский", TRENCH, {-11.00, 108.00}},
        {"Челенджер", 10994, "Тихий", TRENCH, {11.35, 142.20}},  // часть Марианской
        {"Лорд-Хау", 8000, "Тихий", TRENCH, {-32.00, 162.00}},
        {"Перуанско-Чилийский желоб", 8065, "Тихий", TRENCH, {-20.00, -71.00}},
        {"Алеутский желоб", 7679, "Тихий", TRENCH, {52.00, -173.00}},
        {"Гренландское море", 5600, "Северный Ледовитый", RIFT, {75.00, -10.00}},
        {"Хребет Гаккеля", 4500, "Северный Ледовитый", RIDGE, {85.00, 0.00}},
        {"Красное море разлом", 3040, "Индийский", RIFT, {20.00, 38.00}}
    };

    // 1. Минимум и максимум
    double minD, maxD;
    findMinMaxDepth(trenches, 20, minD, maxD);
    cout << "Минимальная глубина: " << minD << " м\n";
    cout << "Максимальная глубина: " << maxD << " м\n\n";

    // 2. Желобные впадины, отсортированные по убыванию
    printSortedTrenches(trenches, 20);
    cout << "\n";

    // 3. Океаны трёх глубочайших впадин
    printOceansOfDeepest(trenches, 20);
    cout << "\n";

    // 4. Изменение впадины по глубине (пример)
    changeTrenchByDepth(trenches, 20, 11034, 11035);
    // Проверим изменение:
    cout << "\nПосле изменения:\n";
    for (int i = 0; i < 20; ++i) {
        if (trenches[i].name == "Марианская")
            cout << "Марианская глубина теперь: " << trenches[i].depth << " м\n";
    }
    cout << "\n";

    // 5. Фильтрация по океану (ввод с клавиатуры)
    filterByOcean(trenches, 20);

    return 0;
}
