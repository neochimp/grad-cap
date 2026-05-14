# Cameron's Epic Grad Cap

## SDSU Class of 2026!

I am graduating with my bachelor's this year from SDSU and I am extra asf.

## Displaying Images

In order to display images on the cap you pass a vector of strings that represent each pixel to draw functions that then assign the color values to the leds e.g.:
```
const std::vector<std::string> sdsu = {
  ".........www...............wwwww",
  "........wwrww..............w...w",
  ".......wwrrcrww...........www...w",
  "......wwrrrrrww....wwww..w.....w",
  ".....wwrrrrrrrwwwwww..wwww...www",
  "....wwrrrrrrrrrww............w..",
  "...wwrrrrrrrrrrw...........www..",
  "..wwrrrrrwwrrrrrw..........ww...",
  ".wwrrrrrwwwwrrrrrwww........w...",
  "wwrrrrrrww..wrrrrwwwww......w...",
  "wrrrrrrrr....wrrwwwwwww.....w...",
  "wwrrrrrr.....wrwwwrrwwww....w...",
  ".wwrrrr.....wwwwwrrrrrww....w...",
  "..wwrr....wwwwwwrrrrrrrw....w...",
  "...ww....wrrrwwrrrrrrrrr....w...",
  "...w....wrrrrrrrrrrrrrrr...ww...",
  "..ww....wrrrrrrrrrrwrrrw...w....",
  ".ww....wrrrrrrrrrrwwwrw...www...",
  "ww....wwwrrrrrrrrwwwww...wwrww..",
  "w.......wwwrrrrrwwwwww...wrrrww.",
  "w........wwwrrrwwwww....wrrrrrww",
  "ww........wwwrwwrrw....wwrrrrrrw",
  ".www.......wwwwrrrrw..wwwwrrrrrw",
  "...ww.......wwwrrrrrwwwwwrrrrrww",
  "...ww........wwwrrrrrwwwrrrrrww.",
  "..ww..........w.wrrrrrwrrrrrww..",
  ".ww..............wrrrrrrrrrww...",
  ".w....www........wrrrrrrrrww....",
  ".w...ww.ww......wwwrrrrrrww.....",
  ".ww.ww...w.....ww.wwrrrrww......",
  "..www....ww...ww...wwrrww.......",
  "..........ww.ww.....wwww........"
};
```

## PNG to 2D Array Script
In order to prevent me from going insane when trying to convert pixel arts to the code, I have made a short python script that outputs string vector needed based on an inputted .png file.
```
python png_to_vector.py <filename.png>
```
