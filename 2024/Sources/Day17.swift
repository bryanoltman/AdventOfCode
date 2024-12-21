enum Opcode: Int {
  /// The adv instruction (opcode 0) performs division. The numerator is the value in the A register.
  /// The denominator is found by raising 2 to the power of the instruction's combo operand.
  /// (So, an operand of 2 would divide A by 4 (2^2); an operand of 5 would divide A by 2^B.)
  /// The result of the division operation is truncated to an integer and then written to the A register.
  case adv = 0
  ///  The bxl instruction (opcode 1) calculates the bitwise XOR of register B and the instruction's
  ///  literal operand, then stores the result in register B.
  case bxl = 1
  /// The bst instruction (opcode 2) calculates the value of its combo operand modulo 8 (thereby keeping only its lowest 3 bits), then writes that value to the B register.
  case bst = 2
  /// The jnz instruction (opcode 3) does nothing if the A register is 0. However, if the A register is not zero, it jumps by setting the instruction pointer to the value of its literal operand; if this instruction jumps, the instruction pointer is not increased by 2 after this instruction.
  case jnz = 3
  /// The bxc instruction (opcode 4) calculates the bitwise XOR of register B and register C, then stores the result in register B. (For legacy reasons, this instruction reads an operand but ignores it.)
  case bxc = 4
  /// The out instruction (opcode 5) calculates the value of its combo operand modulo 8, then outputs that value. (If a program outputs multiple values, they are separated by commas.)
  case out = 5
  /// The bdv instruction (opcode 6) works exactly like the adv instruction except that the result is stored in the B register. (The numerator is still read from the A register.)
  case bdv = 6
  /// The cdv instruction (opcode 7) works exactly like the adv instruction except that the result is stored in the C register. (The numerator is still read from the A register.)
  case cdv = 7
}

struct Computer {
  var regA: Int
  var regB: Int
  var regC: Int
}

struct Day17: AdventDay {
  init(data: String) {
    self.data = data
    let lines = data.trimmingCharacters(in: .whitespacesAndNewlines).split(separator: "\n")
    computer = Computer(
      regA: Int(lines[0].replacing("Register A: ", with: ""))!,
      regB: Int(lines[1].replacing("Register B: ", with: ""))!,
      regC: Int(lines[2].replacing("Register C: ", with: ""))!
    )

    program = lines.last!.replacing("Program: ", with: "").split(separator: ",").map { Int($0)! }
  }

  var data: String

  var computer: Computer
  let program: [Int]

  func getComboOperand(_ val: Int, cpu: Computer) -> Int {
    switch val {
    // 0 to 3 are literal
    case 0..<4: return val
    case 4: return cpu.regA
    case 5: return cpu.regB
    case 6: return cpu.regC
    case _:
      print("OH NO")
      print("OH NO")
      print("OH NO")
      print("OH NO")
      print("OH NO")
      return Int.max
    }
  }

  func runProgram(_ instrs: [Int], on startCpu: Computer) {
    var instrPtr = 0
    var cpu = startCpu
    while instrPtr < instrs.count {
      let op = Opcode(rawValue: instrs[instrPtr])!
      instrPtr += 1

      if op != .jnz && instrPtr >= instrs.count {
        break
      }

      switch op {
      case .adv:
        // combo operand
        let operand = getComboOperand(instrs[instrPtr], cpu: cpu)
        instrPtr += 1

        let numerator = cpu.regA
        let denominator = 1 << operand
        cpu.regA = Int(numerator / denominator)
      case .bxl:
        // literal operand
        let operand = instrs[instrPtr]
        instrPtr += 1
        cpu.regB ^= operand
      case .bst:
        // combo operand
        let operand = getComboOperand(instrs[instrPtr], cpu: cpu)
        instrPtr += 1
        cpu.regB = operand % 8
      case .jnz:
        if cpu.regA == 0 {
          break
        }

        // literal operand
        let operand = instrs[instrPtr]
        instrPtr = operand
      case .bxc:
        // unused operand, just increment instrPtr
        instrPtr += 1
        cpu.regB ^= cpu.regC
      case .out:
        // combo operand
        let operand = getComboOperand(instrs[instrPtr], cpu: cpu)
        instrPtr += 1
        print(operand % 8, terminator: ",")
      case .bdv:
        // combo operand
        let operand = getComboOperand(instrs[instrPtr], cpu: cpu)
        instrPtr += 1

        let numerator = cpu.regB
        let denominator = 1 << operand
        cpu.regB = Int(numerator / denominator)
      case .cdv:
        // combo operand
        let operand = getComboOperand(instrs[instrPtr], cpu: cpu)
        instrPtr += 1

        let numerator = cpu.regC
        let denominator = 1 << operand
        cpu.regC = Int(numerator / denominator)
      }
    }
  }

  func part1() -> Int {
    runProgram(program, on: computer)
    return 0
  }

  func part2() -> Int {
    return 0
  }
}
