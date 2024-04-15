content = list(map(int, open('input.txt', 'r').read().split('\n')[:-1]))

def part1() -> int:
    for i in range(len(content) - 1):
        for j in range(len(content)):
            if content[i] + content[j] == 2020:
               return content[i] * content[j]

def part2() -> int:
    for i in range(len(content) - 2):
        for j in range(len(content) - 1):
            for k in range(len(content)):
                if content[i] + content[j] + content[k] == 2020:
                    return content[i] * content[j] * content[k]

print("Part 1:", part1()) # 982464
print("Part 2:", part2()) # 162292410
