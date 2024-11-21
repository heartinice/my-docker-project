# Используем официальный образ gcc
FROM gcc:latest

# Обновляем репозитории и меняем зеркало на более доступное
RUN echo "deb http://deb.debian.org/debian/ bookworm main" > /etc/apt/sources.list \
    && echo "deb http://security.debian.org/debian-security bookworm-security main" >> /etc/apt/sources.list \
    && echo "deb http://deb.debian.org/debian/ bookworm-updates main" >> /etc/apt/sources.list \
    && apt-get update && apt-get install -y \
    cmake \
    make \
    g++ \
    curl \
    gnupg \
    lsb-release \
    && apt-get clean

# Копируем исходный код приложения
COPY . /app

# Устанавливаем рабочую директорию
WORKDIR /app

# Строим приложение
RUN cmake . && make

# Указываем команду для запуска приложения
CMD ["./your_application_executable"]
