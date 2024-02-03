#1
def outer_function(x):
    def inner_function(y):
        return x * y
    return inner_function

multiplier_by_3 = outer_function(3)
print(multiplier_by_3(5))  # Output: 15

#2
def outer_function(x):
    y = 10
    global z
    z = 5

    def inner_function():
        nonlocal y
        y += 1
        print(f"x (local to outer): {x}, y (non-local): {y}, z (global): {z}")

    return inner_function

closure = outer_function(3)
closure()  # Output: x (local to outer): 3, y (non-local): 11, z (global): 5

#3
def outer():
    x = [10]

    def inner():
        nonlocal x
        x[0] += 1  # Modifies the list element, which is mutable
        return x[0]

    return inner

my_closure = outer()
print(my_closure())  # Output: 11
print(my_closure())  # Output: 12

#4
def outer_function(x):
    def middle_function(y):
        def inner_function(z):
            return x * y * z
        return inner_function
    return middle_function

nested_closure = outer_function(2)(3)
print(nested_closure(4))  # Output: 24