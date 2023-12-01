#import <XCTest/XCTest.h>

#import "../01/day01.hpp"

using namespace std;

@interface _1_tests : XCTestCase
@end

@implementation _1_tests

vector<string> input_;

- (void)setUp {
  input_.clear();
  input_.push_back("1abc2");
  input_.push_back("pqr3stu8vwx");
  input_.push_back("a1b2c3d4e5f");
  input_.push_back("treb7uchet");
}

- (void)tearDown {
}

- (void)testParsesInput {
  XCTAssert(input_.size() == 4);
}

- (void)testPart1 {
  XCTAssertEqual(PartOne(input_), 142);
}

@end
