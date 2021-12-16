#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
    FILE *fp;
    unsigned char magic[4];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s FILENAME\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "rb");  // open file
    if (fp == NULL) {
        perror("fopen failed"); // print Error Message
        return 1;
    }
    fread(magic,1,4,fp);
    //find magic number of file
    // if (fread(magic, 1, 4, fp) != 4) { // read first 4 bytes of file
    //     if (feof(fp)) 
    //         fputs("File is less than 4 bytes\n", stderr); //ghi 1 chuoi toi Stream da xac dinh (stderr)
    //     else
    //         fputs("Error reading the file\n", stderr);
    //     return 1;
    // }
    printf("%02hhx%02hhx%02hhx%02hhx\n",magic[0],magic[1],magic[2],magic[3]);
    // size of file
    fseek(fp, 0L, SEEK_END);
    long int res = ftell(fp);  // calculating the size of the file
    
    // close
    fclose(fp);  
    int loop;
    int i; 
    
    i=0;
    loop=0;
    char output[9];
    while(magic[loop] != '\0')
    {
        sprintf((char*)(output+i),"%02x", magic[loop]);
        loop+=1;
        i+=2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';

    //print
    puts("The magic number of your file is:");
    printf("%s\n", output);
    
    if (res!= -1){
        puts("Size of file:");
        printf("%d\n", res);
    }
    if (strstr(output,"7f454c46") != NULL) printf("File in type ELF\n");
    // if (strcmp(output,"7f454c46") > 0)
    //     printf("File in type ELF \n");
    return 0;
}