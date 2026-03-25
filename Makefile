CC=x86_64-w64-mingw32-g++
INJECTOR=injector.exe
DLL=mod.dll

all: $(DLL) $(INJECTOR)

$(DLL): dll.cpp
	$(CC) -shared -o $(DLL) dll.cpp

$(INJECTOR): injector.cpp
	$(CC) injector.cpp -o $(INJECTOR)

clean:
	rm -f $(INJECTOR) $(DLL)
