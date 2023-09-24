The objective of this project is to Binarize an image, and encode/decode:
    
    1- To import the image.
    
    2- Binarise the image using an adaptive threshold. 
    This threshold was calculated using an average of the neighbour pixels in a customisable block size.
    If the value of the pixel was above the threshold, then it became a white pixel. if bellow, then it 
    became a black pixel.
    
    3- Calculate a "Ocurrences" array that reflected the occurrences of black and white pixels.
    To make it coherent for the decoder, I always introduced the number of white pixels first.
    For instance for {255,255,0,255,0,0,0,0,0}, you would get
    a vector of ints = {0,2,1,1,5} 
    For instance for {0,255,0,255,0,0,0,0,0}, you would get {1,1,1,1,5}.
    
    4-The decoder populated the pixels of the image using a complementary thought process. (**STILL IN DEVELOPMENT**)

    5- Write and Read the values of the encoder in a bitstream. (**STILL IN DEVELOPMENT**)


To create the executable, you will need to have cmake installed. 
afterwards run the following commands in the terminal:
       
        1- Run the command : cmake CMakeLists.txt 
        2- Run the command : make

The executable Binarization is now created.

To run the algorithm you will need to specify the input file, the output file and optionally 
the block size and cOffset, which are parameters which tweak the pseudo-adaptive threshold.
Their default values are blockSize = 20 and cOffset=30:

    Example 1: ./Binarization Assignment1_1.png Assignment1_1_Binarized.png 
    Example 2( w/optional arguments): ./Binarization Assignment1_1.png Assignment1_1_Binarized.png 20 30
