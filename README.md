# Podcast-Automator

This is a simple piece of code that uses a teensy 4.0 board to help my (mostly) blind use and operate a podcast recorder. I'm using Reaper64 to record his audio. Just put this on your teensy board, and it should work like a charm. Or, if you want, hook up some buttons, and be able to control your computer using big, visible arcade buttons. 

## Reaper Setup

Before you can use this, you'll need to add some reaper keyboard shortcuts, by clicking `Options -> Preferences -> Keyboard/Multitouch -> Assign keyboard shortcuts to actions or change existing shortcuts`. It will ask if you want to replace the remove the existing shortcut, just say yes; it's a duplicate shortcut of many.

| COMMAND | KEYBOARD SHORTCUT |
| ------- | ----------------- |
| Track: Arm all tracks for recording | Ctrl+9 |
| Track: Unarm all tracks for recording | Ctrl+8 |


## Wiring


![alt text](https://raw.githubusercontent.com/ntatko/Podcast-Automator/main/docs/fritzing_drawing.png)
