#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <unistd.h> // Для getcwd
#include <limits.h> // Для PATH_MAX

class Task {
public:
    int id;
    std::string task;

    // Конструктор для Task
    Task(int id, const std::string& task) {
        this->id = id;
        this->task = task;
    }
};

class TodoApp {
public:
    TodoApp(const std::string& dbFile) {
        this->dbFile = dbFile;
        this->nextId = 1;
        loadTasks();  // Загружаем задачи из файла при старте
    }

    ~TodoApp() {
        saveTasks();  // Сохраняем задачи в файл при завершении
    }

    // Метод для добавления задачи
    void addTask(const std::string& task) {
        tasks.push_back(Task(nextId++, task));  // Создание объекта Task
        std::cout << "Задача добавлена: " << task << std::endl;
        saveTasks();  // Сохраняем изменения в файл сразу после добавления
    }

    // Метод для удаления задачи
    void removeTask(int taskId) {
        bool found = false;
        for (std::vector<Task>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->id == taskId) {
                tasks.erase(it);
                std::cout << "Задача с ID " << taskId << " удалена.\n";
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Задача с таким ID не найдена.\n";
        }
        saveTasks();  // Сохраняем изменения в файл сразу после удаления
    }

    // Метод для просмотра всех задач
    void viewTasks() const {
        if (tasks.empty()) {
            std::cout << "Задачи отсутствуют.\n";
            return;
        }

        std::cout << "\nСписок ваших задач:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << tasks[i].id << ". " << tasks[i].task << "\n";
        }
    }

private:
    std::vector<Task> tasks; // Список задач
    int nextId;  // Следующий идентификатор для задачи
    std::string dbFile;  // Путь к файлу базы данных

    // Загрузка задач из файла
    void loadTasks() {
        std::ifstream file(dbFile);
        std::string line;
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл " << dbFile << std::endl;
            return;
        }

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int id;
            std::string task;
            ss >> id;                  // Считываем ID
            std::getline(ss, task);    // Считываем текст задачи
            if (!task.empty() && task[0] == ',') {
                task = task.substr(1); // Убираем лишний пробел
            }
            tasks.push_back(Task(id, task));
            nextId = (id >= nextId) ? (id + 1) : nextId; // Обновляем nextId
        }
    }

    // Сохранение задач в файл
    void saveTasks() const {
        std::ofstream file(dbFile, std::ofstream::trunc); // Открываем файл для перезаписи
        if (!file) {
            std::cerr << "Ошибка: не удалось открыть файл для записи\n";
            return;
        }

        for (size_t i = 0; i < tasks.size(); ++i) {
            file << tasks[i].id << ", " << tasks[i].task << "\n";
        }
    }
};

int main() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Текущая рабочая директория: " << cwd << std::endl;
    } else {
        perror("Ошибка getcwd");
    }

    TodoApp app("../database/base.txt"); // Путь к файлу базы данных

    int choice;
    std::string newTask;
    int taskId;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Просмотреть задачи\n";
        std::cout << "2. Добавить задачу\n";
        std::cout << "3. Удалить задачу\n";
        std::cout << "4. Выйти\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                app.viewTasks();
                break;
            case 2:
                std::cout << "Введите описание задачи: ";
                std::cin.ignore(); // Очищаем буфер ввода
                std::getline(std::cin, newTask);
                app.addTask(newTask);
                break;
            case 3:
                std::cout << "Введите ID задачи для удаления: ";
                std::cin >> taskId;
                app.removeTask(taskId);
                break;
            case 4:
                std::cout << "До свидания!\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
                break;
        }
    } while (choice != 4); // Закрываем do-while цикл, если выбор != 4

    return 0; // Завершаем программу
}
