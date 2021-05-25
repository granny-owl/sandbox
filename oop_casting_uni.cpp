#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <random>
#include <ctime>

struct person {
    int age;
    bool gender;
    int score;
    std::string name;
    virtual void print_info() = 0;
    virtual ~person(){}
};

struct student : person {
    void print_info() override {};
};

struct professor : person {    
    void print_info() override {
        std::cout << "Professor\n";
        std::cout << "Name: " << name << '\n';
        std::cout << "Gender: " << gender << '\n';
        std::cout << "Age: " << age << '\n' << '\n';
    }
};

int main() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> s_uni(0, 100), s_names(0, 3), s_age(0, 30);

    int uni_size = 1 + s_uni(gen); 
    std::vector<person*> university;

    std::vector<std::string> names = {
        "Sam",
        "Max",
        "Alex",
        "Charlie"
    };

    for (int i = 0; i < uni_size; i++ ) {
        int fill_uni = s_uni(gen);
        int name_at = s_names(gen);
        bool g_chance = (fill_uni%2 == 1);
        int age_n = s_age(gen);

        if (fill_uni > 20) {
            student* st = new student;
            st->name = names.at(name_at);
            st->gender = g_chance;
            st->age = age_n + 20;
            st->score = fill_uni;
            university.emplace_back(st);
        } else {
            professor* pr = new professor;
            pr->name = names.at(name_at);
            pr->gender = g_chance;
            pr->age = age_n + 40;
            university.emplace_back(pr);
        }
    }
  
    int score_sum = 0;
    int stud_count = 0;

    for (int i = 0; i < uni_size; i++) {
        person* p1 = university.at(i);
        if (dynamic_cast<student*>(p1)) {
            stud_count++;
            score_sum += p1->score;
            std::cout << "Student " << p1->name; 
            std::cout << "\nScore: " << p1->score << '\n' << '\n';
        } else if (dynamic_cast<professor*>(p1)) {
            p1->print_info();
        } 
    }  

    std::cout << "Avg. score: " << score_sum/stud_count;
    
    for (auto i : university) {
        delete i;
    }

    return 0;
}
