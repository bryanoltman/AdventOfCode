import Foundation

precedencegroup PowerPrecedence {
  higherThan: MultiplicationPrecedence
}
infix operator ^^ : PowerPrecedence
func ^^ (radix: Int, power: Int) -> Int {
  return Int(pow(Double(radix), Double(power)))
}

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
  var a: Int
  var b: Int
  var c: Int
}

struct Day17: AdventDay {
  init(data: String) {
    self.data = data
    let lines = data.trimmingCharacters(in: .whitespacesAndNewlines).split(
      separator: "\n")
    computer = Computer(
      a: Int(lines[0].replacing("Register A: ", with: ""))!,
      b: Int(lines[1].replacing("Register B: ", with: ""))!,
      c: Int(lines[2].replacing("Register C: ", with: ""))!
    )

    program = lines.last!.replacing("Program: ", with: "").split(separator: ",")
      .map { Int($0)! }
  }

  var data: String

  var computer: Computer
  let program: [Int]

  func getComboOperand(_ val: Int, cpu: Computer) -> Int {
    switch val {
    // 0 to 3 are literal
    case 0..<4: return val
    case 4: return cpu.a
    case 5: return cpu.b
    case 6: return cpu.c
    case _:
      print("OH NO")
      print("OH NO")
      print("OH NO")
      print("OH NO")
      print("OH NO")
      return Int.max
    }
  }

  func runProgram(_ instrs: [Int], on startCpu: Computer) -> [Int] {
    var instrPtr = 0
    var cpu = startCpu
    var outputs = [Int]()
    while instrPtr < instrs.count {
      let op = Opcode(rawValue: instrs[instrPtr])!
      instrPtr += 1

      if op != .jnz && instrPtr >= instrs.count {
        break
      }

      switch op {
      case .adv:
        // Divide reg A by 2 to the power of its operand (combo)
        let operand = getComboOperand(instrs[instrPtr], cpu: cpu)
        instrPtr += 1

        let numerator = cpu.a
        let denominator = 1 << operand
        cpu.a = Int(numerator / denominator)
      case .bxl:
        // literal operand
        let operand = instrs[instrPtr]
        instrPtr += 1
        cpu.b ^= operand
      case .bst:
        // combo operand
        let operand = getComboOperand(instrs[instrPtr], cpu: cpu)
        instrPtr += 1
        cpu.b = operand % 8
      case .jnz:
        if cpu.a == 0 {
          continue
        }

        // literal operand
        let operand = instrs[instrPtr]
        instrPtr = operand
      case .bxc:
        // unused operand, just increment instrPtr
        instrPtr += 1
        cpu.b ^= cpu.c
      case .out:
        // combo operand
        let operand = getComboOperand(instrs[instrPtr], cpu: cpu)
        instrPtr += 1
        outputs.append(operand % 8)
      case .bdv:
        // combo operand
        let operand = getComboOperand(instrs[instrPtr], cpu: cpu)
        instrPtr += 1

        let numerator = cpu.a
        let denominator = 1 << operand
        cpu.b = Int(numerator / denominator)
      case .cdv:
        // combo operand
        let operand = getComboOperand(instrs[instrPtr], cpu: cpu)
        instrPtr += 1

        let numerator = cpu.a
        let denominator = 1 << operand
        cpu.c = Int(numerator / denominator)
      }
    }

    return outputs
  }

  // An implementation of the real input's program
  func progImpl(cpu cpuIn: Computer) -> [Int] {
    var ret = [Int]()
    var cpu = cpuIn
    repeat {
      cpu.b = cpu.a % 8
      cpu.b = cpu.b ^ 5  // b101
      cpu.c = cpu.a / (1 << cpu.b)
      cpu.b = cpu.b ^ 6  // b110
      cpu.a = cpu.a / 8
      cpu.b = cpu.b ^ cpu.c

      ret.append(cpu.b % 8)
    } while cpu.a != 0

    return ret
  }

  // An implementation of the real input's program
  func progImplSimpl(cpu cpuIn: Computer) -> [Int] {
    var ret = [Int]()
    var cpu = cpuIn
    repeat {
      cpu.b = (cpu.a % 8) ^ 5  // b101
      cpu.c = cpu.a >> cpu.b  // Shifting by at most 7 (b = 010, 010 ^ 101 = 111)
      cpu.a = cpu.a >> 3
      cpu.b = (cpu.b ^ 6) ^ cpu.c

      ret.append(cpu.b % 8)
    } while cpu.a != 0

    return ret
  }

  func part1() -> String {
    print(progImpl(cpu: computer).map { String($0) }.joined(separator: ","))
    print(
      progImplSimpl(cpu: computer).map { String($0) }.joined(separator: ","))
    return runProgram(program, on: computer)
      .map { String($0) }.joined(separator: ",")
  }

  func getComboStringRepr(_ val: Int) -> String {
    switch val {
    // 0 to 3 are literal
    case 0..<4: return String(val)
    case 4: return "a"
    case 5: return "b"
    case 6: return "c"
    case _: return "OH NO"
    }
  }

  func printProgram() {
    var instrPtr = 0
    let instrs = program
    while instrPtr < instrs.count {
      let op = Opcode(rawValue: instrs[instrPtr])!
      instrPtr += 1

      if op != .jnz && instrPtr >= instrs.count {
        break
      }

      print("\(instrPtr): ", terminator: "")

      switch op {
      case .adv:
        // Divide reg A by 2 to the power of its operand (combo)
        let operand = getComboStringRepr(instrs[instrPtr])
        instrPtr += 1
        print("cpu.a /= (2 ^ \(operand))")
      case .bxl:
        // literal operand
        let operand = instrs[instrPtr]
        instrPtr += 1
        print("cpu.b ^= \(operand)")
      case .bst:
        // combo operand
        let operand = getComboStringRepr(instrs[instrPtr])
        instrPtr += 1
        print("cpu.b = \(operand) % 8")
      case .jnz:
        // literal operand
        let operand = instrs[instrPtr]
        print("if cpu.a != 0: goto \(operand)")
      case .bxc:
        // unused operand, just increment instrPtr
        instrPtr += 1
        print("cpu.b ^= cpu.c")
      case .out:
        // combo operand
        let operand = getComboStringRepr(instrs[instrPtr])
        instrPtr += 1
        print("print(\(operand) % 8)")
      case .bdv:
        // b = divde a by (2 raised to the combo operand)
        let operand = getComboStringRepr(instrs[instrPtr])
        instrPtr += 1
        print("cpu.b = cpu.a / 2 ** (\(operand))")
      case .cdv:
        // c = a / (two raised to the combo operand)
        let operand = getComboStringRepr(instrs[instrPtr])
        instrPtr += 1
        print("cpu.c = cpu.a / (2 ** \(operand))")
      }
    }
  }

  func part2() -> String {
    //  859449217430856 is too high
    var exp = 14
    var currentA = 8 ^^ (program.count - 1)
    let min = 035_184_372_088_832
    let max = 108_082_757_369_856

    while exp > 0 && currentA < max {
      var currentComputer = computer
      currentComputer.a = currentA

      let outputInstrs = progImplSimpl(cpu: currentComputer)
//      print("A:\(currentA) output:\(outputInstrs)")

      // Notice how as the power (n) decreases, the last 14 - n digits do not change. Thus, my program just increments A by 8 ** n, then when the last 15 - n digits of the output match the program, n is decremented. This repeats until the entire output matches the program. For me, the total program runtime is about 0.4 seconds.

      var shouldDecr = true
      let indexes = Array((exp + 1)..<program.count)
      for i in indexes {
        if program[i] != outputInstrs[i] {
          shouldDecr = false
          break
        }
      }

      if shouldDecr {
        print("exp is \(exp), a is \(currentA)")
        exp -= 1
      }
      
      currentA += 8 ^^ exp
    }

    return String(currentA)

//    var max = 859_449_217_430_856
    //    printProgram()
    print(program)
    while true {
      if currentA > max {
        return "done"
      }

      if currentA % 10_000_000 == 0 {
        print("a is \(currentA)")
      }
      var currentComputer = computer
      currentComputer.a = currentA
      let outputInstrs = progImplSimpl(cpu: currentComputer)
      print("A: \(currentA), output: \(outputInstrs)")

      //      if outputInstrs.count != program.count {
      //        return
      //          "output instr count: \(outputInstrs.count), program count: \(program.count)"
      //      }

      if outputInstrs == program {
        return String(currentA)
      }

      currentA += 8 ^^ 4
    }
  }
}
