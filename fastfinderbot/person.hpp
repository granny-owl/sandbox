#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using str_ref = const std::string&; 

class person {
    const int64_t chat_id;
    const std::string username;
    std::string nick;
    std::set<std::string> tags;
    std::vector<std::string> search_results;
public:
    person(int64_t new_chat_id, str_ref username, str_ref new_nick);
    int64_t get_chat_id() const;                                      //get person's chat id
    str_ref get_tg_username() const;                                  //get person's tg username
    str_ref get_nick() const;                                         //get person's nick
    const std::set<std::string> get_tags() const;                     //get person's tags
    void change_nick(str_ref new_name);                               //change person's name
    size_t get_tags_size() const;                                     //get number of tags the person has
    bool has_tag(str_ref tag) const;                                  //check if person has the tag
    void add_tag(str_ref tag);                                        //add a tag to person's taglist
    void del_tag(str_ref tag);                                        //delete the tag from person's taglist
    void del_tag();                                                   //delete all the person's tags
    bool operator<(const person& p) const;
};


person::person(int64_t new_chat_id, str_ref new_username, str_ref new_nick) 
: chat_id(new_chat_id), username(new_username), nick(new_nick) {}

int64_t person::get_chat_id() const {
    return chat_id;
}

str_ref person::get_tg_username() const {
    return username;
}

str_ref person::get_nick() const { 
    return nick;
}

const std::set<std::string> person::get_tags() {
    return tags;
}

void person::change_nick(srt_ref new_nick) {
    nick = new_nick;
}

size_t person::get_tags_size() const { 
    return tags.size();
}

bool person::has_tag(str_ref tag) const { 
    return tags.count(tag) == 1;
}

void person::add_tag(str_ref tag) { 
    if (!has_tag(tag)) tags.insert(tag);
}

void person::del_tag(str_ref tag) { 
    if(has_tag(tag)) tags.erase(tag);
}

void person::del_tag() {
    tags.clear();
}

bool person::operator<(const person& p) const {
    return chat_id < p.get_chat_id();
}