local ins3d
local win = ide.osname == "Windows"
local mac = ide.osname == "Macintosh"

return {
  name = "INS3D",
  description = "Insane 3D Engine",
  api = {"baselib", "ins3d"},
  frun = function(self,wfilename,rundebug)
    ins3d = ins3d or ide.config.path.ins3d -- check if the path is configured
    
    if not GetFullPathIfExists(self:fworkdir(wfilename), 'Main.lua') then
      DisplayOutput("Can't find 'Main.lua' file in the current project folder.\n")
      return
    end

    if rundebug then
      DebuggerAttachDefault({runstart = ide.config.debugger.runonstart == true})
    end

    local params = ide.config.arg.any or ide.config.arg.ins3d
    local cmd = ('"%s"'):format(ins3d)
    -- CommandLineRun(cmd,wdir,tooutput,nohide,stringcallback,uid,endcallback)
    return CommandLineRun(cmd,ins3d,true,true)
  end,
  fprojdir = function(self,wfilename)
    return wfilename:GetPath(wx.wxPATH_GET_VOLUME)
  end,
  fworkdir = function(self,wfilename)
    return ide.config.path.projectdir or wfilename:GetPath(wx.wxPATH_GET_VOLUME)
  end,
  hasdebugger = true,
  fattachdebug = function(self) DebuggerAttachDefault() end,
  scratchextloop = true,
  takeparameters = true,
}
