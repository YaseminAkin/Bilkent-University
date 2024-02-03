-- 22101782_akin_yasemin.lua

-- Boolean expressions in Lua

-- 1. Boolean operators
local a = true
local b = false
print("a = ", a)
print("b = ", b)

print("1. Boolean operators in Lua:")
print("AND 'and'(a and b): ", a and b) -- false
print("OR 'or' (a or b): ", a or b) -- true
print("NOT 'not' (not a): ", not a) -- false

-- 2. Data types for operands of boolean operators, Boolean values (Truthy and Falsy values)
print("\n2. Data types for operands of boolean operators, Boolean values (Truthy and Falsy values) in Lua: in Lua, only 'false' and 'nil' are 'falsy'. Everything else is 'truthy'.")
print("Boolean value of 1: ", 1 and true or false) -- true ('truthy' value)
print("Boolean value of nil: ", nil and true or false) -- false ('falsy' value)
print("Boolean value of 0: ", 0 and true or false) -- true (0 is 'truthy')
print("Boolean value of an empty string: ", "" and true or false) -- true (empty string is 'truthy')

-- 3. Operator precedence rules
print("\n3. Operator precedence rules in Lua: not > and > or")
local c = false
print("a or b and not c: ", a or b and not c)  -- Equivalent to (a or (b and (not c)))

local d = true
print("a or b == c and d ~= a", a or b == c and d ~= a) -- Equivalent to (a or ((b == c) and (d ~= a)))

print("not a and b or c == d and d ~= a: ", not a and b or c == d and d ~= a) -- Equivalent to (((not a) and b) or ((c == d) and (d ~= a)))
-- ((false and b) or ((c == d) and (d != a)))
-- ((false and b) or (false and false))
-- (false or false)
-- false

-- 4. Operator associativity rules
print("\n4. Operator associativity rules in Lua: left-associative")
print("a and b and c and d: ", a and b and c and d) -- Evaluates as (((a and b) and c) and d)

local x = 0
local y = 1
print("x > y or y > x or y == x: ", x > y or y > x or y == x) -- Evaluates as ((x > y or y > x) or y == x)

-- 5. Operand evaluation order
print("\n5. Operand evaluation order in Lua: left-to-right")
local function first_method()
  print("First method called")
  return true
end

local function second_method()
  print("Second method called")
  return false
end

if first_method() and second_method() then end  -- Output: "First method called" then "Second method called"
if second_method() or first_method() then end -- Outputs: "Second method called" then "First method called"

-- 6. Short-circuit evaluation
print("\n6. Short-circuit evaluation:")
-- Lua uses short-circuit evaluation for 'and' and 'or'.

-- For 'and', if the first operand is false, the second operand is not evaluated.
local result = b and second_method()   -- "Second method called" is not printed
print("Result of b and second_method(): ", result)

-- For 'or', if the first operand is true, the second operand is not evaluated.
result = a or second_method()    -- "Second method called" is not printed
print("Result of a or second_method(): ", result)