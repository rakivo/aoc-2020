#include <iostream>

#include <vector>
#include <fstream>

#define FILE_NAME "input.txt"

struct Instruction;

using usize  = size_t;
using Color  = std::string;
using String = std::string;
using vb     = std::vector<bool>;
using vs     = std::vector<std::string>;
using vi     = std::vector<Instruction>;

const static vs split(String, String);
static void print_instruction(Instruction instruction);
const static void solve(int&, usize&, vi, const vi*, vb*, const usize*);

enum class Kind
{
    ACC,
    JMP,
    NOP
};

std::ostream& operator<<(std::ostream& os, const Kind& kind)
{
    switch (kind)
    {
        case Kind::ACC: os << "ACC"; break;
        case Kind::JMP: os << "JMP"; break;
        case Kind::NOP: os << "NOP"; break;
    }
    return os;
}

struct Instruction
{
    Kind kind;
    int value;
    bool visited;
};   

static int part1(vi instructions)
{
    int acc = 0;
    usize line = 0;
    solve(acc, line, instructions, NULL, NULL, NULL);
    return acc;
}

static int part2(const vi& instructions)
{
    for (usize i = 0; i < instructions.size(); ++i)
    {
        vi new_instructions = instructions;
        switch (instructions[i].kind)
        {
        case Kind::JMP: new_instructions[i].kind = Kind::NOP; break;
        case Kind::NOP: new_instructions[i].kind = Kind::JMP; break;
        default: continue;
        }

        const usize N = new_instructions.size();
        
        int acc = 0;
        usize line = 0;
        vb visited(N, false);

        solve(acc, line, instructions, &new_instructions, &visited, &N);
        if (line == N) return acc;
    }

    return -1;
}

const static vi get_instructions(std::ifstream& f)
{
	vi result = {};
	String line;
    usize uline = 0;
	while (getline(f, line))
    {
        const vs splitted = split(line, " ");

        Kind kind = Kind::NOP;
        if      (splitted[0] == "acc") kind = Kind::ACC;
        else if (splitted[0] == "jmp") kind = Kind::JMP;
        else if (splitted[0] == "nop") kind = Kind::NOP;

        result.emplace_back(
            Instruction {
                .kind = kind,
                .value = std::stoi(splitted[1]),
                .visited = false
            });
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

    const vi instructions = get_instructions(f);

    std::cout << "Part 1: " << part1(instructions) << std::endl; // 1446
    std::cout << "Part 2: " << part2(instructions) << std::endl; // 1403
    
    f.close();

    return 0;
}

const static void solve(int& acc, usize& line, vi instructions, const vi *new_instructions, vb *visited, const usize *N)
{
    if (new_instructions != NULL && visited != NULL)
    {
        while (line < *N)
        {
            if ((*visited)[line]) break;
            (*visited)[line] = true;
            switch ((*new_instructions)[line].kind)
            {
            case Kind::ACC: acc  += instructions[line].value; line++; break;
            case Kind::JMP: line += instructions[line].value; break;
            case Kind::NOP: line++; break;
            }
        }
    } else {
        const usize N = instructions.size();
        while (line < N)
        {
            if (instructions[line].visited) break;
            
            instructions[line].visited = true;
            
            switch (instructions[line].kind)
            {
            case Kind::ACC: acc  += instructions[line].value; line++; break;
            case Kind::JMP: line += instructions[line].value; break;
            case Kind::NOP: line++; break;
            }
        }        
    }
}

const static vs split(String s, String delimiter)
{
	usize start = 0, end, delim_len = delimiter.size();
	String token = {};
	vs result = {};

	while ((end = s.find(delimiter, start)) != String::npos)
	{
		token = s.substr(start, end - start);
		start = end + delim_len;
		result.emplace_back(token);
	}

	result.emplace_back(s.substr(start));
	return result;
}
