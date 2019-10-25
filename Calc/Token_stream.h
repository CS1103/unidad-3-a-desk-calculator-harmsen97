//
// Created by Jeronimo on 2019-10-21.
//

#ifndef CALCULATOR_TOKEN_STREAM_H
#define CALCULATOR_TOKEN_STREAM_H

#include "Token.h"
#include <iostream>
#include <map>

// Aux Headers

double expr(bool get);

double term(bool get);

double prim(bool get);

double error(const std::string& s);

// Token Stream Class

class Token_stream{
    void close(){if(owns)delete ip;}

    std::istream* ip;
    bool owns;
    Token ct{Kind::end};
public:
    explicit Token_stream (std::istream& s):ip{&s}, owns{false}{};
    explicit Token_stream (std::istream* p):ip{p}, owns{true}{};

    ~Token_stream(){close();}

    Token get();
    const Token& current();

    void set_input(std::istream& s){close(); ip = &s; owns = false;}
    void set_input(std::istream* p){close(); ip = p; owns = true;}
};

Token Token_stream::get() {
    char ch = 0;
    *ip>>ch;

    switch(ch){
        case 0:
            return ct = {Kind::end};
        case ';':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return ct = {static_cast<Kind>(ch)};
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            ip -> putback(ch);
            *ip >> ct.number_value;
            ct.kind = Kind::number;
            return ct;
        default:
            if(isalpha(ch)){
                ip->putback(ch);
                *ip>>ct.string_value;
                ct.kind = Kind::name;
                return ct;
            }

            error("bad token");
            return ct={Kind::print};
    }
}

const Token &Token_stream::current() {
    return ct;
}

// Global Variables

Token_stream ts{std::cin};
std::map<std::string,double> table;
int no_of_errors;

// Aux Functions

double error(const std::string& s){
    no_of_errors++;
    std::cerr<<s<<'\n';
    return 1;
}

double expr(bool get){
    double left = term(get);
    while(true){
        switch(ts.current().kind){
            case Kind::plus:
                left += term(true);
                break;
            case Kind::minus:
                left -= term(true);
                break;
            default:
                return left;
        }
    }
}

double term(bool get){
    double left = prim(get);

    while(true) {
        switch(ts.current().kind) {
            case Kind::mul:
                left *= prim(true);
                break;
            case Kind::div:
                if(auto d = prim(true)){
                    left /= d;
                    break;
                }
                return error("divide by 0");
            default:
                return left;
        }
    }
}

double prim(bool get){
    if(get) ts.get();

    switch(ts.current().kind){
        case Kind ::number:{
            double v = ts.current().number_value;
            ts.get();
            return v;
        }
        case Kind::name: {
            double &v = table[ts.current().string_value];
            if (ts.get().kind == Kind::assign) v = expr(true);
            return v;
        }
        case Kind:: minus:
            return -prim(true);
        case Kind::lp:{
            auto e = expr(true);
            if(ts.current().kind != Kind::rp) return error("')' expected" );
            ts.get();
            return e;
        }
        default:
            return error("primary expected");
    }
}

#endif //CALCULATOR_TOKEN_STREAM_H