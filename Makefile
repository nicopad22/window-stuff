CFILES=src/main.c src/graphics.c src/player.c
LIBS=user32.lib gdi32.lib
CFLAGS=/Zi /nologo
DEFINES=/DUNICODE /D_UNICODE
EXENAME=game.exe

game: $(CFILES)
	cl $(CFILES) $(CFLAGS) $(LIBS) $(DEFINES) /Fe$(EXENAME)
