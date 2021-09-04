/*
 * @Description: command template class
 * @Author: Sean
 * @Date: 2021-08-06 11:10:44
 * @LastEditTime: 2021-09-02 20:40:25
 * @LastEditors: Please set LastEditors
 * @Reference: 
 */

#pragma once

// c++ stl
#include <functional>
#include <memory>
#include <unordered_map>

namespace CommandSystem{
/**
 * @brief Command Public Base, for Class Manager,
 * 
 */
class BaseCommand {
public:
    ~BaseCommand() {}
};

/**
 * @brief Command, output type should be void, otherwise program will ignore.
 * 
 * @tparam ArgTypes input types
 */
template<typename... ArgTypes>
class Command : public BaseCommand {
    using Function = std::function<void(ArgTypes...)>;
    Function func;
public:
    /**
     * @brief Construct a new Command object
     * 
     * @param _func     :input function
     */
    explicit Command(std::function<void(ArgTypes...)> _func) : func(_func) {}

    /**
     * @brief functor execute
     * 
     * @param args 
     */
    void operator()(ArgTypes&&... args) {
        if (func)
            func(std::forward<ArgTypes>(args)...);
    }

    /**
     * @brief Get the Function object
     * 
     * @return Function 
     */
    Function getFunction() {return func;};

};

class Manager {
public:
    Manager(){}

    /**
     * @brief register function to manager
     * 
     * @tparam T            :Command<Arag...>
     * @param name          :register name
     * @param func          :register function
     * @return true         :register success
     * @return false        :name already exist
     */
    template<typename T>
    bool attach(const std::string& name, const T& func) {
        auto itr = hash.find(name);
        if (itr != hash.end())
            return false;
        hash.insert(std::make_pair(name, std::shared_ptr<BaseCommand>(new T(func))));
        return true;
    }

    /**
     * @brief execute registed function
     * 
     * @tparam ArgTypes     :function input types
     * @param name          :registed name
     * @param args          :function input arguments
     */
    template<typename... ArgTypes>
    void execute(const std::string& name, ArgTypes&&... args) {
        auto cur_cmd = (Command<ArgTypes...>*)(getCommand(name));
        if (cur_cmd)
            (*cur_cmd)(std::forward<ArgTypes>(args)...);
    }

    /**
     * @brief Get the Command object, for thread pool
     * 
     * @param name              :registed name
     * @return BaseCommand*     :base pointor;
     */
    BaseCommand* getCommand(const std::string& name) {
        std::unordered_map<std::string, std::shared_ptr<BaseCommand>>::const_iterator itr = hash.find(name);

        if (itr == hash.end())
            return nullptr;
        return itr->second.get();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<BaseCommand>> hash;
};
};
