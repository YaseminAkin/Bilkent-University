// 22101782_akin_yasemin.go

package main

import "fmt"

func main() {

	// 1. Boolean operators
	a := true
	b := false
	fmt.Println("1. Boolean operators in Go:")
	fmt.Println("AND '&&' (a && b):", a && b)        // false
	fmt.Println("OR '||' (a || b):", a || b)         // true
	fmt.Println("NOT '!' (!a):", !a)                 // false

	// 2. Data types for operands of boolean operators, Boolean values (Truthy and Falsy values)
	fmt.Println("\n2. Data types for operands of boolean operators, Boolean values (Truthy and Falsy values) in Go: no truthy or falsy values")
	fmt.Println("Boolean true:", true)   // true
	fmt.Println("Boolean false:", false) // false

	// Attempting to use non-boolean values in boolean context will result in a compilation error.
	var number int = 5
	var str string = "hello"
	var ptr *int = &number
	var slice []int = []int{1, 2, 3}

	// Uncommenting any of the following lines will result in a compilation error in Go
	// fmt.Println("Number in boolean context:", bool(number))
	// fmt.Println("String in boolean context:", bool(str))
	// fmt.Println("Pointer in boolean context:", bool(ptr))
	// fmt.Println("Slice in boolean context:", bool(slice))

	// Correct way to use non-boolean values in boolean context
	fmt.Println("Is number non-zero?:", number != 0)
	fmt.Println("Is string non-empty?:", str != "")
	fmt.Println("Is pointer non-nil?:", ptr != nil)
	fmt.Println("Is slice non-empty?:", len(slice) > 0)

	// 3. Operator precedence rules
	fmt.Println("\n3. Operator precedence rules in Go: NOT > AND > OR")
	c := false
	d := true
	fmt.Println("a || b && !c:", a || b && !c)                               // Equivalent to a || (b && (!c))
	fmt.Println("a || b == c && d != a:", a || b == c && d != a)             // Equivalent to a || (b == c) && (d != a)
	fmt.Println("!a && b || c == d && d != a:", !a && b || c == d && d != a) //Equivalent to ((!a) && b) || ((c == d) && (d != a))

	// 4. Operator associativity rules
	fmt.Println("\n4. Operator associativity rules in Go: left-associative")
	fmt.Println("a && b && c && d:", a && b && c && d) // Evaluates as (((a && b) && c) && d)
	x := 0
	y := 1
	fmt.Println("x > y || y > x || y == x:", x > y || y > x || y == x) // Evaluates as ((x > y || y > x) || y == x)
	
	// 5. Operand evaluation order
	fmt.Println("\n5. Operand evaluation order in Go: left-to-right")
	result1 := firstMethod() && secondMethod()
	fmt.Println(result1)
	result2 := secondMethod() || firstMethod()
	fmt.Println(result2)

	// 6. Short-circuit evaluation
	fmt.Println("\n6. Short-circuit evaluation in Go:")
	fmt.Println("false && secondMethod():", false && secondMethod()) // secondMethod is not called
	fmt.Println("true || secondMethod():", true || secondMethod())   // secondMethod is not called
}

func firstMethod() bool {
	fmt.Println("First method called")
	return true
}

func secondMethod() bool {
	fmt.Println("Second method called")
	return false
}