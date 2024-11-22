# Базовый образ MySQL
FROM mysql:8.0

# Копирование файла инициализации
COPY base1.sql /docker-entrypoint-initdb.d/

# Установка переменных среды
ENV MYSQL_ROOT_PASSWORD=root
ENV MYSQL_DATABASE=example_db
