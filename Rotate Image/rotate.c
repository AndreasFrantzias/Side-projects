#include <stdio.h>
#include <stdlib.h>

//Συνάρτηση που παιρνει ως είσοδο τον πίνακα με την αρχική εικόνα και την στρίβει 90 μοίρες δεξιόστροφα στον πινακα rimage
void rotateimage(unsigned char **image,unsigned char **rimage,int width,int height){
    for (int j = 0; j < width; j++) {
        for (int i = height - 1; i >= 0; i--) {
            rimage[width - 1 - j][i * 3] = image[i][j * 3]; // Κόκκινο
            rimage[width - 1 - j][i * 3 + 1] = image[i][j * 3 + 1]; // Πράσινο
            rimage[width - 1 - j][i * 3 + 2] = image[i][j * 3 + 2]; // Μπλε
        }
    }
}

int main() {
    FILE* inputfile = stdin; 
    // Δέσμευση μνήμης με κεφαλίδα της εικόνας 
    unsigned char header[54];
    size_t bytesread;

    // Διάβασμα της κεφαλίδας της εικόνας
    bytesread = fread(header, sizeof(unsigned char), 54, inputfile);
    if (header[0] != 'B' || header[1] != 'M') {
        return 1; 
    }
    //Έλεγχος αν header είναι μικρότερος απο 54 
    if(bytesread<54){
        return 1;
    }

    //Ελέγχουμε αν χρησιμοποιεί 24-bit για την αναπαράσταση χρώματος
    unsigned int colordepth=*(int*)&header[28];
    if(colordepth!=24){
        return 1;
    }

    // Εξαγωγή πλάτους,ύψους και υπολογισμός padding από την κεφαλίδα
    int width,height,padding;
     height = *(int*)&header[22]; 
     width = *(int*)&header[18]; 
     padding = (4 - (width * 3) % 4) % 4;

    // Δημιουργία δυναμικού δισδιάστατου πίνακα και δεύσμευση μνήμης  για την αρχική εικόνα
    unsigned char** image = (unsigned char**)malloc(height * sizeof(unsigned char*));
    for (int i = 0; i < height; i++) {
        image[i] = (unsigned char*)malloc((width * 3 + padding) * sizeof(unsigned char));
    }
    //Έλεγχος αν εκτελέστηκε επιτυχώς η δέσμευση μνημης
    if(image==NULL){
        for(int i=0;i<height;i++){
            free(image[i]);
        }
        free(image);
        return 1;
    }

    // Διάβασμα δεδομένων εικόνας στον πίνακα image
    for (int i = 0; i < height; i++) {
        bytesread = fread(image[i], sizeof(unsigned char),padding+(width * 3), inputfile);
    }

    // Έλεγχος εάν διαβάστηκαν όλα τα bytes
    size_t expectedbytes = (width * 3) + padding;
    if (bytesread != expectedbytes) {
        return 1;
    }

    // Δημιουργία δυναμικού δισδιάστατου πίνακα και δέσμευση μνήμης για την περιστραμμένη εικόνα
    unsigned char** rimage = (unsigned char**)malloc(width * sizeof(unsigned char*));
    for (int i = 0; i < width; i++) {
        rimage[i] = (unsigned char*)malloc((height * 3) * sizeof(unsigned char));
        if (rimage[i] == NULL) {
            for (int j = 0; j < height; j++) {
                free(image[j]);
            }
            free(image);
            for (int j = 0; j < i; j++) {
                free(rimage[j]);
            }
            free(rimage);
            return 1; 
        }
    }

    //Κάλεσμα συνάρτησης για την περιστοφή της εικόνας
    rotateimage(image,rimage,width,height);

    // Ενημέρωση της κεφαλίδας για την περιστραμμένη εικόνα
    unsigned char rheader[54];
    for (int i = 0; i < 54; i++) {
        rheader[i] = header[i];
    }

    *(int*)&rheader[18] = height; // Ενημέρωση πλάτους με το αρχικό ύψος
    *(int*)&rheader[22] = width; // Ενημέρωση ύψους με το αρχικό πλάτος
    int rpadding = (4 - (height * 3) % 4) % 4; // Padding για την περιστραμμένη εικόνα

    FILE* outputfile = stdout;
    // Γράψιμο της κεφαλίδας της περιστραμμένης εικόνας στο outputfile
    fwrite(rheader, sizeof(unsigned char), 54, outputfile);

    // Γράψιμο της περιστραμμένης εικόνας στο outputfile
    for (int i = 0; i < width; i++) {
        fwrite(rimage[i], sizeof(unsigned char), (height * 3), outputfile);
        // Προσθήκη padding για την περιστραμμένη εικόνα
        for (int j = 0; j < rpadding; j++) {
            fputc(0, outputfile);
        }
    }

    // Απελευθέρωση  δεσμευμένης μνήμης πίνακα περιστραμμένης εικόνας
    for (int i = 0; i < width; i++) {
        free(rimage[i]);
    }
    free(rimage);

    // Απελευθέρωση  δεσμευμένης μνήμης αρχικής εικόνας
    for (int i = 0; i < height; i++) {
        free(image[i]);
    }
    free(image);

    return 0;
}
