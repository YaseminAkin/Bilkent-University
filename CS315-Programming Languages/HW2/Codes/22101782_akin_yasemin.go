package main

import "fmt"

func outerFunction() func() {
	outerVar := 10
	packageLevelVar := &globalVar

	closure := func() {
		fmt.Println("Outer variable:", outerVar)

		fmt.Println("Package-level variable:", *packageLevelVar)
	}

	return closure
}

var globalVar = 100

func outerClosure() func() func() string {
	outerVar := "Outer"

	return func() func() string {
		innerVar := "Inner"
		fmt.Println(outerVar) // Accesses outer closure variable

		return func() string {
			return outerVar + " " + innerVar // Accesses both outer and inner variables
		}
	}
}

func main() {

	//1
	adderFunc := func(x int) func(int) int {
		return func(y int) int {
			return x + y
		}
	}

	addFive := adderFunc(5)
	fmt.Println(addFive(10)) // Output: 15

	//2
	myClosure := outerFunction()
	myClosure() // Access the outer and package-level variables

	//3
	outerVar := 10
	closure := func() {
		outerVar += 5 // Modifying the outer variable
		fmt.Println("Inside Closure:", outerVar)
	}

	fmt.Println("Before Closure:", outerVar)
	closure()
	fmt.Println("After Closure:", outerVar)

	//4
	innerClosure := outerClosure()()
	fmt.Println(innerClosure()) // Executes the nested closure
}