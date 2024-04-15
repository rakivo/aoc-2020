content = open('input.txt', 'r').read().split('\n')[:-1]

def part1(slope: tuple[int, int]) -> int:
    x = len(content[0])
    y = len(content)

    result, row, col = 0, 0, 0
    while row < y:
        if content[row][col] == '#': result += 1
        col = (col + slope[0]) % x
        row += slope[1]

    return result

def part2() -> int:
    result = part1((1, 1))

    tuples = [(3, 1), (5, 1), (7, 1), (1, 2)]
    for tup in tuples:
        result *= part1(tup)

    return result

print("Part 1:", part1((3, 1))) # 218
print("Part 2:", part2()) # 3847183340
