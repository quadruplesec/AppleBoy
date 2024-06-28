# AppleBoy - A Gameboy Emulator in C
I began this project after awakening interesting in hardware emulation. I thought an old gaming system like the Nintendo Gameboy would be a good starter project, but it was nowhere as easy as I thought it would be.
This project has been incredibly useful: it has made me more profecient at programming in C and gave me a better understanding of early gaming hardware.

As of updating this README, I have added NO code of my own to this project, but I intend to expand on this project, seeing as the series that documented its development was dropped.

## How to Build
This project will ONLY build on Linux. Windows support is not planned at the moment.
I will give instructions on how to build this project in Debian/Ubuntu. 

First of all, you will need to install some dependencies:
```
sudo apt-get install build-essential git cmake libsdl2-dev libsdl2-ttf-dev check
```

Then, clone this repository to your own computer:
```
git clone https://github.com/quadruplesec/AppleBoy.git
```

When you are done, run this command to go inside of the new directory, create a build directory, and go inside of it:
```
cd AppleBoy && mkdir build && cd build
```

Once inside, run the following command to build the project using CMake:
```
cmake ..
```

Then, you simply have to run:
```
make
```

If compilation goes as it should, you can now run the emulator.

Place whatever roms you want to play inside of the `roms` directory, and run the following commands to run the emulator (while inside `/build`!):
```
gbemu/gbemu ../roms/[ROM NAME].gb
```

A window should pop up with your game! Simply close it to exit the emulator.

At the moment it is quite limited, but you should be able to play and save on most games made for the original Gameboy (ROM Only or MBC1).


![AppleBoy Demo](https://i.imgur.com/MhJu31I.png)
*Demonstration of AppleBoy playing a legally obtained copy of Legend of Zelda - Link's Awakening*

## Default Controls
At the moment, controls are not easily customisable. This is a planned feature.

For the time being, these are the default controls:

- `UP`: Up Arrow Key
- `DOWN`: Down Arrow Key
- `LEFT`: Left Arrow Key
- `RIGHT`: Right Arrow Key
- `START`: Enter Key
- `SELECT`: TAB Key
- `A`: X Key
- `B`: Z Key

## Limitations
At the moment, the emulator has very limited support, but should be able to play most popular titles.

- This emulator supports MBC1 ROMs (with battery saving and extra RAM banks) and ROM ONLY games.

- Games that use newer MBC mapping will not run. Support for newer MBC mappings is planned.

- Games for the Gameboy Color will NOT run. Support is not planned.

- This emulator also does not have audio. Support is not planned.

## Special Thanks
Special thanks to LowLevelDevel/rockytriton for providing the guide which I followed for the early stages of development. I could not have done this without his help.

If you wish to also follow his guide, you can find it in this [playlist](https://www.youtube.com/playlist?list=PLVxiWMqQvhg_yk4qy2cSC3457wZJga_e5)!


## Important References

https://gbdev.io/pandocs/

https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html

https://archive.org/details/GameBoyProgManVer1.1/page/n85/mode/2up

https://github.com/rockytriton/LLD_gbemu/raw/main/docs/The%20Cycle-Accurate%20Game%20Boy%20Docs.pdf

https://github.com/rockytriton/LLD_gbemu/raw/main/docs/gbctr.pdf


## Why the name?
My goal for this emulator was eventually being able to run a ROM that played the [Bad Apple!!](https://www.youtube.com/watch?v=FtutLA63Cp8) music video.

I have not as of yet implemented the MBC5 Mapper which is required to run the [Bad Apple!! ROM](https://github.com/elseyf/Bad-Apple-for-DMG-GameBoy)
