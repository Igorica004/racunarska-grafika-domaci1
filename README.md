U korenu projekta se već nalazi kompajliran program, tako da je moguće pokrenuti ga bez kompajliranja. Izvršna datoteka sa kojom se pokreće projekat se zove main.exe.

Projekat koristi CMake build sistem. CMake izvršne datoteke se nalaze u cmake folderu u korenu projekta. CMake automatski prepoznaje Visual Studio 2022 kompajler ako je instaliran na računaru, ne znam koja je procedura za druge kompajlere.

Uputstvo za kompajliranje:
1. Otvoriti terminal u folderu projekta.
2. Pokrenuti sledeće komande (svaka linija je odvojena komanda):

(inicijalizacija cmake-a)
cd .\build\
..\cmake\bin\cmake.exe ..

(vracanje u koren projekta)
cd ..

(kompajliranje projekta)
.\cmake\bin\cmake.exe --build build

(pokretanje projekta)
.\build\Debug\main.exe

