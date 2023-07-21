/*
* This is the header file, this has the encrypt function which handles symmetric encryption of the data
*/

/**
 * @brief Encrypts data using XOR operation  
 * 
 * @param data 
 * @param key 
 * @return char* 
 */
char* encrypt(char* data, char* key){
    char *encryptedData = malloc(strlen(data) * sizeof(char));
    for (int i = 0; i < strlen(data); i++){
        encryptedData[i] = (data[i] ^ key[i % strlen(key)]) + 40;
    }
    return encryptedData;
}