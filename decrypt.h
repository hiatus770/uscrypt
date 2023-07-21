/*
* This is the decrypt header files which handles the decryption of the encrypted file
*/
char* decrypt(char* data, char* key){
    char *encryptedData = malloc(strlen(data) * sizeof(char));
    for (int i = 0; i < strlen(data); i++){
        encryptedData[i] = ((data[i]-40 ) ^ key[i % strlen(key)]);
    }
    return encryptedData;
}
