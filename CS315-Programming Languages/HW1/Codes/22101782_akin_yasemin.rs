// 22101782_akin_yasemin.rs

fn main() {

    // 1. Boolean operators:
    let a = true;
    let b = false;
    println!("a = {}", a);
    println!("b = {}", b);

    println!("1. Boolean operators in Rust:");
    println!("AND '&&'(a && b): {}", a && b); // false
    println!("OR '||' (a || b): {}", a || b); // true
    println!("NOT '!' (!a): {}", !a); // false

    // 2. Data types for operands of boolean operators, Boolean values:
    println!("\n2. Data types for operands of boolean operators, Boolean values in Rust: Rust strictly uses bool type for Boolean expressions");
    // Using non-bool types as operands will cause a compilation error
    
    // Incorrect usage: using a string in a boolean context
    // let non_bool = "I am not a boolean";

    // The following line will cause a compilation error
    // Uncomment to see the error
    // if non_bool {
    //     println!("This won't compile");
    // }
    
    // Incorrect usage: using an integer in a boolean context
    // let number = 5;

    // The following line will also cause a compilation error
    // Uncomment to see the error
    // if number {
    //     println!("This won't compile either");
    // }

    // 3. Operator precedence rules:
    println!("\n3. Operator precedence rules in Rust: ! > && > ||");
    let c = false;
    println!("a || b && !c: {}", a || b && !c); // Equivalent to a || (b && (!c))
    // a || (b && true)
    // a || false
    // true
    let d = true;
    println!("a || b == c && d != a: {}", a || b == c && d != a); // Equivalent to (a || ((b == c) && (d != a)))
    // (a || ((true) && (false)) 
    // (a || (false))
    // (true)
    println!("!a && b || c == d && d != a: {}", !a && b || c == d && d != a); // Equivalent to ((!a) && b) || ((c == d) && (d != a))
    // (false && b) || ((c == d) && (d != a))
    // (false && b) || (false && false)
    // false || false
    // false
    
    // 4. Operator associativity rules:
    println!("\n4. Operator associativity rules in Rust: all Boolean operators are left-associative except '!', which is an unary operator so associativity is irrelevant here.");
    println!("a && b && c && d: {}", a && b && c && d); // Evaluates as (((a && b) && c) && d)
    // ((false && c) && d)
    // (false && d)
    // false
    let x = 0;
    let y = 1;
    println!("x > y || y > x || y == x: {}", x > y || y > x || y == x); // Evaluates as ((x > y || y > x) || y == x)
    // (true || y == x)
    // true

    // 5. Operand evaluation order:
    println!("\n5. Operand evaluation order in Rust: left-to-right");
    let mut result = func1() && func2(); // func1 called, then func2 called
    println!("{}", result);
    result = func2() || func1(); // func2 called, then func1 called
    println!("{}", result);
    
    // 6. Short-circuit evaluation.
    println!("\n6. Short-circuit evaluation:");
    result = b && (a || check());
    println!("Result of b && (a || check()): {}", result); // check() is not called
}

fn func1() -> bool { println!("func1 called"); true }

fn func2() -> bool { println!("func2 called"); false }

fn check() -> bool { println!("check() function called");true }