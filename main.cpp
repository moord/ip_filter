#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void out_ip_pool(const std::vector<std::vector<std::string> > & ip_pool){
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

template <typename T, typename Pred>
auto filter(const std::vector<T>& vec, Pred p) {
    std::vector<T> out;
    std::copy_if(begin(vec), end(vec), std::back_inserter(out), p);
    return out;
}

int main(int, char **)
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(),
            [](const auto &a, const auto &b){
                return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                   [](const auto &s1, const auto &s2) { return std::stoi(s1) > std::stoi(s2);});
            });

        out_ip_pool(ip_pool);

        // TODO filter by first byte and output
        out_ip_pool(filter(ip_pool, [](const auto &elem) { return elem[0] == "1";}));

        // TODO filter by first and second bytes and output
        out_ip_pool(filter(ip_pool, [](const auto &elem) { return elem[0] == "46" && elem[1] == "70";}));

        // TODO filter by any byte and output
        out_ip_pool(filter(ip_pool, [](const auto &elem) { return std::find(elem.begin(), elem.end(), "46") != elem.end();}));

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
