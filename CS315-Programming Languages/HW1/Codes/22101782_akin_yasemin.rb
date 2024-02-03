# 22101782_akin_yasemin.rb

# Boolean expressions in Ruby

# 1. Boolean operators
a = true
b = false
puts "a = #{a}"
puts "b = #{b}"

puts "1. Boolean operators in Ruby:"
puts "AND '&&'(a && b): #{a && b}" # false
puts "OR '||' (a || b): #{a || b}" # true
puts "NOT '!' (!a): #{!a}" # false

# 2. Data types for operands of boolean operators, Boolean values
puts "\n2. Data types for operands of boolean operators, Boolean values in Ruby: in Ruby, almost every value is 'truthy', except for 'false' and 'nil' which are 'falsy'."
# 'true' and 'false' are the only boolean values. Everything else is truthy, except 'nil'.
puts !!1 # true ('truthy' value)
puts !!nil # false ('falsy' value)
puts !!0 # true (0 is 'truthy')
puts !"" # false
non_bool = "I am not a boolean"
if non_bool
    puts "In Ruby, non-boolean types can be used in boolean contexts. This will print."
end
number = 5
if number
    puts "Numbers other than 0 are also truthy in Ruby. This will print."
end

# 3. Operator precedence rules
puts "\n3. Operator precedence rules in Ruby: ! > && > ||"
c = false
puts "a || b && !c: #{a || b && !c}"  # Equivalent to a || (b && (!c))

d = true
puts "a || b == c && d != a: #{a || b == c && d != a}" # Equivalent to (a || ((b == c) && (d != a)))

puts "!a && b || c == d && d != a: #{!a && b || c == d && d != a}" # Equivalent to ((!a) && b) || ((c == d) && (d != a))

# 4. Operator associativity rules
puts "\n4. Operator associativity rules in Ruby: left-associative"
puts "a && b && c && d: #{a && b && c && d}" # Evaluates as (((a && b) && c) && d)

x = 0
y = 1
puts "x > y || y > x || y == x: #{x > y || y > x || y == x}" # Evaluates as ((x > y || y > x) || y == x)

# 5. Operand evaluation order
puts "\n5. Operand evaluation order in Ruby: left-to-right"
def first_method
  puts "First method called"
  true
end

def second_method
  puts "Second method called"
  false
end

first_method && second_method  # Output: "First method called" then "Second method called"
first_method || second_method  # Output: "First method called" then "Second method called"

# 6. Short-circuit evaluation
puts "\n6. Short-circuit evaluation:"
# Ruby uses short-circuit evaluation for && and ||.

# For &&, if the first operand is false, the second operand is not evaluated.
puts false && second_method   # "Second method called" is not printed

# For ||, if the first operand is true, the second operand is not evaluated.
puts true || second_method    # "Second method called" is not printed

result = b && (a || check())
puts "Result of b && (a || check()): #{result}" # check() is not called

def check
    puts "check() function called"
    true
end
