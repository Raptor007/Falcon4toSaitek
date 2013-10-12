#include <msclr\auto_gcroot.h>

class FIPBitmap
{
public:
	FIPBitmap( void );
	System::Drawing::Graphics ^GetGraphics( void );
	unsigned char *GetBuffer( void );

private:
	unsigned char Buffer[ 320*240*3 ];
	msclr::auto_gcroot<System::Drawing::Bitmap^> Bmp;
	msclr::auto_gcroot<System::Drawing::Graphics^> Gfx;
};
