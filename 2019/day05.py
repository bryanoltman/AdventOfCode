from enum import Enum
import os


class Op(Enum):
    ADD = 1
    MULT = 2
    INPUT = 3
    PRINT = 4
    JNZ = 5
    JZ = 6
    LT = 7
    EQ = 8

    HALT = 99


class Opcode:
    def __init__(self, code: int):
        code_str = "{:05d}".format(code)
        self.op = Op(int(code_str[-2:]))
        self.is_param_a_immediate = code_str[-3] == "1"
        self.is_param_b_immediate = code_str[-4] == "1"

    def __repr__(self):
        return f"{self.__class__!s}({self.__dict__!r})"

    def num_params(self):
        if self.op == Op.ADD:
            return 3
        elif self.op == Op.MULT:
            return 3
        elif self.op == Op.INPUT:
            return 1
        elif self.op == Op.PRINT:
            return 1
        elif self.op == Op.JNZ:
            return 2
        elif self.op == Op.JZ:
            return 2
        elif self.op == Op.LT:
            return 3
        elif self.op == Op.EQ:
            return 3


def resolve_param(param: int, program: list[int], is_immediate: bool):
    return param if is_immediate else program[param]


class IntcodeComputer:
    def handle_opcode(self, idx: int, program: list[int]):
        code = program[idx]
        opcode = Opcode(code)
        print(opcode)
        if opcode.op == Op.ADD:
            a = resolve_param(program[idx + 1], program, opcode.is_param_a_immediate)
            b = resolve_param(program[idx + 2], program, opcode.is_param_b_immediate)
            out = program[idx + 3]
            program[out] = a + b
        elif opcode.op == Op.MULT:
            a = resolve_param(program[idx + 1], program, opcode.is_param_a_immediate)
            b = resolve_param(program[idx + 2], program, opcode.is_param_b_immediate)
            out = program[idx + 3]
            program[out] = a * b
        elif opcode.op == Op.INPUT:
            val = int(input("Input:"))
            out = program[idx + 1]
            program[out] = val
        elif opcode.op == Op.PRINT:
            a = resolve_param(program[idx + 1], program, opcode.is_param_a_immediate)
            print(a)
        elif opcode.op == Op.JNZ:
            a = resolve_param(program[idx + 1], program, opcode.is_param_a_immediate)
            b = resolve_param(program[idx + 2], program, opcode.is_param_b_immediate)
            if a != 0:
                return (program, b)
        elif opcode.op == Op.JZ:
            a = resolve_param(program[idx + 1], program, opcode.is_param_a_immediate)
            b = resolve_param(program[idx + 2], program, opcode.is_param_b_immediate)
            if a == 0:
                return (program, b)
        elif opcode.op == Op.LT:
            a = resolve_param(program[idx + 1], program, opcode.is_param_a_immediate)
            b = resolve_param(program[idx + 2], program, opcode.is_param_b_immediate)
            out = program[idx + 3]
            program[out] = 1 if a < b else 0
        elif opcode.op == Op.EQ:
            a = resolve_param(program[idx + 1], program, opcode.is_param_a_immediate)
            b = resolve_param(program[idx + 2], program, opcode.is_param_b_immediate)
            out = program[idx + 3]
            program[out] = 1 if a == b else 0
        elif opcode.op == Op.HALT:
            return (program, len(program))
        else:
            raise Exception(f"unknown opcode {code}")

        return (program, idx + opcode.num_params() + 1)

    def run_program(self, program):
        idx = 0
        while idx < len(program):
            (program, idx) = self.handle_opcode(idx, program)
        return program


def part1(input_str):
    program = list(map(int, input_str.split(",")))
    cpu = IntcodeComputer()
    cpu.run_program(program)


def part2(input_str):
    program = list(map(int, input_str.split(",")))
    cpu = IntcodeComputer()
    cpu.run_program(program)


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input_str = open(f"{script_path}/data/05.txt", "r").read().strip()
    print(f"Part 1: {part1(input_str)}")
    print(f"Part 2: {part2(input_str)}")
