# Cryptic



<p>
    Cryptic is a simplistic encryption program I wrote in the C language for the sake of exploring the concept. 
</p>
<p>
    Using a quick hash program, to translate text passwords into integer keys, it runs an encryption formula to change each byte of a file into a four byte equivalent and then back again.
</p>

```
>>> cryptic enc message.txt 1234
Encrypting...
Your file "message.txt" has been encrypted with password "1234"
Exiting...
```
```
>>> cryptic dec message.txt 1234
Decrypting...

Your file, "message.txt", has been decrypted with password "1234"
Would you like to revert this decryption? WARNING: This action is irreversable!

  Enter [y/n]
  >>> n

Exiting...
```

<br>
<br>

# Setup

<mark>NOTE: Currently the setup guide is only written for Windows 10</mark>

 
Precompiled version for windows are included in <a href="./versions">versions</a>. Each should be named `cryptic.exe(v-{version number})`
<br>
To use one, remove the version number from the end of the file, and then proceed with the "Adding to PATH" instructions.

<h2>
    Compiling:
</h2>

1. Make sure you have gcc installed in your environment.
2. Download/Clone the repository to your device.
3. Navigate to src folder.
4. Run Make command to use the pre-written Makefile.
5. This will create a file cryptic.exe in the same folder that contains src.
 
<h2 id="PATH">
    Adding to PATH:
</h2>

1. Create a folder were you would like to store the Cryptic executable.
2. Move `cryptic.exe` to this folder.
3. Copy the filepath to that folder starting at your drive.
4. In Windows search bar, type `environment`, and open the option to `edit environement variables`.
5. Select `Environment Variables...`
6. Under `User variable for {user name}`, select `Path`, then click `Edit...`.
7. Click `New`.
8. Paste your filepath, from your drive to the folder containing `cryptic.exe`, and click `OK`.
9. Click `OK`.
10. Click `OK`.

* To test that it was added correctly, open your command prompt and type `cryptic`. You should recieve the error:

```
Missing argument: most likely {mode}
Try help for information
```

<br>
<br>

# Usage

<p>
    Once cryptic has been setup it can be used, from the command line, to encrypt text based files.
</p>

* Command usage

```
cryptic {mode} {filename} {password} 
cryptic help
```

* Argument definitions

| Argument | Description                               | Options                   |
|----------|-------------------------------------------|---------------------------|
| mode     | Specifies wheather to encrypt or decrypt  | `enc`/`dec`               |
| filename | Set path to the file being performed on   | fp from current directory |
| password | Password to be used in encryption formula | Password of your choosing |

* Special Arguments

<p>
    If any of these are used as the first argument, it enacts special behavior
</p>

| Argument | Description          |
|----------|----------------------|
| help     | Displays a help menu |

<br>
<br>

# Code Implementation 

<p> Hash </p>

```c
int hash(char* key, int max) {
    int result = 1;
    unsigned long sze = strlen(key);
    for (unsigned long i = 0; i < sze; i++) {
        if (result + (key[i] * key[i] - key[i])) result += (key[i] * key[i] - key[i]);
    }
    return (result % max) + 1;
}
```

<br>
<br>

<p> Encryption </p>

```c
void encrypt(char* fn, char* key, unsigned int hash_factor) {
    FILE* input = fopen(fn, "r");
    FILE* tmp = tmpfile();

    int new;
    int hashed = hash(key, hash_factor);
    while ((new = getc(input)) != EOF) {
        new = new * hashed + hashed;
        fwrite(&new, sizeof(int), 1, tmp); 
    }
    fclose(input);
    
    FILE* output = fopen(fn, "w");
    rewind(tmp);
    
    cpyfile(output, tmp);
    fclose(output);
}
```

<br>
<br>

# Warnings

* This program was written for education purposes! It is **not** recommended for use with **any** sensitive information!
* There is no guarentee this program will not permanently damage files! It is **not** recommended for use with any important files as they may be damaged beyond repair!
* Handling of passwords is left strictly in the hands of the user. Forgetting a password use for encryption may result in file being unrecoverable!
* Decrypting a file with an incorrect password may result in the file being unrecoverable! 
* After decrypting the program offers a **single** opportunity to revert the file to its encrypted state. To prevent the loss of date check your files contents before deciding not to revert.
* Though it **may** be possible to use this encryptor on any file with `bitsze % 8 == 0`, this is not necessarily the case. It is **not** recommended to use cryptic with any file other than those encoded with standard ASCII!