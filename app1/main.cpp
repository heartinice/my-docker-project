#include <iostream>
#include <sqlite3.h> // Подключаем SQLite3
#include <string>

// Функция для выполнения SQL-запросов
void executeSQL(sqlite3* db, const std::string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

// Функция для отображения задач
void viewTasks(sqlite3* db) {
    const char* sql = "SELECT id, task FROM tasks;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "\nYour tasks:\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* task = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::cout << id << ". " << task << "\n";
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to fetch tasks.\n";
    }
}

// Функция для добавления задачи
void addTask(sqlite3* db) {
    std::cout << "\nEnter a new task: ";
    std::string newTask;
    std::cin.ignore();
    std::getline(std::cin, newTask);

    std::string sql = "INSERT INTO tasks (task) VALUES ('" + newTask + "');";
    executeSQL(db, sql);
    std::cout << "Task added successfully!\n";
}

// Функция для удаления задачи
void removeTask(sqlite3* db) {
    std::cout << "\nEnter the ID of the task to remove: ";
    int taskId;
    std::cin >> taskId;

    std::string sql = "DELETE FROM tasks WHERE id = " + std::to_string(taskId) + ";";
    executeSQL(db, sql);
    std::cout << "Task removed successfully!\n";
}

// Главная функция
int main() {
    // Открываем базу данных
    sqlite3* db;
    if (sqlite3_open("../database/base1.db", &db) != SQLITE_OK) {
        std::cerr << "Failed to open database\n";
        return 1;
    }

    // Создаем таблицу, если её ещё нет
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS tasks ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "task TEXT NOT NULL);";
    executeSQL(db, createTableSQL);

    // Меню приложения
    int choice;
    do {
        std::cout << "\nTODO List Application\n";
        std::cout << "1. View tasks\n";
        std::cout << "2. Add task\n";
        std::cout << "3. Remove task\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            viewTasks(db);
        } else if (choice == 2) {
            addTask(db);
        } else if (choice == 3) {
            removeTask(db);
        }
    } while (choice != 4);

    // Закрываем базу данных
    sqlite3_close(db);
    std::cout << "Goodbye!\n";
    return 0;
}
