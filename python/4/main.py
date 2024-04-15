content = open('input.txt', 'r').read().split('\n\n')[:-1]

REQUIRED_FIELDS = frozenset(['byr', 'ecl', 'eyr', 'hcl', 'hgt', 'iyr', 'pid'])
FULL_FIELDS = frozenset(['byr', 'cid', 'ecl', 'eyr', 'hcl', 'hgt', 'iyr', 'pid'])

def part1() -> int:
    result = 0

    for chunk in content:
        fields = set(map(lambda x: x.split(':')[0], chunk.split()))
        if REQUIRED_FIELDS.issubset(fields): result += 1
        elif FULL_FIELDS.issubset(fields): result += 1

    return result

import re

def check(field: str, value: str) -> bool:
    if not value: return False
    elif field == 'byr' and not (1920 <= int(value) <= 2002): return False
    elif field == 'iyr' and not (2010 <= int(value) <= 2020): return False
    elif field == 'eyr' and not (2020 <= int(value) <= 2030): return False
    elif field == 'hgt':
        if value.endswith('cm') and (150 <= int(value[:-2]) <= 193): return True
        elif value.endswith('in') and (59 <= int(value[:-2]) <= 76): return True
        else: return False
    elif field == 'hcl' and not re.match(r'^#[0-9a-f]{6}$', value): return False
    elif field == 'ecl' and not value in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']: return False
    elif field == 'pid' and not re.match(r'^\d{9}$', value): return False
    return True
 
def part2() -> int:
    result = 0

    for chunk in content:
        kvs = list(map(lambda x: tuple(x.split(':')), chunk.split()))
        fields = {kv[0] for kv in kvs}
        if REQUIRED_FIELDS.issubset(fields) or FULL_FIELDS.issubset(fields):
            if all(check(field, value) for field, value in kvs): result += 1
                
    return result

print("Part 1:", part1()) # 202
print("Part 2:", part2()) # 137
