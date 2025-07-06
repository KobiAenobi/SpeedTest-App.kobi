# Speed_Test_App.kobi
An Internet Speed Test App with BACKEND using 'CPP' and 'CURL' library & FRONTEND  'C# WINDOWS PRESENTATION FOUNDATION' <br>

What is CURL?<br>

curl is a command-line tool and library used for transferring data with URLs. It's a versatile tool for interacting with web servers, APIs, and other services, supporting various protocols and features. Essentially, curl allows you to send and receive data to and from servers using a command-line interface.<br>
https://curl.se/<br>
'CURL' is designed for transferring data to and from servers using URLs.<br>
This TRANSFERRING OF FILES TO & FORM THE SERVERS is what is used to:
1. DOWNLOAD the data from a URL for DOWNLOAD TEST using Cloudflare’s speed testing infrastructure(https://speed.cloudflare.com/__down?bytes=10240000000) to download a 10240000000 bytes file.
2. UPLOAD the data to a cloud-hosted server (using https://railway.com free subscription right now to host my own server using PYTHON & FLASK.(https://github.com/KobiAenobi/upload-server.git). P.S. - you'll probably need to change the upload server link in the Upload_Test_App.cpp in the future.<br>

How to compile:-<br>
1. Download the Repo.
2. Install the CURL LIBRARY using 'vbpkg' in Visual Studio  (vbpkg install curl).
3. Open and build the SpeedTest Main.sln.
4. Open the C++ backend files and open and build the 'Download_Test_App.sln' & 'Upload_Test_App.sln'.
5. Now copy the files from the 'Download_Test_App' & 'Upload_Test_App' Build folders (usually at /x64/debug/) and paste into the 'SpeeTest Main.sln' Build folder, usually at /bin/build/.net8.0 windows/. Replace files if prompted.
6. Execute the program using 'SpeeTest Main.exe' in the build folder.
