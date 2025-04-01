function love.load()
  love.window.setPosition(300,300,1)
  aX = 0
  aY = 0
  love.graphics.setColor(255,0,0)
end

function love.update(dt)
  down = love.mouse.isDown(1)
end

function love.draw()
  cursorX,cursorY = love.mouse.getPosition()
  if down == true then
    aX = cursorX
    aY = cursorY
  end
  love.graphics.print(tostring(down),10,10)
  --love.graphics.print(cursorX,10,10)
  --love.graphics.print(cursorY,10,30)
  love.graphics.rectangle("fill",aX,aY,cursorX-aX,cursorY-aY)

end
