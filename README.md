# uscrypt tool 

A tool to encrypt files from one folder to another to ensure all your secrets stay that way. 

See the following points in order to use this application 

- [INSTALLATION](#installation) 
- [USAGE](#usage)
- [ERRORS](#errors) 

# Usage

The program really only has two commands, encrypt and decrypt which is all that is needed. 

Before proceeded please acknowledge that the key used for encrypting is "KEY!" and is public, change this before using uscrypt 

To encrypt an input folder with the directory of `input` to an output folder of  `output` 
Use the following command
```
./uscrypt encrypt input output
```

To decrypt its a similar pattern
```
./uscrypt decrypt input output
```

*Note that this is not been implemented to be recursive yet so all folders inside of folders will not be encrypted* 


# Installation

Clone the repository and then open that folder, and compile the program 
Remember to change line 14 to another key 
```#define KEY TheLongerTheBetter```
Feel free to change anything else for better usage 

### Linux 
Once inside of the folder open your terminal and run make 
```
git clone https://github.com/hiatus770/uscrypt.git
cd uscrypt
make
```

### Windows 
Do the same thing but in windows, (I dont know how) 

### Mac 
If you have make do the same thing but in Mac OS (I dont know how) 

# Errors

This program could become a buggy nightmare, inside of `main.c` there is a isDebug value, setting this to true can let you see whats going wrong and where. 
Common errors are not having proper permissions and incorrect fileDirectory 

