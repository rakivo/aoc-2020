#include <iostream>

#include <regex>
#include <deque>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 
#include <unordered_map>

#define FILE_NAME "input.txt"

struct Child;
struct Rule;

using usize  = size_t;
using Color  = std::string;
using String = std::string;
using vr     = std::vector<Rule>;
using vc     = std::vector<Child>;
using dc     = std::deque<Color>;
using vs     = std::vector<std::string>;
using ucb    = std::unordered_map<Color, bool>;
using vvs    = std::vector<std::vector<std::string>>;
using Rules  = std::unordered_map<Color, std::vector<Child>>;

const static Rule s2r(String);
const static vs split(String, String);
const static inline String trim(String s);
static bool can_contain(const Rules&, const Color&, const Color&);

struct Child
{
    Color color;
    usize amount;
};

struct Rule
{
    Color container;
    vc children;
};

static usize part1(const Rules& rules, const Color& color)
{
    usize result = 0;

    for (const auto& rule : rules)
        if (can_contain(rules, rule.first, color))
            result++;

    return result;
}

static bool can_contain(const Rules& rules, const Color& outer_color, const Color& inner_color)
{
    const auto& children = rules.at(outer_color);
    for (const auto& child : children)
        if (child.color == inner_color || can_contain(rules, child.color, inner_color))
            return true;

    return false;
}

static usize part2(const Rules& rules, const Color& color)
{
    usize result = 0;

    if (rules.find(color) != rules.end())
        for (const auto& child: rules.at(color))
            result += child.amount + child.amount * part2(rules, child.color);

    return result;
}

const static Rules get_rules(std::ifstream& f)
{
	Rules result = {};
	String line;
	while (getline(f, line))
	{
		const Rule rule = s2r(line);
		result[rule.container] = rule.children;
	}
	
	return result;
}

int main(void)
{
	std::ifstream f(FILE_NAME);
	if (!f.is_open())
	{
		std::cout << "Failed to open " << FILE_NAME << std::endl;
		return 1;
	}

	const Rules rules = get_rules(f);

    printf("Part 1: %zu\n", part1(rules, "shiny gold")); // 119
    printf("Part 2: %zu\n", part2(rules, "shiny gold")); // 155802

    f.close();

    return 0;
}

const static Rule s2r(String line)
{
	const vs contain_splitted = split(line, "contain");
	const String container = trim(split(contain_splitted[0], "bags")[0]);

	if (contain_splitted[1] == " no other bags.") return Rule { .container = container, .children = {} };
		
	std::regex pattern(" ([0-9]+) (.*) bags?");
	std::smatch matches;
	vc children = {};
	for (const auto& child : split(contain_splitted[1], ","))
		if (std::regex_search(child, matches, pattern))
			children.emplace_back(Child {
				.color = matches[2],
				.amount = static_cast<usize>(std::stoi(matches[1]))
			});

	return Rule {
		.container = container,
		.children = children
	};
}

const static vs split(String s, String delimiter)
{
	usize start = 0, end, delim_len = delimiter.size();
	String token = {};
	vs result = {};

	while ((end = s.find(delimiter, start)) != String::npos)
	{
		token = s.substr (start, end - start);
		start = end + delim_len;
		result.emplace_back(token);
	}

	result.emplace_back(s.substr(start));
	return result;
}

const static inline String trim(String s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
	{
		return !std::isspace(ch);
	}));

	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
	{
		return !std::isspace(ch);
	}).base(), s.end());

	return s;
}
