// 22101782_akin_yasemin.dart

void main() {
  // 1. Boolean operators
  bool a = true;
  bool b = false;
  print("1. Boolean operators in Dart:");
  print("AND '&&' (a && b): ${a && b}"); // false
  print("OR '||' (a || b): ${a || b}"); // true
  print("NOT '!' (!a): ${!a}"); // false

  // 2. Data types for operands of boolean operators, Boolean values (Truthy and Falsy values)
  print("\n2. Data types for operands of boolean operators, Boolean values (Truthy and Falsy values) in Dart:");
  // Dart strictly uses bool type (has strict typing) for Boolean expressions, because Dart is a statically typed language and Non-Boolean values cannot be directly used as operasnd without explicit conversion.
  // The following lines will result in a compilation error in Dart
  // print("Number in boolean context:", 5);   // Compilation error
  // print("String in boolean context:", "hello"); // Compilation error
  // print("String in Boolean context: " + ("string" && a));
  // print("Number in Boolean context: " + (0 && a));

  // Correct way to use non-boolean values in boolean context
  int number = 5;
  String str = "hello";
  print("Is number non-zero?: ${number != 0}");
  print("Is string non-empty?: ${str.isNotEmpty}");

  // 3. Operator precedence rules
  print("\n3. Operator precedence rules in Dart: NOT > AND > OR");
  bool c = false;
  bool d = true;
  print("a || b && !c: ${a || b && !c}");                               // Equivalent to a || (b && (!c))
  print("a || b == c && d != a: ${a || b == c && d != a}");             // Equivalent to a || (b == c) && (d != a)
  print("!a && b || c == d && d != a: ${!a && b || c == d && d != a}"); // Equivalent to ((!a) && b) || ((c == d) && (d != a))

  // 4. Operator associativity rules
  print("\n4. Operator associativity rules in Dart: left-associative");
  print("a && b && c && d: ${a && b && c && d}"); // Evaluates as (((a && b) && c) && d)

  // 5. Operand evaluation order
  print("\n5. Operand evaluation order in Dart: left-to-right");
  bool result1 = firstMethod() && secondMethod();
  print(result1);
  bool result2 = secondMethod() || firstMethod();
  print(result2);

  // 6. Short-circuit evaluation
  print("\n6. Short-circuit evaluation in Dart:");
  print("false && secondMethod(): ${false && secondMethod()}"); // secondMethod is not called
  print("true || secondMethod(): ${true || secondMethod()}");   // secondMethod is not called
  bool result = b && (a || check());
  print("Result of b && (a || check()): $result"); //check() is not called because value of the second operand for the or operator does not matter at this example.
}

bool firstMethod() {
  print("First method called");
  return true;
}

bool secondMethod() {
  print("Second method called");
  return false;
}

bool check() {
  print("check() function called");
  return true;
}