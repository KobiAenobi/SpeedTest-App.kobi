# Speed_Test_App.kobi
An Internet Speed Test App with BACKEND using CPP and CURL library & FRONTEND  C# WINDOWS PRESENTATION FOUNDATION.


What is CURL?
curl is a command-line tool and library used for transferring data with URLs. It's a versatile tool for interacting with web servers, APIs, and other services, supporting various protocols and features. Essentially, curl allows you to send and receive data to and from servers using a command-line interface.

curl is designed for transferring data to and from servers using URLs.
This TRANSFERRING OF FILES TO & FORM THE SERVERS is what is used to:
1. DOWNLOAD the data from a URL for DOWNLOAD TEST using Cloudflare’s speed testing infrastructure(https://speed.cloudflare.com/__down?bytes=10240000000) to download a 10240000000 bytes file.
2. UPLOAD the data to a cloud-hosted server (using https://railway.com free subscription right now to host my own server using PYTHON & FLASK.. P.S. - you'll probably need to change the upload server link in the Upload_Test_App.cpp in the future).


How to compile:-

1. Download the Repo.
2. Install the CURL LIBRARY using vbpkg in Visual Studio  (vbpkg install curl).
3. Open and build the SpeedTest Main.sln.
4. Open the C++ backend files and open and build the Download_Test_App.sln & Upload_Test_App.sln.
5. now copy the files from the Download_Test_App & Upload_Test_App Build folders (usually at /x64/debug/) and past into the SpeeTest Main.sln Build folder, usually at /bin/build/.net8.0 windows/. Replace files if prompted.
6. execute the program using SpeeTest Main.exe in the build folder.
