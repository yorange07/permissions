#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

class User {
    string _name;
    string _login;
    string _pass;

public:
    User(string name, string login, string pass):_name(name), _login(login), _pass(pass) {}

    friend fstream& operator >>(fstream& is, User& obj);
    friend ostream& operator <<(ostream& os, const User& obj);
};

fstream& operator >>(fstream& is, User& obj)
{
    is >> obj._name;
    is >> obj._login;
    is >> obj._pass;
    return is;
}
ostream& operator <<(ostream& os, const User& obj)
{
    os << obj._name;
    os << ' ';
    os << obj._login;
    os << ' ';
    os << obj._pass;
    return os;
}

class Message {
    string _text;
    string _sender;
    string _receiver;

public:
    Message(string text, string sender, string receiver):_text(text), _sender(sender), _receiver(receiver) {}

    friend fstream& operator >>(fstream& is, Message& obj);
    friend ostream& operator <<(ostream& os, const Message& obj);
};

fstream& operator >>(fstream& is, Message& obj)
{
    is >> obj._text;
    is >> obj._sender;
    is >> obj._receiver;
    return is;
}
ostream& operator <<(ostream& os, const Message& obj)
{
    os << obj._text;
    os << ' ';
    os << obj._sender;
    os << ' ';
    os << obj._receiver;
    return os;
}


int main() {

    fstream user_file = fstream("users.txt", ios::in | ios::out);
    if (!user_file)
        // Для создания файла используем параметр ios::trunc
           user_file = fstream("users.txt", ios::in | ios::out | ios::trunc);

    fs::permissions("users.txt",
        fs::perms::owner_write | fs::perms::owner_read,
        fs::perm_options::remove);

    if (user_file) {
        User obj("Vladimir", "qwerty", "12345");
           // Запишем данные по в файл
        user_file << obj << endl;
           // Чтобы считать данные из файла, надо установить позицию для чтения в начало файла
        user_file.seekg(0, ios_base::beg);
           // Считываем данные из файла
        user_file >> obj;
        cout << obj << endl;
    }
    else
    {
        cout << "Could not open file users.txt!" << '\n';
        return 0;

    }

    fstream message_file = fstream("message.txt", ios::in | ios::out);
    if (!message_file)
           user_file = fstream("message.txt", ios::in | ios::out | ios::trunc);

    fs::permissions("message.txt",
        fs::perms::owner_write | fs::perms::owner_read,
        fs::perm_options::remove);

    if (message_file) {
        Message obj_m("Hello!", "Vladimir", "Alen");
        message_file << obj_m << endl;
        message_file.seekg(0, ios_base::beg);
        message_file >> obj_m;
        cout << obj_m << endl;
    }
    else
    {
        cout << "Could not open file message.txt!" << '\n';
        return 0;

    }
}
