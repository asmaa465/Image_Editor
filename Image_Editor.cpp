/* FCAI – OOP Programming – 2023 - Assignment 1
   Program name:             ImageEditor.cpp
   Last Modification Date: 	 19/10/2023
   Asmaa Yasser,  ID:20221022, Group:B
   Esraa Mahmoud, ID:20220058, Group:A
   Yasmeen Yehia, ID:20220379, Group:A
   Purpose: Apply Filters to Images
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
string n;

void loadImage ();
void saveImage ();
void doSomethingForImage ();

int main()
{
  loadImage();
  doSomethingForImage();
  saveImage();
  return 0;
}

//_________________________________________
void loadImage () {
   char image1FileName[100];
   char image2FileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> image1FileName;

   // Add to it .bmp extension and load image
   strcat (image1FileName, ".bmp");
   readGSBMP(image1FileName, image);

   cout<<"Please select a filter to apply or 0 to exit: \n";
   cout<<"1-\tBlack & White Filter\n"
         "2-\tInvert Filter\n"
         "3-\tMerge Filter \n"
         "4-\tFlip Image\n"
         "5-\tRotate Image\n"
         "6-\tDarken and Lighten Image \n"
         "7-\tDetect Image Edges\n"
         "8-\tEnlarge Image\n"
         "9-\tShrink Image\n"
         "a-\tMirror 1/2 Image\n"
         "b-\tShuffle Image\n"
         "c-\tBlur Image\n"
         "d-\tCrop Image\n"
         "e-\tSkew Image Right  \n"
         "f-\tSkew Image Up  \n";

    cin>>n;
    if (n=="3"){
   //Get gray scale image file name to merge with it
   cout<< "Please enter name of image file to merge with:  ";
   cin>> image2FileName;

   // Add to it .bmp extension and load image
   strcat (image2FileName, ".bmp");
   readGSBMP(image2FileName, image2);
    }
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}
//_________________________________________
void darken_or_lighten() {
    char x;
    cout << "Do you want to (d)arken or (l)ighten? \n";
    cin >> x;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ( x == 'd')
                //Make the image darker by 50%
                image[i][j] = image[i][j] / 2;

            if ( x == 'l')
                //Make the image lighter by 50%
                image[i][j] = (255 - image[i][j]) / 2 + image[i][j];
        }
    }
}

void shrink(){
    unsigned char temp[SIZE][SIZE];
    string num_to_shrink;
    cout<<"Shrink to (1/2), (1/3) or (1/4)? ";
    cin>>num_to_shrink;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j]=255;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (num_to_shrink=="1/2")
                temp[i / 2][j / 2] = image[i][j];
            if (num_to_shrink=="1/3")
                temp[i / 3][j / 3] = image[i][j];
            if (num_to_shrink=="1/4")
                temp[i / 4][j / 4] = image[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = temp[i][j];

        }
    }
}

void blur(){
    unsigned char temp[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            int count = 0;
            for (int x = -9/2; x <= 9/2; x++) {
                for (int y = -9/2; y <= 9/2; y++) {
                    int ni = i + x;
                    int nj = j + y;

                    //handle edges and corners pixels
                    if (ni >= 0 && ni < 255 && nj >= 0 && nj < 255) {
                        sum += image[ni][nj];
                        count++;
                    }
                }
            }
            temp[i][j] =sum / count;
        }
    }

    // Copy the blurred image to the output image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = temp[i][j];
        }
    }
}

void skew_v(){
    cout<<"Please enter degree to skew vertical: ";
    double rad;
    cin >> rad;
    rad = (rad * 22) / (180 * 7);
    int x;
    x =  256 / (tan(rad) + 1);
    double step = SIZE - x;
    double mov = step / SIZE;
    unsigned char img_in[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            img_in[i][j] = 255;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            img_in[(j * x) / SIZE][i] = image[j][i];

        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = (int) step; j < step + x; ++j) {
            image[j][i] = img_in[(int) (j - step)][i];

        }
        step -= mov;
    }

}
void bw(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
                   if( image[i][j]>127){
                       image[i][j]=255;
                   }else{
                      image[i][j]=0;
                   }
        }
    }
    }
void mirror_image() {
    string s;cin>>s;
    if(s=="lower"){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j]=image[SIZE-1-i][j];
            }
        }
    }else if(s=="right"){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j]=image[i][SIZE-1-j];
            }
        }
    }else if(s=="left"){
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE/2; j < SIZE; j++) {
                image[i][j]=image[i][SIZE-1-j];
            }
        }
    }else if(s=="upper"){
        for (int i = SIZE/2; i < SIZE; i++) {
            for (int j =0 ; j < SIZE; j++) {
                image[i][j]=image[SIZE-1-i][j];
            }
        }
    }
}
void crop(){
    int x , y , l , w;
    cin>>x>>y>>l>>w;
    int xmin =x;
    int xmax =x+(l-1);
    int ymin =y;
    int ymax = y+(w-1);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i <= xmin || i >= xmax || j <= ymin || j >= ymax) {
                image[i][j] = 255;
            }
        }
    }
}
void flip() {
    cout<<"Flip (h)orizontally or (v)ertically ?\n";
    char s;
    cin >> s;
    if (s == 'v') {
        for (int i = 0; i < (SIZE + 1) / 2; i++) {
            for (int j = 0; j < SIZE; j++) { 
                long long temp = image[i][j];
                image[i][j] = image[SIZE - 1 - i][j];
                image[SIZE - 1 - i][j] = temp;
            }
        }
    } else if (s == 'h') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE + 1) / 2; j++) {
                long long temp = image[i][j]; 
                image[i][j] = image[i][SIZE - 1 - j];
                image[i][SIZE - 1 - j] = temp;
            }
        }
    }
}
void detect(){
int av = 0, sum = 0;
for (int i = 0; i < SIZE; i++) {
for (int j = 0; j < SIZE; j++) {
sum += image[i][j];
}
}
av = sum / (265 * 256);
for (int i = 1; i < SIZE-1; i++) {
for (int j = 1; j < SIZE-1; j++) {
if ((image[i][j]>av&&image[i][j+1]<av)||(image[i][j]<av&&image[i+1][j+1]>av)||(image[i][j]>av&&image[i+1][j]<av)||
(image[i][j]<av&&image[i+1][j]>av)||(image[i][j]>av&&image[i+1][j+1]<av)||(image[i][j]<av&&image[i][j+1]>av) )
{
image[i][j] = 0;
} else {
image[i][j] = 255;
}

}

}
}
void inverse() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255 - image[i][j];

        }

    }
}

void merge(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (n=="3")
                //Merge two images
                image[i][j]= (image[i][j] + image2[i][j]) / 2;

        }
    }

}

void rotate()
{

    int photo[SIZE][SIZE];
    int angle;
    cout<<"rotate(90),(180)or(270)?:";
    cin>>angle;
    for (int i= 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if(angle==90) {
                photo[j][SIZE - 1 - i] = image[i][j];
            }
            if(angle==180)
            {
                photo[SIZE - 1 - i][SIZE - 1 - j] = image[i][j];
            }
            if(angle==270){
                photo[SIZE - 1 - j][i] = image[i][j];
            }

        }
    }

    for (int i= 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = photo[i][j];
        }
    }
}

   void enlargeimage () {

    int q;
    cout<<"Which quarter to enlarge 1, 2, 3 or 4? ";
    cin>>q;
    int Q1[SIZE/2][SIZE/2];
    for (int i = 0; i <SIZE/2; i++) {
        for (int j = 0; j<SIZE/2; j++) {
            Q1[i][j]=image[i][j];
        }
    }
   
   int Q2[SIZE/2][SIZE/2];
    for (int i = 0; i <SIZE/2; i++) {
        for (int j = SIZE/2; j<SIZE; j++) {
            Q2[i][j]=image[i][j];
        }
    }

    int Q3[SIZE/2][SIZE/2];
    for (int i =SIZE/2; i<SIZE; i++) {
        for (int j = 0; j<SIZE/2; j++) {
            Q3[i][j]=image[i][j];
        }
    }


int Q4[SIZE/2][SIZE/2];
    for (int i =SIZE/2; i <SIZE; i++) {
        for (int j = SIZE/2; j<SIZE; j++) {
            Q4[i][j]=image[i][j];
        }
    } if(q==1)
    {
        for (int i = 0; i <SIZE; i++) {
            for (int j =0; j<SIZE; j++) {
                image[i][j]=Q1[i/2][j/2];
            }
        }
    }
      
    if(q==2)
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                image[i][j]=Q2[i/2][j/2];
            }
        }

    }
    if  (q==3)
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                image[i][j]=Q3[i/2][j/2];
            }
        }

    }

     if(q==4)
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                image[i][j]=Q4[i/2][j/2];
            }
        }

    }

}






void shuffle() {
    unsigned char photo[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            photo[i][j] = image[i][j];
        }
    }
    cout << "New order of quarters ? ";
    int q1, q2, q3, q4;
    cin >> q1 >> q2 >> q3 >> q4;
    if (q1 == 1) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = photo[i][j];
            }
        }
    }
    if (q1 == 2) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] =photo [i][j + 128];
            }
        }
    }
    if (q1 == 3) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = photo[i + 128][j];
            }
        }
    }
    if (q1 == 4) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = photo[i + 128][j + 128];
            }
        }
    }
    if (q2 == 1) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[i][j] =photo [i][j - 128];
            }
        }
    }
    if (q2 == 2) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[i][j] =photo [i][j];
            }
        }
    }
    if (q2 == 3) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[i][j] = photo[i + 128][j - 128];
            }
        }
    }
    if (q2 == 4) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[i][j] = photo[i + 128][j];
            }
        }
    }
    if (q3 == 1) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = photo[i - 128][j];
            }
        }
    }
    if (q3 == 2) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = photo[i - 128][j + 128];
            }
        }
    }
    if (q3 == 3) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = photo[i][j];
            }
        }
    }
    if (q3 == 4) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][j] = photo[i][j + 128];
            }
        }
    }
    if (q4 == 1) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[i][j] =photo [i - 128][j - 128];
            }
        }
    }
    if (q4 == 2) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[i][j] =photo[i - 128][j];
            }
        }
    }
    if (q4 == 3) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[i][j] = photo[i][j - 128];
            }
        }
    }
    if (q4 == 4) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[i][j] = photo[i][j];
            }
        }
    }
}
void skew_h() {

    cout<<"Please enter degree to skew horizontal: ";
    double rad;
    cin >> rad;
    rad=90-rad;
    rad = (rad * 22) / (180 * 7);
    int x;
    x = (tan(rad) * 256) / (tan(rad) + 1);
    double step = SIZE - x;
    double mov = step / SIZE;
    unsigned char img_in[SIZE][SIZE];
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            img_in[i][j] = 255;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            img_in[i][(j * x) / SIZE] = image[i][j];

        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = (int) step; j < step + x; ++j) {
            image[i][j] = img_in[i][(int) (j - step)];

        }
        step -= mov;
    }
}
  

//_________________________________________
void doSomethingForImage() {
   if(n=="1")
      bw();
   if(n=="2")
      inverse();
   if(n=="3")
      merge();
   if(n=="4")
      flip();
   if(n=="5")
      rotate();
   if (n=="6")
      darken_or_lighten();
   if(n=="7")
      detect();
   if(n=="8")
      enlargeimage();
    if (n=="9")
      shrink();
    if(n=="a")
      mirror_image();
    if(n=="b")
      shuffle();
    if (n=="c")
      blur();
    if(n=="d")
      crop();
    if (n=="e")
      skew_h();
    if(n=="f")
      skew_v();

    }
