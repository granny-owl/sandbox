#include <iostream>
#include <stack>
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
    long long it = 0;
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

template <class Str>
Str& do_postfix (Str& foo) {
     std::stack<char> stk;
     Str stg;

     for (auto i = foo.begin(); i != foo.end(); i++) {
         for (size_t j = 0; j < 10; j++) {
             if (*i == (char)(48+j)) { //ASCII digits
                stg.push_back(*i);
             }
         }

         if (*i == '(') {
             stk.push('(');
         }

         if (*i == ')') {
             while (stk.top() != '(') {
                 stg.push_back(stk.top());
                 stk.pop();
             }

             if (stk.top() == '(') {
                 stk.pop();
             }
         }

         
             if (*i == '^') {
                 stk.push('^');
             } 

             if (*i=='/' || *i=='*') {
                 char s = stk.top();
                 
                 while (!stk.empty() && (stk.top()=='/' 
                        || stk.top()=='*' 
                        || stk.top()=='^')) {
                    stg.push_back(stk.top());
                    stk.pop();
                 }
                 
                 stk.push(*i);
             } 

             if (*i=='+' || *i=='-') {
                 
                 while (!stk.empty() && (stk.top()=='+' 
                        || stk.top()=='-' 
                        || stk.top()=='/' 
                        || stk.top()=='*' 
                        || stk.top()=='^')) {
                    stg.push_back(stk.top());
                    stk.pop();                    
                 }
                 
                 stk.push(*i); 
             } 
        
     }

     while (stk.empty() == false) {
         stg.push_back(stk.top());
         stk.pop();
     } 
     
     foo.erase();
     foo = stg;
     return foo;
}


int main() {
    std::string bar = "-45 7-8 *(2^3) 3/(-2+2) 6^2";
    std::cout << bar << "\n";   
    erase_spaces(bar);    
    add_zeroes(bar);       
    add_multsigns(bar);

    do_postfix(bar);
    std::cout << bar << "\n"; 

    return 0;
}
