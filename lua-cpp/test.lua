--[[
    Author: object_he@yeah.net

    Last modified: 2017-7-4
    
    Filename: Object.h
    
    Description: 
]]
local Object = require "libObject"

local  obj = Object.new("老司机",1024)
print (obj:getName())
print (obj:getValue())
obj:setValue(586)
print (obj:getValue())

--also
Object.setValue(obj,666)
print (Object.getValue(obj))
