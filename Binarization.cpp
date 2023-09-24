
#include "Binarization.h"

class Image{
  public:
    u32 width;
    u32 height;
    u8* data;
    void make_image(Image & I, u32 width, u32 height)
  {
//    assert(width);
//    assert(height);

    I.width = width;
    I.height = height;
    I.data = (u8*)malloc(sizeof(u8) * width * height);

    assert(I.data);
  }
    void clear_image(Image & I){
      if(I.data!=nullptr){
        free(I.data);
        I.data = nullptr;
      }
    }
    void computeBinarization(Image & Iin, Image &Iout, int blockSize, int c_offset)
    {
      for(int pos = 0; pos < Iin.height * Iin.width;pos++ )
        Iout.data[pos] = iterativeThreshold(Iin,pos,pos%Iin.width,pos/Iin.width,blockSize,c_offset);
    }
    u8 iterativeThreshold(Image& Iin, int pos, int x , int y, int blockSize,int c_offset){
      int sum = 0;
      int count = 0;
        // Iterate trough the neighbours, given into account the 
        for (int n = -blockSize / 2; n <= blockSize / 2; n++) {
                for (int m = -blockSize / 2; m <= blockSize / 2; m++) {
                    int i = x + m;
                    int j = y + n;

                    // Check if the neighboring pixel is within the image boundaries
                    if (i >= 0 && i < Iin.width && j >= 0 && j < Iin.height) {
                        sum += Iin.data[j* Iin.width + i%Iin.width];
                        count++;
                    }
                }
            }

            // Calculate the local threshold
            int localThreshold = sum / count - c_offset;
            // Binarization
            if (Iin.data[pos]> localThreshold) {
                return 255; // Set pixel to white
            } else {
                return 0;   // Set pixel to black
            }
    }
};

class Encoder{
  public:
      Image I;
      vector<int> stream;
      int aux;
      void write_stream(const char* encoderPath){
        ofstream encoderFile;
        encoderFile.open(encoderPath, ios::binary); //Open as a binary file
        encode();
          size_t size = stream.size();
          encoderFile.write(reinterpret_cast<char*>(&this->I.width),sizeof(u32));
          encoderFile.write(reinterpret_cast<char*>(&this->I.height),sizeof(u32));
          encoderFile.write(reinterpret_cast<char*>(&size),sizeof(size));// write the size of the vector
          for(int i=0;i < size ; i++)
          {
            aux = stream[i]; 
            encoderFile.write(reinterpret_cast<char*>(&aux),sizeof(int));
          }
        encoderFile.close();
      };
      void encode(){

        int counter=0;
        int pixel = 0, prev_pixel=0;
        //u32 pos;
        pixel = this->I.data[0];
       
        prev_pixel = pixel;
        if (pixel == 255)
          this->stream.push_back(0);
     
        for(int pos = 0; pos < I.height * I.width; pos++){
             prev_pixel = pixel;
             pixel= I.data[pos]; //curent pixel
             if(pixel != prev_pixel & counter > 0){
                 this->stream.push_back(counter);
                 counter= 1;
             }
             else
                 counter ++;
         } 
        this->stream.push_back(counter);
      };
};
class Decoder{
  public:
  Image I;
  vector<int> stream;
  int nOcurrences;
  
  void readStream(const char* decoderPath){
  ifstream inputFile(decoderPath,ios::binary);
  size_t size= 0;
  inputFile.read(reinterpret_cast<char*>(&(this->I.width)),sizeof(u32));// Read size of width of Image
  inputFile.read(reinterpret_cast<char*>(&(this->I.height)),sizeof(u32)); // Read size of height
  this->I.make_image(this->I,this->I.width,this->I.height);
  cout << this->I.width << endl << I.height;
  inputFile.read(reinterpret_cast<char*>(&size),sizeof(size)); // Read size of vector of ocurrences
  for(size_t i = 0; i< size; i++)
  {
    inputFile.read(reinterpret_cast<char*>(&nOcurrences),sizeof(int));
    this->stream.push_back(nOcurrences);
  }
  inputFile.close();
  decode();
  };

  void decode(){
       int x=0,y=0,pos=0;
       for(int i = 0; i < stream.size(); i++){
        for(int j = 0 ; j < stream[i]; j++){
             if(i%2 == 1)
                 this->I.data[pos]= 255;
             else
             pos++;
         }
     }
  };

};
