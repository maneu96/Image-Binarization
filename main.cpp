
#include "Binarization.h"

int main(int argc,char *argv[]){
   const char *imagePath = argv[1];
   const char *binarizedImagePath = argv[2];
   int blockSize = 20, cOffset = 30; //Default values for the iterative Threshold algorithmn
   if (argc > 3){
    stringstream obj,obj2;
    obj << argv[3];
    obj >> blockSize;
    obj2 << argv[4];
    obj2 >> cOffset;
   }

   Image Iin,Iout;
   int x=0,y=0,n=0;
   /****************** Creates Iin and loads the image data **********************/
   Iin.data = stbi_load(imagePath,&x,&y,&n,0); 
   Iin.width = x;
   Iin.height = y;
   /****************** Creates Iout and allocates the necessary memory ************/
   Iout.make_image(Iout,x,y);
   //Encoder encoder;
   //Decoder decoder;
   /****************** Compute binarization of the input image *******************/
  
   Iin.computeBinarization(Iin,Iout,blockSize, cOffset);
   stbi_write_png(binarizedImagePath,Iout.width,Iout.height,1,Iout.data,0);

  /* TO IMPLEMENT (RUN LENGTH ENCODING-DECODING) */
   //Encoder encoder;
   //Decoder decoder;
   //  encoder.I=Iout;
   //  encoder.write_stream("encodedimage");
   //   decoder.readStream("encodedimage");
   // stbi_write_png("Assignment1_1_1_decoded.png",decoder.I.width,decoder.I.height,1,decoder.I.data,0);
  
   /******************* Free allocated memory *************/
   stbi_image_free(Iin.data);
   Iout.clear_image(Iout);

}