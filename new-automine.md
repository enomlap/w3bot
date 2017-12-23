Auto Mine 1.2

    Code:

    local workers = {}
    local goldmines = {}
    local _plugin = nil

    function OnGameStarted()
        local mine = GetNearestMine()
        local out = string.format("Sending %i %s(s) to %s ...", table.getsize(workers), Jass.GetUnitName(workers[1]), Jass.GetUnitName(mine))
            
        Game.WriteText(out, FRAME.UNIT, 10)
        
        for _,worker in pairs(workers) do
            Game.ExecuteCmd(worker, CMD.MOVE, 0, 0, mine)
        end
    end

    function OnEnterLoading()
        table.clear(workers)
        table.clear(goldmines)
    end

    function CreateUnit_Post(unit)
        if Jass.GetOwningPlayer(unit) == Jass.GetLocalPlayer() then    
            if IsUnitWorker(unit) then
                table.insert(workers, unit)
            end
        end
        
        if IsUnitGoldmine(unit) then
            table.insert(goldmines, unit)
        end
        
        return nil
    end

    function GetNearestMine()
        local worker = workers[1]

        for _,mine in pairs(goldmines) do
            if Distance(worker, mine) <= 850 then
                return mine
            end
        end
        
        return nil
    end

    function Distance(unit1, unit2)
        local loc1 = Jass.GetUnitLoc(unit1)
        local loc2 = Jass.GetUnitLoc(unit2)
        
        local X1 = Jass.GetLocationX(loc1)
        local X2 = Jass.GetLocationX(loc2)
        
        local Y1 = Jass.GetLocationY(loc1)
        local Y2 = Jass.GetLocationY(loc2)
        
        local Z1 = Jass.GetLocationZ(loc1)
        local Z2 = Jass.GetLocationZ(loc2)
        
        local A = X1 - X2
        local B = Y1 - Y2
        local C = Z1 - Z2
        
        return math.sqrt(A * A + B * B + C * C);
    end

    function IsUnitWorker(unit)
        local unitTypeID = Jass.GetUnitTypeId(unit)
        
        if unitTypeID == 1752196449 or unitTypeID == 1869636975 or unitTypeID == 1969316719 or unitTypeID == 1702327152 then
            return true
        end
        
        return false
    end

    function IsUnitGoldmine(unit)
        local unitName = Jass.GetUnitName(unit)
        
        if unitName == "Gold Mine" then
            return true
        end
        
        return false
    end

    function table.contains(table, element)
        for _, value in pairs(table) do
            if value == element then
                return true
            end
        end
        return false
    end

    function table.getsize(table)
        local count = 0
        for _, value in pairs(table) do
            count = count + 1
        end
        return count
    end

    function table.clear(table)
        for k in pairs (table) do
            table[k] = nil
        end
    end

    function Initialize(plugin)
        plugin:SetName("Auto Mine")
        plugin:SetVersion("1.2")
        plugin:SetAuthor("Shahriyar")
        plugin:SetDescription("Lua Engine Sample Plugin")
        
        plugin:RegisterGameEvent(EVENT.GAME_STARTED, "OnGameStarted")
        plugin:RegisterGameEvent(EVENT.ENTER_LOADING, "OnEnterLoading")
        plugin:RegisterNativeHook("CreateUnit", "", "CreateUnit_Post")
        
        _plugin = plugin -- We are storing this for later use
    end

