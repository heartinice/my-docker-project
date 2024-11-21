FROM gcc:11

# Установить зависимости
RUN apt-get update && apt-get install -y cmake

# Создать рабочую директорию
WORKDIR /app

# Скопировать исходные файлы и сборочный файл
COPY . .

# Сборка проекта
RUN cmake . && make

# Запуск приложения
CMD ["./app2"]
