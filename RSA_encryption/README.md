# Public Key Cryptography

This project is all about cryptography. There is a keygen
file that can generate a public key and private key. There is
an encyptor file that can encrypt input files onto output
files. There is also a decryptor file that can decrypt input
files onto output files. Encrypting a file and then decrypting
it should get you the original file again.

## Building 

Build all three programs with:

```
make
```

Build just keygen with:

```
make keygen
```

Build just encrypt with:

```
make encrypt
```

Build just decrypt with:

```
make decrypt
```

## Running

Run keygen with:

```
$ ./keygen [-hv] [-b bits] -n pbfile -d pvfile
```

Run encrypt with:

```
$ ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey
```

Run decrypt with:

```
$ ./decrypt [-hv] [-i infile] [-o outfile] -n privkey
```


