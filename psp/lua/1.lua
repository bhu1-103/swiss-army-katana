name = "bhu1"
io.write("Size of string ", #name, "\n")
io.write("boku wa namae wa ", name, "\n")
print(type(name))
name = 123
io.write("boku wa namae wa ", name, "\n")
print(type(name))
kira = [[
My name is Yoshikage Kira.
]]
kira2 =[[
Although, if I were to fight I wouldn't lose to anyone.
]]

kira=kira .. kira2
io.write(kira, "\n")
--boolean
canCode = false
io.write(type(canCode, "\n"))
--
io.write(type(lol), "\n")

io.write ("23+46 ",23+46,"\n")
io.write ("23-46 ",23-46,"\n")
io.write ("23*46 ",23*46,"\n")
io.write ("23/46 ",23/46,"\n")
io.write ("23%46 ",23%4,"\n")

io.write("floor(12.34) ", math.floor(12.34),"\n")
io.write("ceil(12.34) ", math.ceil(12.34),"\n")
io.write("max(1,2,3,4) ", math.max(1,2,3,4),"\n")
io.write("min(1,2,3,4) ", math.min(1,2,3,4),"\n")
io.write("pow(12,34) ", math.pow(12,34),"\n")
io.write("sqrt(12.34) ", math.sqrt(12.34),"\n")

io.write(math.randomseed(os.time()))
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")
io.write("random: ",math.random(1,2), "\n")

io.write("time right now is ", os.time())
io.write("\n")
print(string.format("pi value = %0.10f", math.pi))

age = 20

if age > 18 then
local age = 1
io.write("allowed \n") io.write(string.format("permitted to enter at time: %i", os.time(), "\n"))
io.write("\nyour age is ", age, "\n")
else
print("you liar!! go to jail now\n")
io.write("your age is ", age, "\n")
end

--canVote = age > 18 ? true:false
canVote = age > 18 and true or false
io.write("you can vote is ", tostring(canVote))
