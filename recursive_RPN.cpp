#include <iostream>
#include <vector>
#include <string>
#include <iterator>

template <class Str>
Str& erase_spaces(Str& foo) {
    size_t it = 0;
    while (it < foo.size()) {
        bool flag = false;
        if (foo.at(it) == ' ') {
            for (size_t i = it; i < foo.size()-1; i++) {
                foo.at(i) = foo.at(i+1);
            }
            foo.erase(foo.size()-1);
            flag = true;
        }
        if (flag) {
            it = 0;
        } else it++;
    }
    return foo;
}

template <class Str>
Str& add_zeroes (Str& foo) {
    size_t it = 0;
    if (foo.at(it) == '-') {
        foo = '0' + foo;
    }
    it++;
    while (it < foo.size()) {
        if (foo.at(it) == '-' && foo.at(it-1) == '(') {
            foo += ' ';
            for (size_t i = foo.size()-1; i > it; i--) {
                foo.at(i) = foo.at(i-1);
            }
            foo.at(it) = '0';
        }
        it++;
    }
    return foo;
}

template <class Str>
Str& add_multsigns (Str& foo) {
    size_t it = 1;
    Str l_symbs = "0123456789)";
    Str r_symbs = "0123456789(";
    bool l_flag;
    bool r_flag;
    while (it < foo.size()-1) {
        l_flag = false;
        r_flag = false;
        for (auto a = 0; a < l_symbs.size(); a++) {
            if (l_symbs.at(a) == foo.at(it-1)) l_flag = true;
            if (r_symbs.at(a) == foo.at(it+1)) r_flag = true;
        }
    
        if (foo.at(it) == '(' && l_flag == true) {
            foo += ' ';
            for (size_t i = foo.size()-1; i > it; i--) {
                foo.at(i) = foo.at(i-1);
            }
            foo.at(it) = '*';
            l_flag = false; 
        }

        if (foo.at(it) == ')' && r_flag == true) {
            foo += ' ';
            for (size_t i = foo.size()-1; i > it + 1; i--) {
                foo.at(i) = foo.at(i-1);
            }
            foo.at(it+1) = '*';
            r_flag = false;
        }
        it++;
    }
    return foo;
} 

template<class Str>
Str& do_postfix (Str& foo) {

    //delete side brackets, if the Str has them
    bool first_open = false;
    size_t count_brs = 0;
    size_t tt = 0;
        while (tt < foo.size()) {
            if (foo.at(tt) == '(') {
                count_brs++;
                if (tt == 0) {
                    first_open = true;
                }
            }
            if (foo.at(tt) == ')') {
                count_brs--;
                if (first_open == true && count_brs == 0) {
                    if (tt != foo.size() - 1) {
                        tt = foo.size();
                        first_open = false;
                    } else {
                    first_open = false;
                    foo.erase(0,1);
                    foo.erase(foo.size()-1);
                    tt = foo.size();
                    }
                }
            }
            tt++;
        }

    //transform the Str into the std::vector<Str>
    //divide it into numbers, signs and brackets
    Str nums = "0123456789";
    Str signs = "+*-/^!";
    size_t it = 0;
    std::vector<Str> bar;
    Str temp;
    size_t count = 0;
    bool m_br = false;
    bool m_num = false;

    while (it < foo.size()) {
        temp += foo.at(it);

        if (foo.at(it) == '(') {
            if (count == 0) m_br = true;
            count++;
        }   

        if (foo.at(it) == ')') {
            count--;
            if (count == 0) {
                bar.push_back(temp);
                temp.clear();
                m_br = false;
            }
        }

        if (m_br == false) {

            for (auto sgn : signs) {
                if (sgn == foo.at(it)) {
                    Str cut_temp = temp;
                    cut_temp.pop_back();
                    if (cut_temp != "") {
                        bar.push_back(cut_temp);
                    }
                    temp.clear();
                    temp += sgn;
                    bar.push_back(temp);
                    temp.clear();
                }
            } 
            if (it == foo.size() - 1 && temp != "") bar.push_back(temp);
        }

        it++;
    }

    //check if Strs of the above vector have brackets
    //if a Str has them, push it recursively into do_postfix()
    size_t mx = 0;
    size_t mz;
    bool has_brackets = false;
    while (mx < bar.size()) {
        Str element = bar.at(mx);
        mz = 0;
        size_t str_size = element.size();
        while (mz < str_size) {           
            if (element.at(mz) == '(') {
                has_brackets = true;
            }
            mz++;
        }

        if (has_brackets == true) {
            has_brackets = false;
            Str new_string = do_postfix(element);
            bar.at(mx) = new_string;
        }
        mx++;
    } 

    //here we have moves
    size_t i_1 = 0;
    while (i_1 < bar.size()) {
        if (bar.at(i_1) == "^") {
            bar.at(i_1-1) += " ";
            bar.at(i_1-1) += bar.at(i_1+1);
            bar.at(i_1-1) += " ";
            bar.at(i_1-1) += bar.at(i_1);
            bar.erase(bar.begin() + i_1);
            bar.erase(bar.begin() + i_1);
            i_1 = 0;
        }
        i_1++;
    }

    size_t i_2 = 0;
    while (i_2 < bar.size()) {
        if (bar.at(i_2) == "*" || bar.at(i_2) == "/") {
            bar.at(i_2-1) += " ";
            bar.at(i_2-1) += bar.at(i_2+1);
            bar.at(i_2-1) += " ";
            bar.at(i_2-1) += bar.at(i_2);
            bar.erase(bar.begin() + i_2);
            bar.erase(bar.begin() + i_2);
            i_2 = 0;
        }
        i_2++;
    }

    size_t i_3 = 0;
    while (i_3 < bar.size()) {
        if (bar.at(i_3) == "+" || bar.at(i_3) == "-") {
            bar.at(i_3-1) += " ";
            bar.at(i_3-1) += bar.at(i_3+1);
            bar.at(i_3-1) += " ";
            bar.at(i_3-1) += bar.at(i_3);
            bar.erase(bar.begin() + i_3);
            bar.erase(bar.begin() + i_3);
            i_3 = 0;
        }
        i_3++;
    }

    //recollect Strs of vector bar back into Str foo 
    foo.clear();
    size_t ix = 0;
    for (auto ix : bar) {
        foo += ix;
    }
    return foo;
}

int main() {
    std::string bar = "-45 7-8 * 3/(-2+2) ";

    std::cout << bar << "\n";
    bar = erase_spaces(bar); 
    for (auto it : bar) std::cout << it;

    std::cout << "\n";
    add_zeroes(bar);
    for (auto it : bar) std::cout << it;

    std::cout << "\n";    
    add_multsigns(bar);
    for (auto it : bar) std::cout << it;

    std::cout << "\n\n";
    do_postfix(bar);
    for (auto it : bar) std::cout << it;

    return 0;
}
