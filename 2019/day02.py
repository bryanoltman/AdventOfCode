import os


def handle_opcode(idx: int, program: list[int]):
    code = program[idx]
    if code == 1:
        a = program[idx + 1]
        b = program[idx + 2]
        out = program[idx + 3]
        program[out] = program[a] + program[b]
    elif code == 2:
        a = program[idx + 1]
        b = program[idx + 2]
        out = program[idx + 3]
        program[out] = program[a] * program[b]
    elif code == 99:
        return False
    else:
        raise Exception(f"unknown opcode {code}")
    return True


def run_program(program):
    idx = 0
    while idx < len(program):
        if not handle_opcode(idx, program):
            break
        idx += 4
    return program


def part1(input):
    program = list(map(int, input.split(",")))
    program[1] = 12
    program[2] = 2
    program = run_program(program)
    return program[0]


def part2(input):
    for i in range(100):
        for j in range(100):
            program = list(map(int, input.split(",")))
            program[1] = i
            program[2] = j
            program = run_program(program)
            if program[0] == 19690720:
                return f"{i}{j}"
    raise Exception("no answer found")


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/data/02.txt", "r").read()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
