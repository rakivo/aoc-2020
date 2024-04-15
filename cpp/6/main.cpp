#include <iostream>

#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

#define usize size_t
#define String std::string

#define cout std::cout
#define endl std::endl

#define sc std::set<char>
#define vs std::vector<std::string>
#define umcu std::unordered_map<char, usize>
#define vvs std::vector<std::vector<std::string>>

#define FILE_NAME "input.txt"

usize part1(const vvs& content)
{
    usize result = 0;
    for (const auto& group : content)
    {
        sc uniqs = {};
        for (const auto& person: group)
            for (const auto& c: person) uniqs.insert(c);
    
        result += uniqs.size();
    }
    return result;
}

usize part2(const vvs& content)
{
    usize result = 0;
    for (const auto& group : content)
    {
        umcu map = {};
        for (const auto& person: group)
            for (const auto& c: person) map[c]++;
    
        const usize N = group.size();
        for (const auto& pair: map)
            if (pair.second == N) result++;
    }
    return result;
}

// <===========================================================>

const static vvs read_file(std::ifstream& f)
{
    vvs result = {};
    vs temp = {};
    String line;
    while (getline(f, line))
    {
        if (line.empty())
        {
            result.emplace_back(temp);
            temp.clear();
        } else temp.emplace_back(line);
    }
    if (!temp.empty()) result.push_back(temp);

    return result;
}

int main(void)
{
    std::ifstream f(FILE_NAME);
    if (!f.is_open())
    {
        cout << "Failed to open " << FILE_NAME << endl;        
        return 1;
    }

    vvs content = read_file(f);
    
    cout << "Part 1: " << part1(content) << endl; // 6735
    cout << "Part 2: " << part2(content) << endl; // 3221

    f.close();

    return 0;
}
