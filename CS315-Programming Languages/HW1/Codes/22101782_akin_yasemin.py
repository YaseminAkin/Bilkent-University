# 22101782_akin_yasemin.py

# Boolean expressions in Python

# 1. Boolean operators
a = True
b = False
print(f"a = {a}")
print(f"b = {b}")
# Demonstrating 'and', 'or', 'not', ==, !=
print("\n1. Boolean operators in Python:")
print(f"AND 'and' (a and b): {a and b}") # False
print(f"OR 'or' (a or b): {a or b}") # True
print(f"NOT 'not' (not a): {not a}") # False

# 2. Data types for operands of boolean operators, Boolean values (Truthy and Falsy values)
print("\n2. Data types for operands of boolean operators, Boolean values (Truthy and Falsy values) in Python: in Python, 'False', 'None', '0', empty sequences and collections are 'falsy'.")
# In Python, non-boolean types can be operands in boolean expressions
print("0 as Falsy:", bool(0))  # False, because 0 is considered Falsy
print("-5 as Truthy:", bool(-5)) # True, because non-zero numbers are considered Truthy
print("[1,4,6] as Truthy", bool([1,4,6]))
print("Yasemin as Truthy", bool("Yasemin"))
print("Empty string as Falsy", bool(""))
print("[] as Falsy", bool([]))
print("None as Falsy", bool(None))

non_bool = "I am not a boolean"
if non_bool:
    print("In Python, non-boolean types can be used in boolean contexts. This will print.")
number = 5
if number:
    print("Non-zero numbers are truthy in Python. This will print.")
    
print("Non-boolean operands:", 5 and 0)  # 0, because 0 is falsy in Python
print("Non-boolean operands:", "Yasemin" and "")  # "", because "" is falsy in Python

# 3. Operator precedence rules
print("\n3. Operator precedence rules in Python: not > and > or")
# '==' has equal precende with '!=' has higher precedence than 'not' has higher precedence than 'and' and 'and' has higher than 'or'
c = False
print(f"a or b and not c: {a or b and not c}")  # Equivalent to (a or (b and (not c)))

d = True
print(f"a or b == c and d != a: {a or b == c and d != a}") # Equivalent to (a or ((b == c) and (d != a)))
print(f"not a and b or c == d and d != a: {not a and b or c == d and d != a}") # Equivalent to (((not a) and b) or ((c == d) and (d != a)))
# (((not a) and b) or (false and false))
# ((false and b) or (false and false))
# (false or false)
# false

# 4. Operator associativity rules
print("\n4. Operator associativity rules in Python: left-associative")
print(f"a and b and c and d: {a and b and c and d}") # Evaluates as (((a and b) and c) and d)

x = 0
y = 1
print(f"x > y or y > x or y == x: {x > y or y > x or y == x}") # Evaluates as ((x > y or y > x) or y == x)

# 5. Operand evaluation order
print("\n5. Operand evaluation order in Python: left-to-right")
def first_method():
    print("First method called")
    return True

def second_method():
    print("Second method called")
    return False

first_method() and second_method() # Outputs: "First method called" then "Second method called"
second_method() or first_method() # Outputs: "Second method called" then "First method called"

# 6. Short-circuit evaluation
print("\n6. Short-circuit evaluation:")
# Python uses short-circuit evaluation for 'and' and 'or'.

# For 'and', if the first operand is false, the second operand is not evaluated.
print(False and second_method())   # "Second method called" is not printed

# For 'or', if the first operand is true, the second operand is not evaluated.
print(True or second_method())    # "Second method called" is not printed

def check():
    print("check() function called")
    return True

result = b and (a or check())
print(f"Result of b and (a or check()): {result}")  # check() is not called
