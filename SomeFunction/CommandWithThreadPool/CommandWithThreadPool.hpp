/**
 * @file CommandWithThreadPool.hpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "../Command/Command.hpp"
#include "../ThreadPool/threadPool.hpp"

#include <memory>

using pThreadPool = std::shared_ptr<ThreadPool>;

class ManagerTP {
public:
    /**
     * @brief Construct a new Manager T P object
     * 
     * @param size 
     */
    explicit ManagerTP(unsigned size) {
        /// new ThreadPool pointer;
        threadPool = pThreadPool(new ThreadPool(size));
    }

    /**
     * @brief register name/function to managerThreadPool
     * 
     * @tparam T        // CommandSystem::Command<ArgType...>
     * @param name      // register name
     * @param f         // CommandSystem::Command<ArgType> function;
     * @return true     // register success
     * @return false    // register false
     */
    template<typename T>
    bool attach(const std::string& name, const T& f) {
        return cmdManager.attach(name, f);
    }

    /**
     * @brief execute 
     * 
     * @tparam ArgType  :function input types
     * @param name      :register function name
     * @param args      :register function input arguments
     * @return void
     */
    template<typename... ArgType>
    void execute(const std::string& name, ArgType&&... args) {
        auto cmd = cmdManager.getCommand(name);
        if (cmd == nullptr)
            return;
        auto func = ((CommandSystem::Command<ArgType...>*)(cmd))->getFunction();

        threadPool->attach(func, std::forward<ArgType>(args)...);
        return;
    }

private:
    pThreadPool threadPool;
    CommandSystem::Manager cmdManager; /// just use map function
};