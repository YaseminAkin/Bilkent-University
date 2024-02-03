#1
def block_example
  yield "Hello"
end

block_example { |msg| puts "#{msg}, Block!" }

proc_example = Proc.new { |msg| puts "#{msg}, Proc!" }
proc_example.call("Hello")

lambda_example = ->(msg) { puts "#{msg}, Lambda!" }
lambda_example.call("Hello")

#2
CONST_VAR = 100

class Example
  def initialize
    @instance_var = 10
  end

  def create_closure
    local_var = 20
    lambda {
      global_var = 30  # Global variable within closure
      puts "Local variable: #{local_var}"     # Accesses local variable
      puts "Instance variable: #{@instance_var}"  # Accesses instance variable
      puts "Constant: #{CONST_VAR}"          # Accesses constant
      puts "Global variable: #{global_var}"  # Declares and accesses global variable
    }
  end
end

example = Example.new
closure = example.create_closure
closure.call

#3
def outer_function
  x = 10
  inner_function = lambda { x += 5 }
  inner_function.call
  puts x 
end

outer_function()

#4
def outer_function(text)
  inner_function = lambda do
    nested_function = lambda { puts text }
    nested_function.call
  end
  inner_function
end

my_closure = outer_function("Hello, Ruby!")
my_closure.call