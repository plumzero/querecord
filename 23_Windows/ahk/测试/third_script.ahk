^j::
    MsgBox Wow!
    MsgBox this is
    Run, Notepad.exe
    Winactivate, Untitled - Notepad  ; 无标题 - 记事本
    WinWaitActive, Untitled - Notepad  ; 无标题 - 记事本
    Send, 7 lines{!}{enter}
    SendInput, inside the ctrl{+}j hotkey
Return