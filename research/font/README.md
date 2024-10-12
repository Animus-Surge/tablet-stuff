# PADD-PDA Research: Fonts

Creating a custom font handler in SDL2

## Purpose

The purpose of this research is to design my own font rendering scheme outside of SDL_ttf to work
with variable font sizes for quick resizing on the fly. This will allow animation systems to be able
to reposition and resize text without having to reload a texture every frame, and should in theory
allow for a much better memory use.

## Sources
TrueType Reference Manual: https://developer.apple.com/fonts/TrueType-Reference-Manual/

Google Fonts library: https://fonts.google.com/
