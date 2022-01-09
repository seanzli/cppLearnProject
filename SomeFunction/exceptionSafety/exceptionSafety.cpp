#include <memory>
#include <map>
#include <string>

struct User {
    uint16_t uid;
    std::string name;
    int age;
};

std::map<uint16_t, std::shared_ptr<User>> users_by_uid;
std::multimap<std::string, std::shared_ptr<User>> users_by_name;
std::multimap<int, std::shared_ptr<User>> users_by_age;

// basic exception safety guarantees
/**
 * basic exception safety guarantee, all exception safety guarantee base on functions,like make_shared(), insert(),
 * if make_shared() throw an exception, everything is fine.
 * if user_by_name() or user_by_age(), throw an exception, three map's value will be different.
 * @param cur_user
 */
void add_user_basic(User& cur_user) {
    // init
    auto user = std::make_shared<User>(cur_user);

    users_by_uid.insert({cur_user.uid, user});
    users_by_name.insert({cur_user.name, user});
    users_by_age.insert({cur_user.age, user});
}

/**
 * strong exception safety guarantee
 * any of those functions throw exceptions, three maps will be keep the same value
 * but not elegant
 * @param cur_user
 */
void add_user_strong(User& cur_user) {
    // init
    auto user = std::make_shared<User>(cur_user);

    auto r1 = users_by_uid.insert({cur_user.uid, user}).first;
    try {
        auto r2 = users_by_name.insert({cur_user.name, user})->first;
        try {
            users_by_age.insert({cur_user.age, user});
        } catch (...) {
            users_by_name.erase(r2);
        }
    } catch (...) {
        users_by_uid.erase(r1);
    }
}

/**
 * use 'copy and swap' trick to make a strong exception safety guarantee
 * @param cur_user
 */
void add_user_strong_plus(User& cur_user) {
    // init
    auto user = std::make_shared<User>(cur_user);

    // copy
    auto temp_map_uid = users_by_uid;
    auto temp_map_name = users_by_name;
    auto temp_map_age = users_by_age;

    // action
    temp_map_uid.insert({cur_user.uid, user});
    temp_map_name.insert({cur_user.name, user});
    temp_map_age.insert({cur_user.age, user});

    // swap
    users_by_uid.swap(temp_map_uid);
    users_by_name.swap(temp_map_name);
    users_by_age.swap(temp_map_age);
}