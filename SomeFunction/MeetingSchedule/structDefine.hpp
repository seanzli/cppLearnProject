#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <memory>

namespace Meeting {

class Time{
public:
    double start;
    double end;
};

constexpr unsigned int USER_SIZE = 20;

class Person {
public:
    Person(const char* name) : m_name(name) {}
    bool isValid(const Time& time) const {}

private:
    std::string m_name;
    std::vector<Time> m_meeting;
};


class MeetingParameter{
public:
    MeetingParameter(const char* name, Person& host, Time time)
                : m_name(name)
                , m_host(host)
                , m_time(time)
        {}

    bool addPerson(std::shared_ptr<Person> per) {
        if (per->isValid(m_time)) {
            m_person.emplace_back(per);
            return true;
        }
        return false;
    }
private:
    std::string m_name;
    Person& m_host;
    std::vector<std::shared_ptr<Person>> m_person;
    Time m_time;
};

};


