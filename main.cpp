#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

using ip_addr = std::array<int,4>;

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

void out_ip_pool(const std::vector<ip_addr> & ip_pool){
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


template <typename Pred>
auto filter(const std::vector<ip_addr>& in, Pred p) {
    std::vector<ip_addr> out;
    std::copy_if(begin(in), end(in), std::back_inserter(out), p);
    return out;
}

auto filter(const std::vector<ip_addr>& vec, int val1) {
    return filter(vec, [val1](const ip_addr &elem) { return elem[0] == val1;});
}

auto filter(const std::vector<ip_addr>& vec, int val1, int val2) {
    return filter(vec, [val1, val2](const ip_addr &elem) { return elem[0] == val1 && elem[1] == val2;});
}

auto filter_any(const std::vector<ip_addr>& vec, int val_any) {
    return filter(vec, [val_any](const ip_addr &elem) { return std::find(elem.begin(), elem.end(), val_any) != elem.end();});
}

template <typename T>
auto stoi(const T &&strings){
    ip_addr ints{};
    std::transform(strings.begin(), strings.end(), ints.begin(),
        [](std::string s) {
            return std::stoi(s);
        });
    return ints;
}

int main(int, char **)
{
    try
    {
        std::vector<ip_addr> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(stoi(split(v.at(0), '.')));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(),
            [](const auto &a, const auto &b){
                return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                   [](const auto &s1, const auto &s2) { return s1 > s2;});
            });

        out_ip_pool(ip_pool);

        // TODO filter by first byte and output
        //out_ip_pool(filter(ip_pool, [](const auto &elem) { return elem[0] == 1;}));
        out_ip_pool(filter(ip_pool,1));

        // TODO filter by first and second bytes and output
        out_ip_pool(filter(ip_pool,46,70));

        // TODO filter by any byte and output
        out_ip_pool(filter_any(ip_pool,46));

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
