## ChatConsoleCpp

Учебный консольный чат, обладающий следующей функциональностью:
* консольная программа
* регистрация пользователей - логин, пароль, имя
* вход в чат по логину/паролю
* обмен сообщениями между всеми пользователями чата одновременно
* отправка сообщений конкретному пользователю
* обработка исключений

При разработке использовались контейнеры стандартной библиотеки шаблонов.

Классы:
* `User` - класс для описания пользователя со строковыми полями: логин (`_login`), пароль (`_password`), имя (`_name`)
* `Message` - класс для сообщения со строковыми полями: текст сообщения (`_text`) и `_from`, `_to` для хранения логинов и поля `_dateTime` типа `time_t` для хранения времени сообщения
* `Chat` - содержит динамические массивы пользователей (`_users`) и сообщений (`_messages`) и соответствующие методы для обработки и отображения пользователей и сообщений
* Обработка исключений
  - `UserLoginExc` - при попытке регистрации пользователей с одинаковыми логинами
  - `UserNameExc` - при попытке регистрации пользователей с одинаковыми именами

Объявление класса `Chat`
```cpp
class Chat {
public:
	Chat();
	~Chat() = default;
	bool isWork() const;
	void initMenu(); // Начальное меню
	void login(); // Аутентификация пользователя
	void signUp(); // Регистрация пользователя
	void showUserList() const; // Отображение списка пользователей
	void userMenu(); // Меню авторизованного пользователя
	std::shared_ptr<User> getUserByLogin(const std::string&) const;
	std::shared_ptr<User> getUserByName(const std::string&) const;
	std::shared_ptr<User> getCurrentUser() const;
	std::shared_ptr<User> getUserForChat() const;
	void setUserForChat(); // Выбор пользователя для общения
	void addMessage(); // Ввод сообщения
	void showChat() const; // Отображение списка сообщений
private:
	bool _isWork = false;
	std::vector<std::shared_ptr<User>> _users; // Массив пользователей
	std::vector<Message> _messages; // Массив сообщений
	std::shared_ptr<User> _currentUser = nullptr; // Активный пользователь
	std::shared_ptr<User> _userForChat = nullptr; // Пользователь, с которым ведется общение
};
```
Функции `initMenu()` и `userMenu()` реализуют общую логику приложения и пользовательский интерфейс.

Функции `showUserList()` и `showChat()` отображают списки пользователей и сообщений соответственно.

При аутентификации пользователя (функция `login()`) указатель `_currentUser` указывает на активного пользователя. Таким образом он попадает в общий чат. При определении указателя `_userForChat` (функция `setUserForChat()`) пользователь попадает в чат с конкретным пользователем.

### Замечание 1
В данную версию внесены следующие исправления:
1. В обьявлении класса `Chat`
 ```cpp
     std::vector<User> _users;
```
изменено на 
```cpp
    std::vector<std::shared_ptr<User>> _users;
```
Теперь `_users` - динамический массив умных указателей. Соответственно в методах `Chat::getUserByLogin` и `Chat::getUserByName` возвращаем просто умный указатель - `return user`.

2. При регистрации пользователя в функции `Chat::signUp()` во избежание копирования пользователи создаются не на стеке, а в куче 
с помощью `shared_ptr`. Вместо строки
```cpp
	User user = User(login, password, name);
```
добавлена строка
```cpp
	shared_ptr<User> user(new User(login, password, name));
```

3. В функции `Chat::addMessage()` вместо строки
```cpp
	cin.ignore();
```
добавлена строка
```cpp
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
```
В класс `Message` добавлено поле `_dateTime` типа `time_t` для сохранения времени сообщения, соответственно добавлен метод `Message::getTime()`. Также модифицирован метод `Chat::showChat()` для отображения времени сообщения, и добавлена функция `showTime(const time_t& time)` для отображения времени в человекочитаемом формате.

### Замечание 2
Осуществлена попытка реализации кроссплатформенного решения. Проект компиллируется в Windows и Linux. Для Windows пока не решена проблема корректного ввода русских символов во время исполнения программы (для имен пользователей и сообщений). В английской раскладке проект работает корректно. В Linux русские символы вводятся и отображаются корректно.
