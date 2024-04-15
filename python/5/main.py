content = open('input.txt', 'r').read().split('\n')[:-1]

def part1() -> int:
    result = -0xFFFFFFF

    for line in content:
        low, high = 0, 127
        for char in line[:7]:
            mid = (low + high) // 2
            if char == 'F': high = mid
            else: low = mid + 1

        row = low
        low, high = 0, 7
        for char in line[7:]:
            mid = (low + high) // 2
            if char == 'L': high = mid
            else: low = mid + 1

        result = max(result, row * 8 + low)

    return result
    
def part2() -> int:
    minimum, maximum, act_sum = 0xFFFFFFF, -0xFFFFFFF, 0
    for line in content:
        low, high = 0, 127
        for char in line[:7]:
            mid = (low + high) // 2
            if char == 'F': high = mid
            else: low = mid + 1

        row = low
        low, high = 0, 7
        for char in line[7:]:
            mid = (low + high) // 2
            if char == 'L': high = mid
            else: low = mid + 1

        ID = row * 8 + low
        act_sum += ID
        minimum = min(minimum, ID)
        maximum = max(maximum, ID)

    exp_sum = sum(range(minimum, maximum + 1))
    return exp_sum - act_sum
    
print("Part 1:", part1()) # 922
print("Part 2:", part2()) # 747
