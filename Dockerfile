# Используем официальный образ с C++
FROM gcc:latest

# Устанавливаем рабочую директорию
WORKDIR /app

# Копируем исходный код в контейнер
COPY ./app1 /app

# Устанавливаем зависимости (если они есть)
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    libsqlite3-dev

# Компилируем проект
RUN g++ main.cpp -o todoapp

# Команда для запуска приложения
CMD ["./todoapp"]
