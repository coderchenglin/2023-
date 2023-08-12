#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <functional>

class CalTask
{
    using func_t = std::function<int(int,int,char)>;
    // typedef std::function<int(int,int)> func_t;
public:
    CalTask()
    {}
    CalTask(int x, int y, char op, func_t func)
    :_x(x), _y(y), _op(op), _callback(func)
    {}
    std::string operator()()
    {
        int result = _callback(_x, _y, _op);
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "%d %c %d = %d", _x, _op, _y, result);
        return buffer;
    }
    std::string toTaskString()
    {
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "%d %c %d = ?", _x, _op, _y);
        return buffer;
    }
private:
    int _x;
    int _y;
    char _op;
    func_t _callback;
};

const std::string oper = "+-*/%";

int mymath(int x, int y, char op)
{
    int result = 0;
    switch (op)
    {
    case '+':
        result = x + y;
        break;
    case '-':
        result = x - y;
        break;
    case '*':
        result = x * y;
        break;
    case '/':
    {
        if (y == 0)
        {
            std::cerr << "div zero error!" << std::endl;
            result = -1;
        }
        else
            result = x / y;
    }
        break;
    case '%':
    {
        if (y == 0)
        {
            std::cerr << "mod zero error!" << std::endl;
            result = -1;
        }
        else
            result = x % y;
    }
        break;
    default:
        // do nothing
        break;
    }

    return result;
}

class SaveTask
{
    typedef std::function<void(const std::string&)> func_t;
public:
    SaveTask()
    {}
    SaveTask(const std::string &message, func_t func)
    : _message(message), _func(func)
    {}
    void operator()()
    {
        _func(_message);
    }
private:
    std::string _message;
    func_t _func;
};

void Save(const std::string &message)
{
    const std::string target = "./log.txt";
    FILE *fp = fopen(target.c_str(), "a+");
    if(!fp)
    {
        std::cerr << "fopen error" << std::endl;
        return;
    }
    fputs(message.c_str(), fp);
    fputs("\n", fp);
    fclose(fp);
}