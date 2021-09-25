/**
 * @file Collector.hpp
 * @author Sean 
 * @brief   CollectorManager will create threads for each decoder.
 * @version 0.1
 * @date 2021-09-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <thread>
#include <list>
#include <memory>
#include <vector>
#include <future>

#include <type_traits>

#include "StructDefine.hpp"
#include "Data.hpp"

class Decoder {
public:
    /**
     * @brief Construct a new Decoder object.
     * 
     * @param cv    for notify.
     */
    Decoder(std::condition_variable& cv) : m_cv(cv) {}
    virtual ~Decoder() {}

    /**
     * @brief Derive class should override their own decoder method.
     * 
     */
    virtual void parser() = 0;
    void notify() {
        m_cv.notify_one();
    }

protected:
    std::atomic<bool>   isrunning{false};
    std::condition_variable& m_cv;
};

class Velodyne : public Decoder {
public:
    explicit Velodyne(std::condition_variable& cv, 
                      Buffer<LidarData>& _data) 
            : Decoder(cv)
            , data(_data) {}

    void parser() override {
        notify();
    }
private:
    Buffer<LidarData>& data;
};

class STIM300 : public Decoder {
public:
    explicit STIM300(std::condition_variable& cv, 
                     Buffer<ImuData>& _data)
                    : Decoder(cv)
                    , data(_data) {}

    void parser() override {
        notify();
    }
private:
    Buffer<ImuData> &data;
};

//-----------------

class CollectorManager {
public:
    CollectorManager() {}
    ~CollectorManager() {
        teminate();
    }

    void teminate() {
        for (auto &th : m_threads) {
            if (th.joinable())
                th.join();
        }
    }

    template<typename T>
    void add(T& __collector) {
        auto th = [] (T& __collector) {__collector.parser();};
        m_threads.emplace_back( std::thread(
           th , std::ref(__collector)
        ));
    }

private:
    std::vector<std::thread> m_threads;
};
