^b::  ; Ctrl+B 热键
    Send, {ctrl down}c{ctrl up}  ; 复制选定的文本. 也可以使用 ^c, 但这种方法更加可靠.
    SendInput, [b]{ctrl down}v{ctrl up}[/b] ; 粘贴所复制的文本, 并在文本前后加上加粗标签.
Return  ; 热键内容结束, 这之后的内容将不会触发.