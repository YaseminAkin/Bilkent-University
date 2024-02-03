String Function(int) createAdder(int addBy) {
    return (int i) => 'Result: ${i + addBy}';
}

String outerFunction(String message) {
  // An outer scope variable
  String outerVariable = 'Outer: $message';

  // Closure definition
  String innerFunction() {
    // Accessing the outer scope variable
    return 'Inner accesses: $outerVariable';
  }

  return innerFunction(); // Executing the closure
}

var globalVar = 10;

Function outerClosure() {
  var outerVar = 'Outer';

  Function innerClosure() {
    var innerVar = 'Inner';
    print(outerVar); // Accesses variable from the outer closure
    return () {
      print('$outerVar $innerVar'); // Accesses variables from both scopes
    };
  }

  return innerClosure();
}

void main() {

  //1
  var addTwo = createAdder(2);
  print(addTwo(3));  // Output: Result: 5
  
  //2
  var result = outerFunction('Hello');
  print(result); // Output will be displayed
  
  //3
  final outerFinal = 10;
  var outerVar = 10;
    Function closure = () {
        // outerFinal = 20; // This line would cause an error, as final variables can't be modified.
        print(outerFinal);
        outerVar = 20;
        print(outerVar);
        globalVar = 20;
        print(globalVar);
    };
    closure();  // Outputs: 10 20 20
  
  //4
  var nestedClosure = outerClosure();
  nestedClosure(); // Executes the nested closure
}