# Podcast-Automator

This is a simple piece of code that uses a teensy 4.0 board to help my (mostly) blind grandfather use and operate a podcast recorder. I'm using Reaper64 to record his audio. Just hook up some buttons, and be able to control your computer using big, visible arcade buttons. 

## Reaper Setup

Before you can use this, you'll need to add some reaper keyboard shortcuts, by clicking `Options -> Preferences -> Keyboard/Multitouch -> Assign keyboard shortcuts to actions or change existing shortcuts`. It will ask if you want to replace the remove the existing shortcut, just say yes; it's a duplicate shortcut of many.

| COMMAND | KEYBOARD SHORTCUT |
| ------- | ----------------- |
| Track: Arm all tracks for recording | Ctrl+9 |
| Track: Unarm all tracks for recording | Ctrl+8 |


## Why this layout?

If you make your own version, you have the right to lay out your buttons any way you choose. That being said, if you're putting your buttons into a project box that has rotational symmetry, take that into consideration. A triangle and a square have different rotational symmetries, so as long as you're holding the sides and the buttons point away from you, you're holding it right.

## Parts List

*To buy*
* [Light up buttons](https://www.amazon.com/gp/product/B06XBLH25X/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
* [Teensy 4.0](https://www.amazon.com/PJRC-Teensy-4-0-Without-pins/dp/B07W5J3WNH/ref=sr_1_2?dchild=1&keywords=teensy+4.0&qid=1606692355&sr=8-2)
* [Project box](https://www.amazon.com/gp/product/B083HSD9HZ/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
* [Terminal block](https://www.amazon.com/gp/product/B076BR7RSH/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)

*Tools, etc*
* Soldering iron, solder, third hand
* Wire stripper
* crimper

I didn't include wire or connectors in this, because you can do whatever you want to connect things: speaker wire or leftover phone cord, terminal connectors or soldered directly, I won't dictate your preference


## Wiring
Fritzing wiring diagram

<img alt="simple fritzing wiring diagram" src="https://raw.githubusercontent.com/ntatko/Podcast-Automator/main/docs/fritzing_drawing.png" width="600"/>


The teensy and terminal block

<img alt="teensy and terminal block" src="https://raw.githubusercontent.com/ntatko/Podcast-Automator/main/docs/wiring_terminal_block.jpg" width="600"/>


The buttons, all wired up

<img atl="back of buttons" src="https://raw.githubusercontent.com/ntatko/Podcast-Automator/main/docs/wiring_buttons.jpg" width="600"/>

