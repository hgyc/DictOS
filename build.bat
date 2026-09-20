@echo off
setlocal
yasm -p gas -f bin -o bootsect.tmp bootsect.asm || exit /b 1
powershell -NoProfile -Command "$b=[IO.File]::ReadAllBytes('bootsect.tmp'); [IO.File]::WriteAllBytes('bootsect.bin', $b[0x7c00..($b.Length-1)])" || exit /b 1
del bootsect.tmp
cl.exe /nologo /GS- /c kernel.cpp || exit /b 1
link.exe /nologo /OUT:kernel.bin /BASE:0x10000 /FIXED /FILEALIGN:512 /MERGE:.rdata=.data /IGNORE:4254 /NODEFAULTLIB /ENTRY:kmain /SUBSYSTEM:NATIVE kernel.obj || exit /b 1
powershell -NoProfile -Command "foreach ($p in @(@('bootsect.bin','boot.img'),@('kernel.bin','kernel.img'))) { [IO.File]::Copy($p[0],$p[1],$true); $f=[IO.File]::Open($p[1],'Open'); $f.SetLength(1474560); $f.Close() }" || exit /b 1
for %%F in (kernel.bin) do echo kernel.bin: %%~zF bytes
echo OK. Run: qemu-system-i386 -fda boot.img -fdb kernel.img
endlocal
