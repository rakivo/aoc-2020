content = list(map(lambda x: x.split(':'), open('input.txt', 'r').read().split('\n')[:-1]))

def part1() -> int:
    result = 0
    for (spec, letters) in content:
        spec = spec.split()
        rng = spec[0].split('-')
        if int(rng[0]) <= letters.count(spec[1]) <= int(rng[1]):
            result += 1

    return result

def part2() -> int:
    result = 0
    for (spec, letters) in content:
        spec = spec.split()
        indexes = list(map(int, spec[0].split('-')))
        if (letters[indexes[0]] == spec[1]) ^ (letters[indexes[1]] == spec[1]):
            result += 1

    return result

print("Part 1:", part1())
print("Part 2:", part2())
