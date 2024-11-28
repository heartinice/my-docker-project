-- CREATE DATABASE IF NOT EXISTS example_db;

-- USE example_db;

-- -- Добавьте ваши таблицы, данные или другие SQL-команды ниже.

-- CREATE DATABASE example_db;
-- USE example_db;
-- CREATE TABLE users (
--     id INT AUTO_INCREMENT PRIMARY KEY,
--     name VARCHAR(100),
--     email VARCHAR(100)
-- );
-- INSERT INTO users (name, email) VALUES ('John Doe', 'john@example.com');
CREATE TABLE IF NOT EXISTS tasks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    task TEXT NOT NULL
);