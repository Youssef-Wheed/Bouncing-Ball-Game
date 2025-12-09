# Bouncing Ball Game in C++ (SFML)

## Overview

This is a simple **Bouncing Ball game** implemented in **C++** using the **SFML library**.
The game features a ball moving inside a window that **bounces off the edges**.
Each time the ball hits a wall, it **changes color** randomly.

---

## Features

* Smooth ball movement with adjustable speed.
* Random color change upon collision with window boundaries.
* Works with keyboard/mouse events (optional interaction to change color).
* Built using **SFML 2.6.1** (Graphics, Window, System modules).

---

## Requirements

* Windows OS
* **C++ Compiler (g++)** — part of MinGW
* **SFML 2.6.1** for Windows (GCC version)

---

## Installation & Setup (Windows CMD)

### 1. Install MinGW (C++ Compiler)

Check if g++ is installed:

```cmd
g++ --version
```

If not installed:

1. Download MinGW installer:

```cmd
curl -L -o mingw.exe https://sourceforge.net/projects/mingw/files/latest/download
```

2. Run the installer:

```cmd
mingw.exe
```

3. In the installer, select `mingw32-gcc-g++`, mark it for installation, and apply changes.
4. Add MinGW to PATH:

```cmd
setx PATH "%PATH%;C:\MinGW\bin"
```

5. Restart CMD and verify:

```cmd
g++ --version
```

---

### 2. Download SFML

```cmd
curl -L -o sfml.zip https://www.sfml-dev.org/files/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit.zip
powershell -command "Expand-Archive sfml.zip -DestinationPath sfml"
```

### 3. Set SFML Environment Variable

```cmd
setx SFML "C:\path\to\sfml\SFML-2.6.1"
```

> Replace the path with your actual SFML folder location.

---

### 4. Copy DLL Files

Navigate to your project folder (where `bouncing_ball.cpp` is located) and run:

```cmd
copy "%SFML%\bin\*.dll" .
```

---

### 5. Compile the Game

```cmd
g++ bouncing_ball.cpp -o ball ^
 -I"%SFML%\include" ^
 -L"%SFML%\lib" ^
 -lsfml-graphics -lsfml-window -lsfml-system
```

---

### 6. Run the Game

```cmd
ball.exe
```

You should see a window with a bouncing ball that changes color every time it hits a wall.

---

## Code Explanation

### Ball Initialization

```cpp
sf::CircleShape ball(radius);
ball.setOrigin(radius, radius); // Center origin
ball.setPosition(WINDOW_W/2.f, WINDOW_H/2.f);
ball.setFillColor(randomColor());
```

* Creates a circular shape.
* Sets origin to the center for easier movement.
* Positions the ball in the middle of the window.
* Assigns a random color.

### Ball Movement

```cpp
pos += velocity * dt;
ball.setPosition(pos);
```

* Updates position based on velocity and delta time.
* Ensures smooth movement independent of frame rate.

### Collision Detection

```cpp
if (pos.x - radius <= 0.f || pos.x + radius >= WINDOW_W) velocity.x = -velocity.x;
if (pos.y - radius <= 0.f || pos.y + radius >= WINDOW_H) velocity.y = -velocity.y;
```

* Checks for collisions with window boundaries.
* Reverses the direction (X or Y) upon collision.
* Changes ball color when a wall is hit.

---

## Optional Extensions

* Multiple balls with different speeds and colors.
* Score system based on wall hits.
* Sound effects on collisions using `sf::Sound`.
* Variable ball sizes or interactive controls.

---

## License

This project is **open-source**. You can modify and use it freely.

---

## Author

**Youssef Wheed**
Embedded Systems & C++ Enthusiast
