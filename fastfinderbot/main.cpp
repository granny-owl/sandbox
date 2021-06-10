#include <tgbot/tgbot.h>
#include "person.hpp"
#include "database.hpp"
#include "parser.hpp"


using namespace TgBot;

int main() {
    std::string token(std::getenv("TOKEN"));
    std::cout << "Token: " << token << std::endl;
    Bot bot(token);
    database db;

    /*bot.getEvents().onCommand("start", [&bot](Message::Ptr mes) {
        bot.getApi().sendMessage(mes->chat->id, "Hi!");
    });*/


    bot.getEvents().onCommand("join", [&bot](Message::Ptr mes) {
        if (!db.user_exists(mes->chat->id)) {
            if (mes->text.size() > 6 && mes->text.size() < 37) {
                auto vec = parse(mes->text);
                if (vec.size() == 2) {
                    if (vec.at(1).size() > 0 && vec.at(1).size() < 31) {
                        auto chat_id = mes->chat->id;
                        auto username = mes->chat->username;
                        auto nick = vec.at(1);
                        db.add_user(chat_id, username, nick);
                        bot.getApi().sendMessage(mes->chat->id, 
                            "Ты успешно вошел под ником " + nick);
                    } else {
                        bot.getApi().sendMessage(mes->chat->id, 
                            "Твой ник должен иметь длину от 1 до 30 символов");
                    }
                } else {
                    bot.getApi().sendMessage(mes->chat->id, 
                        "Твой ник должен состоять из одного слова");
                }
            } else {
                bot.getApi().sendMessage(mes->chat->id, 
                    "Твой ник должен состоять из одного слова длиной от 1 до 30 символов");
            }
        } else {
            bot.getApi().sendMessage(mes->chat->id, 
                "Ты уже вошел в систему.\nДля удаления своих данных и выхода введи '/quit'");
        }
    });


    bot.getEvents().onCommand("nick", [&bot](Message::Ptr mes) {
        if (db.user_exists(mes->chat->id)) {
            if (mes->text.size() > 6 && mes->text.size() < 37) {
                auto vec = parse(mes->text);
                if (vec.size() == 2) {
                    if (vec.at(1).size() > 0 && vec.at(1).size() < 31) {
                        auto chat_id = mes->chat->id;
                        auto nick = vec.at(1);
                        db.change_nick(chat_id, nick);
                        bot.getApi().sendMessage(mes->chat->id, 
                            "Твой ник успешно изменен на " + nick);
                    } else {
                        bot.getApi().sendMessage(mes->chat->id, 
                            "Твой новый ник должен иметь длину от 1 до 30 символов");
                    }
                } else {
                    bot.getApi().sendMessage(mes->chat->id, 
                        "Твой новый ник должен состоять из одного слова");
                }
            } else {
                bot.getApi().sendMessage(mes->chat->id, 
                    "Твой новый ник должен состоять из одного слова длиной от 1 до 30 символов");
            }
        } else {
            bot.getApi().sendMessage(mes->chat->id, 
                "Для начала войди в систему.\nДля входа под ником НИК введи '/join НИК'");
        }
    });


    bot.getEvents().onCommand("quit", [&bot](Message::Ptr mes) {
        if (db.user_exists(mes->chat->id)) {
            if (mes->text.size() == 5) {
                auto chat_id = mes->chat->id;
                db.del_user(chat_id);
                bot.getApi().sendMessage(mes->chat->id, 
                    "Твои данные успешно удалены");
            } else {
                bot.getApi().sendMessage(mes->chat->id, 
                    "Для удаления всех своих данных и выхода введи '/quit' без лишних символов");
            }
        } else {
            bot.getApi().sendMessage(mes->chat->id, 
                "Для начала войди в систему.\nДля входа под ником НИК введи '/join НИК'");
        }
    });


    bot.getEvents().onCommand("del", [&bot](Message::Ptr mes) {
        if (db.user_exists(mes->chat->id)) {
            if (mes->text.size() > 3 && mes->text.size() < 935) {
                auto vec = parse(mes->text);
                if (vec.size() == 1) {
                    if (mes->text.size() == 4) {
                        db.del_tag(mes->chat->id);
                        bot.getApi().sendMessage(mes->chat->id, 
                            "Все твои теги удалены.\nДля добавления новых тегов введи '/add ТЕГ1 ТЕГ2 .. ТЕГN");
                    } else {
                        bot.getApi().sendMessage(mes->chat->id, 
                            "Для удаления всех тегов введи '/del' без лишних символов");
                    }
                } else if (vec.size() > 1 && vec.size() < 31 ) {
                    for (auto it = vec.begin() + 1; it != vec.end(); it++) {
                        db.del_tag(mes->chat->id, *it);
                    }
                    auto tags = db.get_tags(mes->chat->id);
                    std::string all_tags = "";
                    for (auto& t : tags) {
                        all_tags += t;
                        all_tags += ' ';
                    }
                    bot.getApi().sendMessage(mes->chat->id, 
                        "Твои оставшиеся теги:\n" + all_tags);
                } else {
                    bot.getApi().sendMessage(mes->chat->id, 
                    "Максимальное количество тегов 30 штук, длина каждого не более 30 символов");
                }
            } else {
                bot.getApi().sendMessage(mes->chat->id, 
                    "Для удаления тегов ТЕГ1 ТЕГ2 .. ТЕГN введи '/del ТЕГ1 ТЕГ2 .. ТЕГN'.
                    \nДля удаления всех тегов введи '/del'.
                    \nМаксимальное количество тегов 30 штук, длина каждого не более 30 символов");
            }
        } else {
            bot.getApi().sendMessage(mes->chat->id, 
                "Для начала войди в систему.\nДля входа под ником НИК введи '/join НИК'");
        }
    });


    bot.getEvents().onCommand("add", [&bot](Message::Ptr mes) {
        if (db.user_exists(mes->chat->id)) {
            if (mes->text.size() > 5 && mes->text.size() < 935) {
                auto vec = parse(mes->text);
                auto tags_size = db.tags_size(mes->chat->id);
                if (vec.size() == 1) {
                    bot.getApi().sendMessage(mes->chat->id, 
                            "Количество новых тегов должно быть от 1 до 30");
                } else if (vec.size() > 31) {
                    bot.getApi().sendMessage(mes->chat->id, 
                            "Количество новых тегов должно быть от 1 до 30");
                } else {
                    if (tags_size + vec.size() - 1 < 31) {
                        //good
                        for (auto it = vec.begin() + 1; it != vec.end(); it++) {
                            db.add_tag(mes->chat->id, *it);
                        }
                        auto tags = db.get_tags(mes->chat->id);
                        std::string all_tags = "";
                        for (auto& t : tags) {
                            all_tags += t;
                            all_tags += ' ';
                        }
                        bot.getApi().sendMessage(mes->chat->id, 
                        "Твои теги после добавления новых:\n" + all_tags);
                    } else {
                        bot.getApi().sendMessage(mes->chat->id, 
                            "В твоем описании получится более 30 тегов");
                    }
                }
            } else {
                bot.getApi().sendMessage(mes->chat->id, 
                    "Для добавления тегов ТЕГ1 ТЕГ2 .. ТЕГN введи '/del ТЕГ1 ТЕГ2 .. ТЕГN'.
                    \nКоличество тегов пользователя от 1 до 30 штук, длина каждого не более 30 символов");
            }
        } else {
            bot.getApi().sendMessage(mes->chat->id, 
                "Для начала войди в систему.\nДля входа под ником НИК введи '/join НИК'");
        }
    });


    bot.getEvents().onCommand("me", [&bot](Message::Ptr mes) {
        if (db.user_exists(mes->chat->id)) {
            if (mes->text.size() == 3) {
                auto nick = db.get_nick(mes->chat->id);
                auto tags = db.get_tags(mes->chat->id);
                std::string all_tags = "";
                for (auto& t : tags) {
                    all_tags += t;
                    all_tags += ' ';
                }
                bot.getApi().sendMessage(mes->chat->id, 
                    "Твой никнейм:\n" + nick + "\nТвои теги:\n" + all_tags);
            } else {
                bot.getApi().sendMessage(mes->chat->id, 
                    "Чтобы узнать свои ник и теги введи '/me' без лишних символов");
            }
        } else {
            bot.getApi().sendMessage(mes->chat->id, 
                "Для начала войди в систему.\nДля входа под ником НИК введи '/join НИК'");
        }
    });


    bot.getEvents().onAnyMessage([&bot](Message::Ptr mes) {
        std::cout << "User '" << mes->user->username << "' wrote: " << mes->text << std::endl;
        if (StringTools::startsWith(mes->text, "/join")) return;
        if (StringTools::startsWith(mes->text, "/nick")) return;
        if (StringTools::startsWith(mes->text, "/add")) return;
        if (StringTools::startsWith(mes->text, "/del")) return;
        if (StringTools::startsWith(mes->text, "/me")) return;
        if (StringTools::startsWith(mes->text, "/find")) return;
        if (StringTools::startsWith(mes->text, "/musthave")) return;
        if (StringTools::startsWith(mes->text, "/more")) return;
        if (StringTools::startsWith(mes->text, "/join")) return;
        if (StringTools::startsWith(mes->text, "/ask")) return;
        if (StringTools::startsWith(mes->text, "/allow")) return;
        if (StringTools::startsWith(mes->text, "/quit")) return;
        bot.getApi().sendMessage(mes->chat->id, "Твое сообщение:\n" + mes->text + "\n\nЖду команд");
    });

    return 0;
}


//Message::Ptr->chat->id 
//Message::Ptr->chat->username
//Message::Ptr->from->username


//add -- от 1 до 30 слов, каждое от 1 до 30 символов 
//more -- вывести еще пользователей
//find и musthave -- от 1 до 30 слов, каждое от 1 до 30 символов
//ask и allow -- одно слово, от 1 до 30 символов


//join НИК             DONE-- присоединиться под именем НИК
//nick НИК             DONE-- поменять мой никнейм на НИК

//add ТЕГ1..ТЕГ30      DONE-- добавить через пробел до 30 тегов, по которым меня можно искать
//del ТЕГ1..ТЕГ30      DONE-- удалить некоторые теги
//del                  DONE-- удалить все мои теги
//me                   DONE-- показать мои никнейм и теги

//find ТЕГ1..ТЕГ30     -- поиск людей с наиболее совпадающими тегами
//musthave ТЕГ1..ТЕГ30 -- поиск людей, у которых точно есть указанные теги
//more                 -- показать больше людей

//ask НИК              -- попросить у НИК его реальный юзернейм в telegram
//allow НИК            -- позволить НИК получить мой юзернейм 

//quit                 DONE-- удалить все мои данные