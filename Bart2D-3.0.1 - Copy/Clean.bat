@ECHO OFF
RMDIR /S/Q .vs
RMDIR /S/Q Bart2d\Debug
RMDIR /S/Q Game\Debug
7z a -tzip remise.zip "Bart2D" "Game" "Lib" "Bart2D.sln"