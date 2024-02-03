--1
function outerFunction(x)
    return function(y) 
        return x + y
    end
end

local addFive = outerFunction(5)
print(addFive(3))  -- Output: 8

--2
function outerFunction2()
    local localVar = 10
    globalVar = 20
    local tableVar = { value = 30 }

    function innerFunction()
        return localVar, globalVar, tableVar.value
    end

    return innerFunction
end

local closure = outerFunction2()
print(closure()) -- Outputs: 10 20 30

--3
function outerFunction3()
    local outerVar = 10
    function innerFunction2()
        outerVar = outerVar + 5
        return outerVar
    end
    return innerFunction2
end

local myClosure = outerFunction3()
print(myClosure())  -- Output: 15
print(myClosure())  -- Output: 20

--4
function outerFunction4(outerVar2)
    function innerFunction3(innerVar2)
        print(outerVar2, innerVar2)
        return function(mostInnerVar)
            print(outerVar2, innerVar2, mostInnerVar)
        end
    end
    return innerFunction3
end

local nested = outerFunction4("Outer")("Inner")
nested("Most Inner")