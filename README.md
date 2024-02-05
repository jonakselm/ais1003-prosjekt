# Android Tetris with SFML

This is a basic tetris made using the MVC coding pattern.
It is built using a custom built SFML for arm64-v8a or armeabi-v7a,
more info on that here:
https://github.com/SFML/SFML/wiki/Tutorial:-Building-SFML-for-Android

To build this project you need to create your own local.properties file
which tells gradle where to find the android sdk and ndk

In addition to SFML, building this requires cmake and gradle for compiling and android ndk and sdk to build for the android platform 
