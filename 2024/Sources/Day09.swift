enum Block {
  case Empty(size: Int)
  case File(size: Int, id: Int)
}

struct Day09: AdventDay {
  init(data: String) {
    self.data = data

    var blocks = [Block]()
    var isFile = true
    var currentId = 0
    for char in data.trimmingCharacters(in: .whitespacesAndNewlines) {
      let num = Int(String(char))!
      if isFile {
        blocks.append(.File(size: num, id: currentId))
        currentId += 1
      }
      else {
        blocks.append(.Empty(size: num))
      }

      isFile = !isFile
    }

    self.blocks = blocks
  }

  // Input is a disk map that uses a dense format to represent the layout of files and free space on the disk.
  // The digits alternate between indicating the length of a file and the length of free space.
  var data: String

  let blocks: [Block]

  func isFile(block: Block) -> Bool {
    if case .File = block {
      return true
    }
    else {
      return false
    }
  }

  func checksum(blocks: [Block]) -> Int {
    var numberPos = 0
    var sum = 0
    for block in blocks {
      if case .File(var size, let id) = block {
        while size > 0 {
          sum += numberPos * id
          size -= 1
          numberPos += 1
        }
      }
      if case .Empty(let size) = block {
        numberPos += size
      }
    }

    return sum
  }

  func defragPart1(blocks: [Block]) -> [Block] {
    var sortedBlocks = blocks
    var i = 0
    while true {
      let block = sortedBlocks[i]
      guard case .Empty(let emptySize) = block else {
        // If this is a file, we don't need to do anything
        i += 1
        continue
      }

      // Find the last file block
      guard let lastFileIndex = sortedBlocks.lastIndex(where: { isFile(block: $0) }) else {
        // This should never happen (this means there are no file indicies)
        break
      }

      if lastFileIndex <= i {
        // This means we've compressed all the files and we're done
        break
      }

      guard case .File(let fileSize, let fileId) = sortedBlocks[lastFileIndex] else {
        // Something bad has happened - we got a file index but there's not a file there
        print("OH NO")
        break
      }

      if emptySize == fileSize {
        // Same size, we can swap
        sortedBlocks[i] = .File(size: emptySize, id: fileId)
        sortedBlocks[lastFileIndex] = .Empty(size: fileSize)
      }
      else if emptySize < fileSize {
        // We can only fit part of this file here
        sortedBlocks[i] = .File(size: emptySize, id: fileId)
        sortedBlocks[lastFileIndex] = .File(size: fileSize - emptySize, id: fileId)
      }
      else {  // fileSize < emptySize
        // We can fit the full file and have space left over, don't increment the counter
        sortedBlocks[lastFileIndex] = .Empty(size: fileSize)
        sortedBlocks[i] = .Empty(size: emptySize - fileSize)
        sortedBlocks.insert(.File(size: fileSize, id: fileId), at: i)
      }

      i += 1
    }

    return sortedBlocks
  }

  func part1() -> Int {
    let compressed = defragPart1(blocks: blocks)
    return checksum(blocks: compressed)
  }

  func findFileBlockIndex(blocks: [Block], id: Int) -> Int? {
    blocks.lastIndex { block in
      if case .File(_, let fileId) = block {
        return fileId == id
      }
      return false
    }
  }

  func defragPart2(blocks: [Block]) -> [Block] {
    var sortedBlocks = blocks

    // Find the last file block
    guard let lastFileIndex = sortedBlocks.lastIndex(where: { isFile(block: $0) }) else {
      // This should never happen (this means there are no file indicies)
      return blocks
    }

    guard case .File(_, var lastFileId) = sortedBlocks[lastFileIndex] else {
      // Something bad has happened - we got a file index but there's not a file there
      print("OH NO")
      return blocks
    }

    while lastFileId > 0 {
      guard let fileBlockIdx = findFileBlockIndex(blocks: sortedBlocks, id: lastFileId) else {
        print("OH NO")
        break
      }

      guard case .File(let fileSize, let fileId) = sortedBlocks[fileBlockIdx] else {
        print("OH NO")
        break
      }

      var i = 0
      while i < fileBlockIdx {
        let currentBlock = sortedBlocks[i]
        guard case .Empty(let emptySize) = currentBlock else {
          i += 1
          continue
        }

        if emptySize == fileSize {
          // Same size, we can swap
          sortedBlocks[i] = .File(size: emptySize, id: fileId)
          sortedBlocks[fileBlockIdx] = .Empty(size: fileSize)
          break
        }
        else if emptySize < fileSize {
          // We can only fit part of this file here
          i += 1
          continue
        }
        else {  // fileSize < emptySize
          // We can fit the full file and have space left over, don't increment the counter
          sortedBlocks[fileBlockIdx] = .Empty(size: fileSize)
          sortedBlocks[i] = .Empty(size: emptySize - fileSize)
          sortedBlocks.insert(.File(size: fileSize, id: fileId), at: i)
          break
        }

      }
      
      lastFileId -= 1
    }

    return sortedBlocks
  }

  func part2() -> Int {
    let compressed = defragPart2(blocks: blocks)
    return checksum(blocks: compressed)
  }
}
