#include <iostream>
#include "Image_Class.h"
#include <cmath>
#include <string>
#include <limits>
/*Author1: Ahmed Attia Abozaid Mahgoub ID[20230027] Solved Filter 1
  Author2: Anas Emad Ahmed ID[20230070] solved Filter 2, 5 and 11
  Author3: Blal Mohammed Omar ID[20230097] solved filter 3
  Section 7 and 8
  this is the file of program do photoshop filters as grayscale, black and white,
  flip image vertically or horizontally, invert and resize the image with inputed dimensions.
  
  file name: CS112_A3_Part1_S7andS8_20230027_20230070_20230097
  Only choose filters with numbers 1,2,3,5,11 as they are solved 
*/
Image currentImage,originalImage;

using namespace std;
// Nearest Neighbor Interpolation
void resizeImageNearestNeighbor( Image& currentImage, Image& resizedImage, int newWidth, int newHeight) {
    // Calculate scaling factors
    float scaleX = static_cast<float>(currentImage.width) / newWidth;
    float scaleY = static_cast<float>(currentImage.height) / newHeight;

    // Loop through each pixel in the resized image
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate corresponding position in the source image
            int sourceX = round((x * scaleX));
            int sourceY = round((y * scaleY));

            // Set pixel value in the resized image to the nearest neighbor pixel value from the source image
            for (int k = 0; k < 3; ++k) {
                resizedImage.setPixel(x, y,k, currentImage.getPixel(sourceX, sourceY,k));
            }


        }
    }
}




int main() {

    string filename;
    while (true) {
        int choice;
        cout <<"Welcome to our photoshop program ^_^ \n";
        while (filename.empty() ) {

                cout << "Please enter the name of the image to add a filter: ";
                getline(cin,filename);
                originalImage = Image(filename);
                currentImage = originalImage;

            }
        
        cout << "0- load a new image: \n"
             << "1- Graysclae filter \n"
             << "2- Black and White filter \n"
             << "3- Invert Image filter \n"
             << "4- Merge Images filter \n"
             << "5- Flip Image filter \n"
             << "6- Rotate Image filter \n"
             << "7- Darken and Lighten Image filter \n"
             << "8- Crop Images filter \n"
             << "9- Adding a Frame to the Picture filter \n"
             << "10- Detect Image Edges filter \n"
             << "11- Resizing Images filter \n"
             << "12- Blur Images filter \n"
             << "13- End\n"
             << "14- Save image \n"
             <<"Please enter the number of the operation you want to do: ";
        cin >> choice;

        if (cin.fail()) {
            // Input was not an integer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the buffer
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(); // Clear the newline character from the buffer

        if (choice==0)
        {
            char c;
            cout<<"Do you want to save the current one before loading a new one(y/n): ";
            cin>>c;
            if(c=='y'){
                cin.ignore();
                cout<<"Do you want to save the image with the same name or change it(y/n):";
                cin>>c;
                if(c=='y'){
                    currentImage.saveImage(filename);
                    cout<<"Saved succesfully\n";
                }
                else if (c=='n')
                {
                    cin.ignore();
                    string name;
                    cout<<"Enter the new name for the image with one of the following extention (.jpg, .bmp, .png, .tga): ";
                    getline(cin,name);
                    currentImage.saveImage(name);
                    cout<<"Saved succesfully\n";
                }
                else
                    cout<<"Invalid input pls choose (y or n): ";

            }
            else if (c=='n')
            {
                
                cin.ignore();
                cout << "Please enter the name of the image to add a filter: ";
                getline(cin,filename);
                originalImage = Image(filename);
                currentImage = originalImage;
            }
            else
                cout<<"Invalid input pls choose (y or n): \n";
            
            
        }
        
        else if (choice == 1) {
            currentImage = originalImage;
            for(int i=0 ;i<currentImage.width; ++i){
                for(int j=0 ;j< currentImage.height; ++j){
                    unsigned int average = 0 ;
                    for (int k = 0; k < 3; ++k) {
                        average+= currentImage(i,j,k);

                    }       
                    average = average/3 ;
                    for (int k = 0; k < 3; ++k) {
                        currentImage(i,j,k)=average;
                    }

                }
                
            }
            
    
    
        }
        else if(choice==2){
            currentImage = originalImage;
            for (int i = 0; i < currentImage.width; i++) {
                for (int j = 0; j < currentImage.height; j++) {
                    unsigned int avg = 0;
                    unsigned int threshold = 127;
                    for (int k = 0; k < 3; k++) {
                        avg += currentImage(i, j, k); // Corrected
                    }
                    avg /= 3;
                    unsigned char color = (avg > threshold) ? 255 : 0; // Set to white or black
                    for (int l = 0; l < 3; l++) {
                        currentImage(i, j, l) = color; // Corrected
                    }
                }
            }

        }
        else if(choice==3){
            currentImage = originalImage;
            for (int i = 0; i < currentImage.width; ++i) {
                for (int j = 0; j < currentImage.height; ++j) {
                // Assuming image(i, j, k) accesses the k-th color channel of the pixel at (i, j)
                    for (int k = 0; k < 3; ++k) {
                        currentImage(i, j, k) = 255 - currentImage(i, j, k); // Invert color channel
                    }
                }
            }
            
            

        }
        else if(choice==4){
            


        }
        else if(choice==5){
            currentImage = originalImage;
            Image flipped(currentImage.width, currentImage.height);
            int num;
            cout <<"1- Flip Horizontally\n"<<"2- Flipped Vertical\n"<<"choose the number of which flip you want(1/2):";
            cin>>num;
            if (num==1)
            {
                for (int i = 0; i < currentImage.width; i++){
                    for (int j = 0; j < currentImage.height; j++){
                    int new_width = currentImage.width - 1 - i;
                        for (int k = 0; k < 3; k++){
                            flipped(i, j, k) = currentImage(new_width, j, k);
                        }
                    }
                }
                currentImage=flipped;
            }
            else if (num==2)
            {
                for (int i = 0; i < currentImage.width; i++){
                    for (int j = 0; j < currentImage.height; j++){
                        int new_height = currentImage.height - 1 - j;
                        for (int k = 0; k < 3; k++){
                            flipped(i, j, k) = currentImage(i, new_height, k);
                        }
                    }
                }
                currentImage=flipped; 
            }
            else
                cout<<"Invalid input pls choose (1 or 2): \n";
        }
        else if(choice==6){

        }
        else if(choice==7){

        }
        else if(choice==8){

        }
        else if(choice==9){

        }
        else if(choice==10){

        }

        else if (choice==11){
            currentImage = originalImage;
            int width, height;

            cout<<"Please enter the width: ";
            cin>>width;
            cout<<"\nPlease enter the height: ";
            cin>>height;
            Image resizedImage(width,height);
            resizeImageNearestNeighbor(currentImage,resizedImage,width,height);
            currentImage= resizedImage;

        }

        else if(choice==12){

        }

        else if (choice == 13) {
            char c;
            cout<<"Do you want to save the current one before exiting (y/n)?:";
            cin>>c;
            if(c=='y'){
                cin.ignore();
                cout<<"Do you want to save the image with the same name or change it(y/n):";
                cin>>c;
                if(c=='y'){
                    currentImage.saveImage(filename);
                    cout<<"Saved succesfully\n";
                    cout << "Ending the program. Goodbye ^_^ ";
                    break;
                }
                else if (c=='n')
                {
                    cin.ignore();
                    string name;
                    cout<<"Enter the new name for the image with one of the following extention (.jpg, .bmp, .png, .tga): ";
                    getline(cin,name);
                    currentImage.saveImage(name);
                    cout<<"Saved succesfully\n";
                    cout << "Ending the program. Goodbye ^_^ ";
                    break;
                }
                else
                    cout<<"Invalid input pls choose (y or n): ";

            }
            else if (c=='n')
            {
                cout << "Ending the program. Goodbye ^_^ ";
                break;
            }
            else
                cout<<"Invalid input pls choose (y or n): \n";
        }
        else if (choice==14)
        {
            char c;
            cout<<"Do you want to save the image with the same name or change it(y/n): ";
            cin>>c;
            if(c=='y'){
                currentImage.saveImage(filename);
                cout<<"Saved succesfully\n";
            }
            else if (c=='n')//error when choose n
            {
                cin.ignore();
                string name;
                cout<<"Enter the new name for the image with one of the following extention (.jpg, .bmp, .png, .tga): ";
                getline(cin,name);
                currentImage.saveImage(name);
                cout<<"Saved succesfully\n";
            }
            else
                cout<<"Invalid input pls choose (y or n): ";
                
        }
        
        else {
            cout << "\nInvalid input. Please choose number from 1 to 12 only\n";
        }
    }
    return 0;
}