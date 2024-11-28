# Используем базовый образ с поддержкой C++ (например, gcc)
FROM gcc:latest

# Обновление пакетов и установка необходимых зависимостей
RUN apt-get update && apt-get install -y \
    cmake \
    sqlite3 \
    libsqlite3-dev


# Устанавливаем рабочую директорию внутри контейнера
WORKDIR /app

# Копируем исходный код в контейнер
COPY main.cpp .

# Компилируем приложение
RUN g++ -o app main.cpp -lsqlite3

# Указываем команду для запуска приложения
CMD ["./app"]


