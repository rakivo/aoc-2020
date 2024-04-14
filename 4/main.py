CONTENT = open('input.txt', 'r').read().split('\n\n')[:-1]

REQUIRED_FIELDS = frozenset(['byr', 'ecl', 'eyr', 'hcl', 'hgt', 'iyr', 'pid'])
FULL_REQUIRED_FIELDS = frozenset(['byr', 'cid', 'ecl', 'eyr', 'hcl', 'hgt', 'iyr', 'pid'])

def part1() -> int:
    result = 0

    for chunk in CONTENT:
        fields = set(map(lambda x: x.split(':')[0], chunk.split()))
        if REQUIRED_FIELDS.issubset(fields):
            result += 1
        elif FULL_REQUIRED_FIELDS.issubset(fields):
            result += 1

    return result

def part2() -> int:
    # I'll solve this one tomorrow, too sleepy(3 AM)..
    None

print("Part 1:", part1())
print("Part 2:", part2())
