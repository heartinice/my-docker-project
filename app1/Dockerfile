 Используем официальный образ для C++
FROM gcc:latest

# Устанавливаем CMake
RUN apt-get update && apt-get install -y cmake

# Копируем проект в контейнер
WORKDIR /app
COPY . /app

# Создаем проект с помощью cmake
RUN cmake . && make

# Запускаем приложение
CMD ["./todoapp"]