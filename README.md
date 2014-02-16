openssl command line tools can be used to generate private key and
corresponding public key.

use this command to generate private key:
openssl genrsa -out private_key 1024

use this command to generate public key:
openssl rsa -in private_key -pubout -out public_key

The experiment shows that if the private key has been used to encrypted
message, the crypted text would be the same, which is unsafe.
