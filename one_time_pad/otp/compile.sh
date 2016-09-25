clang -c ./lib/otplib.cpp -std=c++11 -lstdc++ -o ./lib/otp.o
ar rcs ./lib/libotp.a ./lib/otp.o
gcc -static otp.cpp -lrt ./lib/libotp.a -o otp.exe -std=c++11 -lstdc++
