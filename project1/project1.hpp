#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <ctime>  
#include <chrono> 
#include <limits>  

class Project1 {
public:
    Project1() {
        // initialization 
        introduction();
        init();
    }
    ~Project1() {}
    void run() {
        // 1 input question num and level
        int num;
        std::string prompt = "How many questions do u want? \n";
        num = getValidNum(0, 20, prompt);
        if (num == -1) // terminate flag
            return;
        
        // 2 input level
        prompt = "Input level?\n";
        int level = getValidNum(0, 4, prompt);
        if (level == -1)
            return;
        
        // 3 start
        std::cout << "-----------start-----------\n";
        generateEquation(num, level);

        // 4 report
        std::cout << "-----------report-----------\n";
        calculateReport();
        return;
    }


private:
    // member data
    float range_max, range_min;
    std::vector<std::vector<float>> report; // size == question num, contain vector: [input ans, time cost];
    std::vector<float> results;             // size == question num, record all results;
    std::vector<std::string> equations;     // size == question num, record all the equations;

    // function
    void init() {
        std::srand(std::time(nullptr)); 
        range_min = 0;
        range_max = 10;
    }

    void introduction() {
        std::cout << "Introduction\n";
        std::cout << "  This is an arithmetic game.\n";
        std::cout << "  1. Type in how many question that you need.\n";
        std::cout << "  2. Type in the level.\n";
        std::cout << "     1) level = 1: test contain addition and substraction, nums between 0 and 10\n";
        std::cout << "     2) level = 2: test contain addition and substraction, nums between 0 and 100\n";
        std::cout << "     3) level = 3: test contain addition, substraction, multiplication and division\n";
        std::cout << "                   nums between 0 and 10\n";
        std::cout << "     4) level = 4: test contain addition, substraction, multiplication and division\n";
        std::cout << "                   nums between 0 and 100\n";
        std::cout << "  3. Enjoy the game!\n";
        std::cout << "  4. Type in 'q' or 'Q' to quit this game whenever you want.\n";
        std::cout << "------------------" << std::endl;
    }

    bool inputQuit(const std::string str) {
        if ("Q" == str || "q" == str) {
            std::cout << "You choose to terminate this game, bye\n";
            getchar();
            return true;
        }
        return false;
    }

    bool allNum(const std::string str) {
        // all number
        int i = 0;
        for (i = 0; i < str.size(); ++i) {
            if (str[i] == '-' || str[i] == '.')
                continue;
            if (str[i] > '9' || str[i] < '0')
                break;
        }
        if (i < str.size())
            return false;
        return true;
    }

    int getValidNum(const int _min, const int  _max, const std::string prompt) {
        std::string str;
        int cur = 0;
        while (1) {
            std::cout << prompt;
            std::cout << "     You can choose input 'q' or 'Q' to teminate this game.\n";
            std::cout << "number should less than " << _max << ", large than "<< _min << "\n";
            std::cout << "(" << _min << " < input <= " << _max << ")\n";
            std::cin >> str;
            if (inputQuit(str)) {
                return -1;
            }

            if (allNum(str) == false)
                continue;

            cur = std::stoi(str);
            if (0 < cur && cur <= 20)
                break;
        }
        return cur;
    }

    // decode level num
    // return true = contain multiplication and division
    bool decodeLevel(const int level) {
        switch (level)
        {
        case 1: range_max = 10, range_min = 0; return false;
        case 2: range_max = 100, range_min = 0; return false;
        case 3: range_max = 10, range_min = 0; return true;
        case 4: range_max = 100, range_min = 0; return true;
        }
        return false;
    }

    

    void generateEquation(const int num, const int level) {
        
        bool b_contain_multiplication_division = decodeLevel(level);

        for (int i = 0; i < num; ++i) {
            std::string str = "";
            std::string equation = generateEquation(b_contain_multiplication_division);
            std::cout << "Question " << i << "\n";
            std::cout << equation << std::endl;
            while (1) {
                auto start_time = std::chrono::high_resolution_clock::now();
                std::cin >> str;
                auto end_time = std::chrono::high_resolution_clock::now();
                if (inputQuit(str))
                    return;
                if (allNum(str) == false) {
                    std::cout << "input should be all number" << std::endl;
                    continue;
                }
                std::chrono::duration<float, std::milli> tm = end_time - start_time;
                float ans_f = std::stof(str);
                report.push_back({ans_f, tm.count()});
                break;
            }
        }
    }

    float gererateRandNum() {
        return range_min + std::rand()/((RAND_MAX + 1u)/(range_max - range_min));
    }

    int getSign(const bool b_level) {
        if (b_level)
            return 1 + std::rand()/((RAND_MAX + 1u)/4);
        return 1 + std::rand()/((RAND_MAX + 1u)/2);
    }

    std::string generateEquation(const bool b_level) {
        int first = gererateRandNum();
        int secend = gererateRandNum();

        int sign = getSign(b_level);
        float res = 0;
        std::string s_sign = "";
        switch (sign) {
            case 1: s_sign = "+"; res = first + secend; break;
            case 2: s_sign = "-"; res = first - secend; break;
            case 3: s_sign = "*"; res = first * secend; break;
            case 4: s_sign = "/"; res = first * 1.0 / secend; break;
        }

        std::string equa = std::to_string(first) + s_sign + std::to_string(secend) + "=";
        equations.push_back(equa);
        results.push_back(res);
        return equa;
    }

    void calculateReport() {
        int num = report.size();
        int right = 0;
        float mini_sec = std::numeric_limits<float>::max();
        float sum_sec = 0.0;
        for (int i = 0; i < num; ++i) {
            std::cout << "Question: " << i << "\n";
            std::cout << equations[i] << "\n";
            std::cout << "Your answer : " << report[i][0] << ", Take time : " << report[i][1]/1000.0 << "s \n";
            std::cout << "True answer : " << results[i] << "\n";
            mini_sec = std::min(mini_sec, report[i][1]);
            sum_sec = sum_sec + report[i][1];
            if (std::abs(report[i][0] - results[i]) < 1e-4)
                right++;
        }

        std::cout << "\n" << "All " << num << " questions, Correct : " << right << "\n";
        std::cout << "min cost  : " << mini_sec/1000.0 << "s\n";
        std::cout << "mean cost : " << sum_sec/1000.0/num << "s";
    }
};