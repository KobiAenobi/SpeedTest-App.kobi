# Speed_Test_App.kobi
A Internet Speed Test App with BACKEND using CPP and CURL library & FRONTEND  C# WINDOWS PRESENTATION FOUNDATION.


What is CURL?
curl is a command-line tool and library used for transferring data with URLs. It's a versatile tool for interacting with web servers, APIs, and other services, supporting various protocols and features. Essentially, curl allows you to send and receive data to and from servers using a command-line interface.
curl is designed for transferring data to and from servers using URLs.
This TRANSFERRING OF FILES TO & FORM THE SERVERS is what is used to:
1. DOWNLOAD the data form a url for DOWNLOAD TEST using Cloudflare’s speed testing infrastructure(https://speed.cloudflare.com/__down?bytes=10240000000) to download a 10240000000 bytes file.
2. UPLOAD the data to a cloud hosted server (using https://railway.com free subscription right now to host my own server using PYTHON & FLASK. P.S - youll Probaly need to change the upload server link in the Upload_Test_App.cpp in future).


How to complie:-

1. Download the Repo.
2. install curl library using vbpkg in visual studio  (vbpkg install curl).
3. open and build the SpeedTest Main.sln.
4. open the c++ backend files and open and build the Download_Test_App.sln & Upload_Test_App.sln.
5. now copy the files from the Download_Test_App & Upload_Test_App Build folders (usually at /x64/debug/) and past into the SpeeTest Main.sln Build folder(usually at /bin/build/.net8.0 windows/).
6. execute the program using SpeeTest Main.exe in the build folder.
