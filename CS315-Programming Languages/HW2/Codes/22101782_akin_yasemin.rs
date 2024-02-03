fn main() {
//1
    let immediate_closure = || println!("This is an immediate closure.");
    immediate_closure();

    let add_closure = |a: i32, b: i32| -> i32 { a + b };
    println!("5 + 3 = {}", add_closure(5, 3));
    
//2
    // Ownership
    let owned_var = String::from("Hello");
    let closure = move || println!("{}", owned_var);
    closure();
    //Borrow mutability
    let mut mutable_var = 10;
    let mut closure2 = || mutable_var += 1;
    closure2();
    println!("{}", mutable_var);
    //Borrow immutability
    let immutable_var = 5;
    //let closure3 = || immutable_var += 1; //error
    //closure3();
    let closure3 = || println!("{}", immutable_var);
    closure3();
    
//3
    let mut count = 0;
    let mut increment = || {
    count += 1;
    println!("Count: {}", count);
    };
    
    increment(); // Count: 1
    increment(); // Count: 2

//4
    let outer_closure = |x: i32| {
        let y = x * 2;
        move |z: i32| y + z
    };

    let inner_closure = outer_closure(3);
    println!("Result: {}", inner_closure(4)); // Output: Result: 10
}