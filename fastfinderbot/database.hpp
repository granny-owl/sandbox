#pragma once
#include "person.hpp"


class database {
    std::set<person> users;
public:
    void add_user(int64_t id, str_ref username, str_ref nick);  //add user to database

    void change_nick(int64_t id, str_ref new_name);             //change person's nickname
    size_t tags_size(int64_t id);                               //get the size of person's taglist
    //get id
    //get username
    //give permission (here or in database)
    const std::set<std::string> get_tags(int64_t id);           //get person's tagset

    bool user_exists(int64_t id);                               //check database for this user
    void del_user(int64_t id);                                  //delete user from database
    void add_tag(int64_t id, str_ref tag);                      //add the tag to the user's taglist
    bool has_tag(int64_t id, str_ref tag);                      //check if user has the tag
    void del_tag(int64_t id, str_ref tag);                      //delete user's tag
    void del_tag(int64_t id);                                   //delete all the user's tags
};


void database::add_user(int64_t id, str_ref username, str_ref nick) { 
    users.emplace(id, username, nick);
}

void database::change_nick(int64_t id, str_ref new_name) {
    person temp(id, "", "");
    auto user = users.find(temp);
    user->change_nick(new_name);
}

size_t database::tags_size(int64_t id) {
    person temp(id, "", "");
    auto user = users.find(temp);
    return user->get_tags_size();
}

const std::set<std::string> database::get_tags(int64_t id) {
    person temp(id, "", "");
    auto user = users.find(temp);
    return user->get_tags();
}

bool database::user_exists(int64_t id) {
    person temp(id, "", "");
    return users.count(temp) == 1;
}

void database::del_user(int64_t id) { 
    person temp(id, "", "");
    users.erase(users.find(temp));
}

void database::add_tag(int64_t id, str_ref tag) { 
    person temp(id, "", "");
    auto user = users.find(temp);
    user->add_tag(tag);
}

bool database::has_tag(int64_t id, str_ref tag) {
    person temp(id, "", "");
    auto user = users.find(temp);
    user->has_tag(tag);
} 

void database::del_tag(int64_t id, str_ref tag) { 
    person temp(id, "", "");
    auto user = users.find(temp);
    user->del_tag(tag);       
}

void database::del_tag(int64_t id) { 
    person temp(id, "", "");
    auto user = users.find(temp);
    user->del_tag();
}