#include <iostream>
#include "Image_Class.h"
#include <cmath>
#include <string>
#include <limits>
/*Author1: Ahmed Attia Abozaid Mahgoub ID[20230027] Solved Filter 1 ,7 ,4 and 10 and 
  did bonus filters 13(sunlight) and 16(purple) alone
  Author2: Anas Emad Ahmed ID[20230070] solved Filter 2, 5 and 11
  Author3: Blal Mohammed Omar ID[20230097] solved filter 3
  Section 7 and 8
  this is the file of program do photoshop filters as grayscale, black and white,
  flip image vertically or horizontally, invert and resize the image with inputed dimensions and other filters.
  
  file name: CS112_A3_Part2B_S7andS8_20230027_20230070_20230097
   

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



Image merge_Images(Image currentImage, Image second){
    int width=max(currentImage.width,second.width); //get max width to set the dimension of merged image and the loop
    int height=max(currentImage.height,second.height);//get max height to set the dimension of merged image and the loop
    Image merged(width,height); 
    for (int i = 0; i < width; i++)
    {
        for(int j = 0 ;j < height; j++){
            for (int k = 0; k < 3; k++)
            {
                unsigned int avg = (currentImage.getPixel(i,j,k) + second.getPixel(i,j,k)) / 2;
            
                merged.setPixel(i, j, k,avg) ;
            }
                
        }
    }
    return merged;
     

}


Image Crop_Filter(Image currentImage, int x,int y, int width, int height) {
    

    Image image2(width,height);
    for (int i = 0 ; i < image2.width ; i++) {
        for (int j = 0 ; j < image2.height ; j++) {
            int old_width = x + i - 1;
            int old_height = y + j - 1;
            for (int k = 0; k < 3; k++) {
                image2(i, j, k) = currentImage(old_width , old_height , k);
            }
        }
    }
    return image2;
    
}



Image purple_Image(Image& currentImage){
    const int intensity = 5; // Adjust this value to control the intensity of the effect
    for(int i=0 ;i<currentImage.width; ++i){
        for(int j=0 ;j< currentImage.height; ++j){
            

            // Increase the intensity of each RGB channel with light purple color
            currentImage(i, j, 0) = min(currentImage(i, j, 0) + intensity, 255);
            currentImage(i, j, 1) = min(currentImage(i, j, 1) + intensity, 120);
            currentImage(i, j, 2) = min(currentImage(i, j, 2) + intensity, 255);
        }
                
    }
            
    return currentImage;

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
             << "9- Adding a Frame to the currentImageture filter \n"
             << "10- Detect Image Edges filter \n"
             << "11- Resizing Images filter \n"
             << "12- Blur Images filter \n"
             << "13- natural sunlight\n"
             << "14- purple \n"
             << "15- End\n"
             << "16- Save the image\n"
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
            currentImage = originalImage;
            string name2;
            Image second, mergedImage;
            cout << "Enter the file name of the second image: ";
            getline(cin,name2);
    
            second.loadNewImage(name2);
    
            if(currentImage.width==second.width && currentImage.height==second.height){
                mergedImage=merge_Images(currentImage,second);
        
            }
            else if (currentImage.width != second.width || currentImage.height != second.height ){

                cout<<"1-Merge the common area\n"
                    <<"2-Resize the two images then merge\n"
                    <<"3-Resize the small image\n"
                    <<"Choose which one you want: ";
                int num;
                cin>>num;
                if(num==1){
                   int min_width= min(currentImage.width,second.width);
                   int min_height= min(currentImage.height,second.height);
                   if(currentImage.width>second.width || currentImage.height>second.height){
                        currentImage = Crop_Filter(currentImage, 1, 1 ,min_width, min_height);
                   }
                   else if(currentImage.width<second.width || currentImage.height<second.height){
                        second = Crop_Filter(second, 1, 1 ,min_width, min_height);
                   }
                   mergedImage=merge_Images(currentImage,second);
                
                }
                else if(num==2){
                    int max_width=max(currentImage.width,second.width); 
                    int max_height=max(currentImage.height,second.height);
                    Image resized1(max_width,max_height), resized2(max_width,max_height);
                    resizeImageNearestNeighbor(currentImage,resized1,max_width,max_height);
                    currentImage=resized1;
                    resizeImageNearestNeighbor(second,resized2,max_width,max_height);
                    second=resized2;

                    mergedImage=merge_Images(currentImage,second);
                }
                else if(num == 3){
                    if(currentImage.width < second.width && currentImage.height > second.height){
                        int max_width=max(currentImage.width,second.width); 
                        int max_height=max(currentImage.height,second.height);
                        Image resized1(max_width,max_height), resized2(max_width,max_height);
                        resizeImageNearestNeighbor(currentImage,resized1,max_width,max_height);
                        currentImage=resized1;
                        resizeImageNearestNeighbor(second,resized2,max_width,max_height);
                        second=resized2;

                        mergedImage=merge_Images(currentImage,second);

                    }
                    else if ( second.width  <  currentImage.width  &&  second.height > currentImage.height )
                    {
                        int max_width=max(currentImage.width,second.width); 
                        int max_height=max(currentImage.height,second.height);
                        Image resized1(max_width,max_height), resized2(max_width,max_height);
                        resizeImageNearestNeighbor(currentImage,resized1,max_width,max_height);
                        currentImage=resized1;
                        resizeImageNearestNeighbor(second,resized2,max_width,max_height);
                        second=resized2;

                        mergedImage=merge_Images(currentImage,second);

                    }
                
                    else if ( currentImage.width < second.width || currentImage.height < second.height){
                        int max_width=max(currentImage.width,second.width); 
                        int max_height=max(currentImage.height,second.height);
                        Image resized1(max_width,max_height);
                        resizeImageNearestNeighbor(currentImage,resized1,max_width,max_height);
                        currentImage=resized1;
                        mergedImage=merge_Images(currentImage,second);

                    }
                    else if ( second.width < currentImage.width  || second.height < currentImage.height)
                    {
                        int max_width=max(currentImage.width,second.width); 
                        int max_height=max(currentImage.height,second.height);
                        Image resized1(max_width,max_height);
                        resizeImageNearestNeighbor(second,resized1,max_width,max_height);
                        second=resized1;
                        mergedImage=merge_Images(currentImage,second);
                    }
                

                }
                else{
                cout<<"Invalid number please choose 1 or 2 or 3";
                }

            }
            currentImage= mergedImage;
            
            


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
            currentImage = originalImage;
            int number,value;
            
            cout<<"1-Lighten the image\n"
            <<"2-Darken the image\n"
            <<"Choose 1 for lighten 2 for darken: ";
            cin>>number;
            if (number==1)//lighten the image
            {   
                for(int i=0;i<currentImage.width;++i){
                    for (int j = 0; j < currentImage.height; j++)
                    {
                        for(int k=0; k<3; k++){//To lighten image by 50% multiply pixel value by 1.5 or 
                            value =1.5*currentImage.getPixel(i,j,k);
                            value= min(255,value);// to ensure value of pixel does not exceed 255 
                            currentImage.setPixel(i, j, k,value);
                        }
                    }
        
                } 
            }
            else if (number==2){ //darken the image

                for(int i=0;i<currentImage.width;++i){
                    for (int j = 0; j < currentImage.height; j++)
                    {
                        for(int k=0; k<3; k++){//To darken image by 50% multiply pixel value by 0.5 
                            value =0.5*currentImage.getPixel(i,j,k);
                    
                            currentImage.setPixel(i, j, k,value);
                        }
                    }
        
                } 
            }
            else{
                cout<<"Invalid choice please enter 1 or 2";
            }
                

        }
        else if(choice==8){
            currentImage = originalImage;
            int x , y , width , height ;
            cout<<"Please enter the width: ";
            cin>>width;
            cout<<"\nPlease enter the height: ";
            cin>>height;
            cout<<"\nPlease enter the horizontal dimension to start crop from: ";
            cin>>x;
            cout<<"\nPlease enter the vertical dimension to start crop from: ";
            cin>>y;
            currentImage=Crop_Filter(currentImage, x, y ,width, height);
            

        }
        else if(choice==9){

        }
        else if(choice==10){
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
            for(int i=0 ;i<currentImage.width; i++){
                for(int j=0 ; j<currentImage.height; j++){
                    for (int k = 0; k < 3; k++)
                    {
                        if(currentImage.getPixel(i,j,k)==0){
                            currentImage.setPixel(i,j,k,0);
                        }
                    }
                    
                }
            }





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

        else if(choice==13){
            currentImage = originalImage;
            for (int i = 0; i < currentImage.width; i++)
            {
                for(int j=0 ;j<currentImage.height; j++){
                    currentImage(i, j, 0) = min(currentImage(i, j, 0) + 5, 255);//255 //255
                    currentImage(i, j, 1) = min(currentImage(i, j, 1) + 5, 253);//253 //252
                    currentImage(i, j, 2) = min(currentImage(i, j, 2) + 5, 153);//153 //136
                }
            }

        }
        else if(choice==14){
            currentImage = originalImage;
            purple_Image(currentImage);

        }

        else if (choice == 15) {
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
        else if (choice==16)
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
