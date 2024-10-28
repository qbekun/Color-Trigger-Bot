# Simple Pixel Trigger Bot

## Description
The Simple Pixel Trigger Bot is a lightweight application designed for gamers who want to automate shooting actions based on pixel color changes on the screen. By monitoring specific pixel colors, the bot can perform a mouse click automatically whenever a target color is detected, enhancing gameplay efficiency.

## Features
- **Pixel Color Detection**: Continuously monitors the color of a specified pixel on the screen.
- **Automated Mouse Clicking**: Simulates a left mouse click when a color change is detected that exceeds a defined threshold.
- **User-Friendly Controls**: Start monitoring color changes by pressing the 'X' key and stop monitoring upon release.
- **Graceful Exit**: The program can be terminated by pressing the 'End' key.

## How It Works
1. The program retrieves the current color of a pixel located at the cursor's position plus a small offset.
2. It continuously checks for color changes while the 'X' key is held down.
3. If a significant color difference is detected (beyond the defined threshold), the bot simulates a mouse click.
4. The monitoring will stop once the 'X' key is released.

## Requirements
- C++ compiler (e.g., Microsoft Visual Studio)

## How to Use
1. Compile the program with a C++ compiler.
2. Run the executable.
3. Move your mouse to the area of interest on the screen.
4. Press 'X' to start monitoring the pixel color.
5. The bot will click whenever a color change is detected.
6. Press 'End' to terminate the program.

## Warning
Using automated tools in online games may violate the game's terms of service and result in account bans. Use this tool responsibly and at your own risk.
